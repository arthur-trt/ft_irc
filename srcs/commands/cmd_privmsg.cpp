/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_privmsg.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:02:21 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/18 15:38:14 by atrouill         ###   ########.fr       */
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

void	cmd_privmsg ( IRC *serv, User *user, std::string & args )
{
	std::vector<std::string>	split;	
	std::string					target, message;

	split = ft_split(args, ":");
	target = trim_copy(split[0]);
	message.append(user_answer(user));
	message.append("PRIVMSG ");
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
			receiver.second->send(serv, user, message);
	}
}