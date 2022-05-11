/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_user.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:55:04 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/11 19:27:45 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPL.hpp"
#include "utils.hpp"
#include "TCPServer.Class.hpp"
#include "commands.hpp"

int		cmd_user ( TCPServer *serv, User *user, std::string args )
{
	std::vector<std::string>	parsed;
	std::string					answer;

	parsed = ft_split(args, " ");
	//if (parsed.size() < 4)
	//{
	//	// ERROR HERE
	//}
	debug("parsed[0] : %s", parsed[0].c_str());
	debug("parsed[1] : %s", parsed[1].c_str());
	debug("parsed[2] : %s", parsed[2].c_str());
	debug("parsed[3] : %s", parsed[3].c_str());

	user->_user_name = parsed[0];
	user->_real_name = parsed[3];

	serv->add_to_buffer(std::make_pair(user->_fd, send_rpl(1, serv, user)));
	serv->add_to_buffer(std::make_pair(user->_fd, send_rpl(2, serv, user)));
	serv->add_to_buffer(std::make_pair(user->_fd, send_rpl(3, serv, user)));
	serv->add_to_buffer(std::make_pair(user->_fd, send_rpl(4, serv, user)));
	return (0);
}
