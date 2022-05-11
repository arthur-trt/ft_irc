/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nick.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:14:16 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/11 18:59:59 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include "utils.hpp"
#include "TCPServer.Class.hpp"
#include "User.Class.hpp"

class TCPServer;
class User;

int		cmd_nick ( TCPServer *serv, User *user, std::string args )
{
	std::string	answer;

	if (user->_nick_name == "")
	{
		//answer.append("NICK ");
	}
	else
	{
		answer.append(user->_nick_name);
		answer.append("@");
		answer.append(user->_user_name);
		answer.append("!");
		answer.append(user->_host_name);
		answer.append(" NICK ");
		answer.append(args);
		answer.append("\r\n");
	}
	user->_nick_name = args;
	if (answer != "")
		serv->add_to_buffer(std::make_pair(user->_fd, answer));

	return (0);
}
