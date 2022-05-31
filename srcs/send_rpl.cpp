/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_rpl.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 19:01:45 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/31 14:41:06 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPL.hpp"
#include "config.hpp"
#include "IRC.Class.hpp"
#include "User.Class.hpp"
#include "utils.hpp"
#include "functions.hpp"

/**
 * @brief Build IRC RPL according to RFC2812.
 *
 * @param rpl_num RPL number as described in RFC2812 (https://datatracker.ietf.org/doc/html/rfc2812#section-5)
 * You can found all the define in `includes/RPL.hpp`
 * @param serv IRC serv instance
 * @param user User who provocate this message
 * @param args Args (depending of the RPL)
 * @return RPL formatted ready to be sent
 */
std::string	send_rpl(int rpl_num, IRC *serv, User *user, std::string args, std::string args2, std::string args3)
{
	std::string		answer = ":";
	std::string		code;

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
		case 221:
			answer.append(RPL_UMODEIS(args, args2, args3));
			break;
		case 315:
			answer.append(RPL_ENDOFWHO(args));
			break;
		case 322:
			answer.append(RPL_LIST(args, args2));
			break;
		case 323:
			answer.append(RPL_LISTEND);
			break;
		case 324:
			answer.append(RPL_CHANNELMODEIS(args, args2, args3));
			break;
		case 331:
			answer.append(RPL_NOTOPIC(args));
			break;
		case 332:
			answer.append(RPL_TOPIC(args));
			break;
		case 353:
			answer.append(RPL_NAMREPLY(args));
			break;
		case 366:
			answer.append(RPL_ENDOFNAMES(args));
			break;
		case 402:
			answer.append(ERR_NOSUCHSERVER(args));
			break;
		case 403:
			answer.append(ERR_NOSUCHCHANNEL(args));
			break;
		case 404:
			answer.append(ERR_CANNOTSENDTOCHAN(args));
			break;
		case 421:
			answer.append(ERR_UNKNOWNCOMMAND(args));
			break;
		case 431:
			answer.append(ERR_NONICKNAMEGIVEN);
			break;
		case 432:
			answer.append(ERR_ERRONEUSNICKNAME(args));
			break;
		case 441:
			answer.append(ERR_USERNOTINCHANNEL(args, args2));
			break;
		case 442:
			answer.append(ERR_NOTONCHANNEL(args));
			break;
		case 433:
			answer.append(ERR_NICKNAMEINUSE(args));
			break;
		case 461:
			answer.append(ERR_NEEDMOREPARAMS(args));
			break;
		case 462:
			answer.append(ERR_ALREADYREGISTRED);
			break;
		case 472:
			answer.append(ERR_UNKNOWNMODE(args));
			break;
		case 475:
			answer.append(ERR_BADCHANNELKEY(args));
			break;
		case 482:
			answer.append(ERR_CHANOPRIVSNEEDED(args));
			break;
		case 501:
			answer.append(ERR_UMODEUNKNOWNFLAG(args));
			break;
		default:
			;
	}
	return (answer);
}

/**
 * @brief Build a answer from and to user
 *
 * @param nick Nickname of the user
 * @param username Username of the user
 * @param host Hostname of the user
 * @return Answer formatted
 */
std::string	user_answer(const std::string & nick, const std::string & username, const std::string & host)
{
	std::string		answer;

	answer.append(":");
	answer.append(nick);
	answer.append("!");
	answer.append(username);
	answer.append("@");
	answer.append(host);
	answer.append(" ");

	return (answer);
}

/**
 * @brief Build a answer from and to user
 *
 * @param user User pointer
 * @return Answer formatted
 */
std::string	user_answer(const User * user)
{
	return (user_answer(user->_nick_name, user->_user_name, user->_hostname));
}
