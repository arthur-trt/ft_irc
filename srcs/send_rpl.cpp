/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_rpl.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 19:01:45 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/16 22:38:49 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPL.hpp"
#include "config.hpp"
#include "IRC.Class.hpp"
#include "User.Class.hpp"
#include "utils.hpp"
#include "functions.hpp"


std::string	send_rpl(int rpl_num, IRC *serv, User *user, std::string args)
{
	std::string		answer = ":";
	std::string		code;

	(void)args;
	answer.append(serv->_tcp.getHostname());
	answer.append(" ");
	if (rpl_num < 10)
		answer.append("00");
	else if (rpl_num < 100)
		answer.append("0");
	answer.append(ft_to_string(rpl_num));
	answer.append(" ");
	if (user->_nick_name == "")
		answer.append("*");
	else
		answer.append(user->_nick_name);
	switch ( rpl_num )
	{
		case 1:
			answer.append(RPL_WELCOME(user->_nick_name, user->_user_name, user->_hostname));
			break;
		case 2:
			answer.append(RPL_YOURHOST);
			break;
		case 3:
			answer.append(RPL_CREATED);
			break;
		case 4:
			answer.append(RPL_MYINFO);
			break;
		case 431:
			answer.append(ERR_NONICKNAMEGIVEN);
			break;
		case 433:
			answer.append(ERR_NICKNAMEINUSE(args));
			break;
		case 432:
			answer.append(ERR_ERRONEUSNICKNAME(args));
			break;
		case 461:
			answer.append(ERR_NEEDMOREPARAMS(args));
			break;
		case 462:
			answer.append(ERR_ALREADYREGISTRED);
			break;
		case 421:
			answer.append(ERR_UNKNOWNCOMMAND(args));
			break;
		case 353:
			answer.append(RPL_NAMREPLY(args));
			break;
		case 366:
			answer.append(RPL_ENDOFNAMES(args));
			break;
		default:
			;
	}
	return (answer);
}

std::string	user_answer(const std::string & nick, const std::string & username, const std::string & host)
{
	std::string		answer;

	answer.append(":");
	answer.append(nick);
	answer.append("@");
	answer.append(username);
	answer.append("!");
	answer.append(host);
	answer.append(" ");

	return (answer);
}

std::string	user_answer(const User * user)
{
	return (user_answer(user->_nick_name, user->_user_name, user->_hostname));
}
