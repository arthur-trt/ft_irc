/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_rpl.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 19:01:45 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/11 19:37:36 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPL.hpp"
#include "config.hpp"
#include "TCPServer.Class.hpp"
#include "User.Class.hpp"
#include "utils.hpp"


std::string	send_rpl(int rpl_num, TCPServer *serv, User *user)
{
	std::string		answer = ":";
	std::string		code;

	answer.append(serv->getHostname());
	answer.append(" ");
	if (rpl_num < 10)
		answer.append("00");
	else if (rpl_num < 100)
		answer.append("0");
	answer.append(ft_to_string(rpl_num));
	answer.append(" ");
	answer.append(user->_nick_name);
	answer.append(" :");
	switch ( rpl_num )
	{
		case 1:
			answer.append(RPL_WELCOME(user->_nick_name, user->_user_name, user->_host_name));
			break;
		case 2:
			answer.append(RPL_YOURHOST);
			break;
		case 3:
			answer.append(RPL_CREATED);
			break;
		case 4:
			answer.append(RPL_MYINFO);
		default:
			;
	}
	return (answer);
}
