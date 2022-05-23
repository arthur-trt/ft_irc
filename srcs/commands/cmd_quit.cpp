/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_quit.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:57:03 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/23 19:27:40 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPL.hpp"
#include "utils.hpp"
#include "IRC.Class.hpp"
#include "commands.hpp"
#include "functions.hpp"
#include <vector>

void	cmd_quit ( IRC *serv, User *user, std::string & args )
{
	std::string						answer;
	std::string						quit_msg;
	std::string						chans;
	std::list<Channel *>::iterator	it;

	answer = user_answer(user);
	answer.append("QUIT ");
	if (args == "" || args.find_first_of(":") == std::string::npos)
	{
		quit_msg = " :leaving";
		answer.append(":leaving");
	}
	else
	{
		quit_msg = " " + trim_copy(args);
		answer.append(trim_copy(args));
	}
	it = user->_channel_joined.begin();
	while (it != user->_channel_joined.end())
	{
		chans.append((*it)->getName());
		it++;
		if (it != user->_channel_joined.end())
			chans.append(", ");
	}
	cmd_part(serv, user, chans.append(quit_msg));
	serv->_tcp.close_connection(user->_fd);
	serv->send_everyone(answer);
}
