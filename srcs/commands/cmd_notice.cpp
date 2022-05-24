/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_notice.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldes-cou <ldes-cou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:15:26 by ldes-cou          #+#    #+#             */
/*   Updated: 2022/05/24 17:28:38 by ldes-cou         ###   ########.fr       */
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

void	cmd_notice (IRC *serv, User *user, std::string & args)
{
	std::vector<std::string>	split;
	std::string					target, message;

	split = ft_split(args, ":");
	target = trim_copy(split[0]);
	message.append(user_answer(user));
	message.append("NOTICE ");
	message.append(target);
	message.append(" :");
	message.append(split[1]);
	message.append("\r\n");
	if (target.find_first_of(CHAN_FIRST, 0) == std::string::npos)
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