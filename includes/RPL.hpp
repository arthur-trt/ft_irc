/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:03:26 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/20 11:54:16 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPL_HPP
# define RPL_HPP

# include "config.hpp"


# define RPL_WELCOME(nick, user, host)	\
	(" :Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host + "\r\n")	//001
# define RPL_YOURHOST					\
	" :Your host is " SERVERNAME ", running version " VERSION "\r\n"						//002
# define RPL_CREATED					\
	(" :This server was created 01/01/1970\r\n")											//003
# define RPL_MYINFO						\
	(" :" SERVERNAME " " VERSION " aiwroOs OovaimnpsrtklbeI\r\n")							//004


# define ERR_NONICKNAMEGIVEN			\
	(" :No nickname given\r\n")																// 431
# define ERR_NICKNAMEINUSE(nick)		\
	(" " + nick + " :Nickname is already in use\r\n")										// 433
# define ERR_ERRONEUSNICKNAME(nick)		\
	(" " + nick + " :Erroneous nickname\r\n")												// 432
# define ERR_NEEDMOREPARAMS(command)	\
	(" " + command + " :Not enough parameters\r\n")											// 461
# define ERR_ALREADYREGISTRED			\
	(" :Unauthorized command (already registered)\r\n")										// 462
# define ERR_UNKNOWNCOMMAND(command)	\
	(" " + command + " :Unknown command\r\n")												// 421
# define RPL_NAMREPLY(channel)			\
	(" = " + channel + " :")																// 353
# define RPL_ENDOFNAMES(channel)		\
	(" " + channel + " :End of NAMES list\r\n")												// 366
# define RPL_NOTOPIC(channel)			\
	(" " + channel + " :No topic is set\r\n")												// 331
# define RPL_TOPIC(channel)				\
	(" " + channel + " :")																	// 332
# define ERR_NOTONCHANNEL(channel)		\
	(" " + channel + " :You're not on that channel\r\n")									// 442
# define ERR_CHANOPRIVSNEEDED(channel)	\
	(" " + channel + " :You're not channel operator\r\n")									// 482

#endif
