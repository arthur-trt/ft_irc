/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_part.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:27:52 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/23 14:24:43 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPL.hpp"
#include "utils.hpp"
#include "IRC.Class.hpp"
#include "commands.hpp"
#include "functions.hpp"
#include <vector>

static bool	valid_args ( IRC *serv, User *user, std::string args )
{
	if (args == "")
	{
		serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(461, serv, user, "PART")));
		return (false);
	}
	return (true);
}

void	cmd_part ( IRC *serv, User *user, std::string & args )
{
	std::string					msg_part;
	std::vector<std::string>	chan_to_quit;
	std::pair<bool, Channel*>	chan;

	if (valid_args(serv, user, args))
	{
		if (args.find_first_of(":") != std::string::npos)
		{
			chan_to_quit = ft_split(args, ":");
			msg_part = trim_copy(chan_to_quit[1]);
			chan_to_quit = ft_split(chan_to_quit[0], ",");
		}
		else
		{
			msg_part = "";
			chan_to_quit = ft_split(args, ",");
		}
		while (chan_to_quit.size() > 0)
		{
			std::string chan_name = trim_copy(chan_to_quit.back());
			chan = serv->get_channel(chan_name);
			if (chan.first)
			{
				if (chan.second->userIsIn(user))
				{
					std::string	answer = user_answer(user);

					answer.append("PART ");
					answer.append(chan_name);
					answer.append(" :");
					answer.append(msg_part);
					answer.append("\r\n");

					chan.second->send_all(serv, answer);
					chan.second->kickUser(user);
					if (chan.second->getMembersCount() == 0)
					{
						serv->remove_channel(chan_name);
					}
				}
				else
				{
					serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(442, serv, user, chan_name)));
				}
			}
			else
			{
				serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(403, serv, user, chan_name)));
			}
			chan_to_quit.pop_back();
		}
	}
}
