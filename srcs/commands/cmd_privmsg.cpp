/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_privmsg.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:02:21 by atrouill          #+#    #+#             */
/*   Updated: 2022/06/02 15:04:39 by atrouill         ###   ########.fr       */
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
		// Test if server mask
		if (target[0] == '$')
		{
			if (user->_isOperator)
			{
				std::string	mask = trim_copy(target);
				if (valid_mask(serv, user, mask))
				{
					if (pattern_match(serv->_tcp.getHostname(), mask))
					{
						message = user_answer(user);
						message.append("PRIVMSG ");
						message.append(mask);
						message.append(" :");
						message.append(split[1]);
						message.append("\r\n");
						serv->send_everyone(message);
					}
				}
			}
			else
			{
				// NO ERROR CODE IN RFC WTF PEOPLE
			}
		}
		
	}
}
