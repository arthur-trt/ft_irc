/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_notice.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:15:26 by ldes-cou          #+#    #+#             */
/*   Updated: 2022/06/09 14:34:39 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPL.hpp"
#include "utils.hpp"
#include "commands.hpp"
#include "IRC.Class.hpp"
#include "User.Class.hpp"
#include "functions.hpp"
#include <vector>
#include <string>

static bool		valid_args (std::string & args )
{
	std::vector<std::string>	split;
	std::string					target, message;

	if (args.find_first_of(':') != std::string::npos && args[args.length() - 1] != ':')
	{
		split = ft_split(args, ":");
		target = trim_copy(split[0]);
		if (target == "")
		{
			return (false);
		}
		message = trim_copy(split[1]);
		if (message == "")
		{
			return (false);
		}
		return (true);
	}
	return (false);
}

void	cmd_notice (IRC *serv, User *user, std::string & args)
{
	std::string					target, message;

	if (valid_args(args))
	{
		target = trim_copy(args.substr(0, args.find(':')));
		message = user_answer(user);
		message.append("NOTICE ");
		message.append(target);
		message.append(" :");
		message.append(args.substr(args.find(':') + 1, args.size()));
		message.append("\r\n");
		if (target.find_first_of(CHAN_FIRST) == std::string::npos)
		{
			debug("Send message to user");
			std::pair<bool, User*>	receiver;

			receiver = serv->get_user(target);
			if (receiver.first)
				serv->_tcp.add_to_buffer(std::make_pair(receiver.second->_fd, message));
		}
		else
		{
			debug("Send message to channel");
			std::pair<bool, Channel*>	receiver;

			receiver = serv->get_channel(target);
			if (receiver.first)
			{
				if (receiver.second->userIsIn(user))
					receiver.second->send(serv, user, message);
			}
		}

	}
}
