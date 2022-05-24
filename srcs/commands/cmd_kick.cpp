/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_kick.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:37:09 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/24 16:16:27 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPL.hpp"
#include "config.hpp"
#include "IRC.Class.hpp"
#include "User.Class.hpp"
#include "utils.hpp"
#include "functions.hpp"
#include <vector>
#include <string>

static bool	valid_args ( IRC *serv, User *user, std::string args )
{
	std::vector<std::string>	tmp;

	tmp = ft_split(args, " ");
	if (tmp.size() < 2)
	{
		serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(461, serv, user, "KICK")));
		return (false);
	}
	return (true);
}

void	cmd_kick ( IRC *serv, User *user, std::string & args )
{
	std::vector<std::string>		tmp;
	std::vector<std::string>		channels;
	std::vector<std::string>		users;
	std::string						kick_message;
	std::string						answer;
	std::pair<bool, Channel*>		chan_tmp;
	std::pair<User*, bool>			user_tmp;
	std::pair<bool, User*>			to_kick;

	if (valid_args(serv, user, args))
	{
		// Build kick message, if not kick_message should be the nick_name
		if (args.find_first_of(":") != std::string::npos)
		{
			tmp = ft_split(args, ":");
			kick_message = tmp[1];
		}
		else
		{
			tmp[0] = args;
			kick_message = "";
		}

		tmp = ft_split(tmp[0], " ");
		channels = ft_split(tmp[0], ",");
		users = ft_split(tmp[1], ",");

		for (size_t i = 0; i < channels.size(); i++)
		{
			chan_tmp = serv->get_channel(channels[i]);
			if (chan_tmp.first)
			{
				if (chan_tmp.second->userIsIn(user))
				{
					user_tmp = chan_tmp.second->getUser(user);
					if (user_tmp.second) // Is operator
					{
						for (size_t j = 0; j < users.size(); j++)
						{
							if (chan_tmp.second->userIsIn(users[j]))
							{
								answer = user_answer(user);
								answer.append("KICK ");
								answer.append(channels[i]);
								answer.append(" ");
								answer.append(users[i]);
								answer.append(" :");
								if (kick_message != "")
									answer.append(kick_message);
								else
									answer.append(users[i]);
								answer.append("\r\n");
								chan_tmp.second->send_all(serv, answer);
								to_kick = serv->get_user(users[i]);
								chan_tmp.second->kickUser(to_kick.second);
							}
							else
							{
								serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(441, serv, user, users[j], channels[i])));
							}
						}
					}
					else
					{
						serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(482, serv, user, channels[i])));
					}
				}
				else
				{
					serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(442, serv, user, channels[i])));
				}
			}
			else
			{
				serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(403, serv, user, channels[i])));
			}
		}
	}
}
