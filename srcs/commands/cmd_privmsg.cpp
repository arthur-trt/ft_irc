/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_privmsg.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:02:21 by atrouill          #+#    #+#             */
/*   Updated: 2022/06/02 19:27:38 by atrouill         ###   ########.fr       */
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

static bool		valid_mask ( IRC *serv, User *user, std::string & args )
{
	std::string		tld;

	if (args.find_first_of('.') == std::string::npos)
	{
		serv->_tcp.add_to_buffer(std::make_pair(
			user->_fd,
			send_rpl(413, serv, user, args)
		));
		return (false);
	}
	tld = args.substr(args.find_last_of('.'), args.size());
	if (tld.find_first_of('*') != std::string::npos || tld.find_first_of('?') != std::string::npos)
	{
		serv->_tcp.add_to_buffer(std::make_pair(
			user->_fd,
			send_rpl(414, serv, user, args)
		));
		return (false);
	}
	return (true);
}

static bool		valid_args ( IRC *serv, User *user, std::string & args )
{
	std::vector<std::string>	split;
	std::string					target, message;

	split = ft_split(args, ":");
	target = trim_copy(split[0]);
	if (target == "")
	{
		serv->_tcp.add_to_buffer(std::make_pair(
			user->_fd,
			send_rpl(411, serv, user, "PRIVMSG")
		));
		return (false);
	}
	message = trim_copy(split[0]);
	if (message == "")
	{
		serv->_tcp.add_to_buffer(std::make_pair(
			user->_fd,
			send_rpl(412, serv, user)
		));
		return (false);
	}
	return (true);
}

void	cmd_privmsg ( IRC *serv, User *user, std::string & args )
{
	std::vector<std::string>	split;
	std::string					target, message;

	split = ft_split(args, ":");
	target = trim_copy(split[0]);
	if (valid_args(serv, user, args))
	{
		message = user_answer(user);
		message.append("PRIVMSG ");
		message.append(target);
		message.append(" :");
		message.append(split[1]);
		message.append("\r\n");
		// Test if server mask
		if (target[0] == '$')
		{
			if (user->_isOperator)
			{
				if (valid_mask(serv, user, target))
				{
					if (pattern_match(serv->_tcp.getHostname(), target))
					{
						debug("Server pattern mathc");
						serv->send_everyone(message);
					}
				}
			}
			else
			{
				debug("%s : Not operator", user->_nick_name.c_str());
			}
		}
		// Test if it's a hostname mask
		else if (target[0] == '#' && args.find_first_of('.') != std::string::npos)
		{
			if (user->_isOperator)
			{
				std::list<User *>			users_list;
				std::list<User *>::iterator	users_list_it;

				users_list = user_masks(serv, "*!*@" + target);
				users_list_it = users_list.begin();
				while (users_list_it != users_list.end())
				{
					debug("Mask match with : %s", (*users_list_it)->_nick_name.c_str());
					if (*users_list_it != user)
					{
						serv->_tcp.add_to_buffer(std::make_pair(
							(*users_list_it)->_fd,
							message
						));
					}
					users_list_it++;
				}
			}
			else
			{
				debug("%s : Not operator", user->_nick_name.c_str());
			}
		}
		else
		{
			std::pair<bool, Channel *>	chan_tmp = serv->get_channel(target);
			std::pair<bool, User *>		user_tmp = serv->get_user(target);

			// If found a channel
			if (chan_tmp.first)
			{
				if (chan_tmp.second->userIsIn(user))
				{
					chan_tmp.second->send(serv, user, message);
				}
				else
				{
					serv->_tcp.add_to_buffer(std::make_pair(
						user->_fd,
						send_rpl(404, serv, user, target)
					));
				}
			}
			// If found a user
			else if (user_tmp.first)
			{
				serv->_tcp.add_to_buffer(std::make_pair(
					user_tmp.second->_fd,
					message
				));
			}
			else
			{
				serv->_tcp.add_to_buffer(std::make_pair(
					user->_fd,
					send_rpl(401, serv, user, target)
				));
			}
		}
	}
}
