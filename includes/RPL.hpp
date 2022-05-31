/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:03:26 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/31 14:40:46 by atrouill         ###   ########.fr       */
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



# define RPL_UMODEIS(nick, mode, params) \
	(" " + nick + " " + mode + " " + params + " \r\n")										// 221
# define RPL_ENDOFWHO(name)			\
	(" "+ name + " :End of WHO list\r\n")													// 315
# define RPL_LIST(chan, topic)		\
	(" " + chan + " :" + topic + "\r\n")													// 322
# define RPL_LISTEND				\
	(" :End of LIST\r\n")																	// 323
# define RPL_CHANNELMODEIS(channel, mode, modeparams) \
	(" " + channel + " " + mode + " " + modeparams + " \r\n")								// 324
# define RPL_NOTOPIC(channel)			\
	(" " + channel + " :No topic is set\r\n")												// 331
# define RPL_TOPIC(channel)				\
	(" " + channel + " :")																	// 332
# define RPL_NAMREPLY(channel)			\
	(" = " + channel + " :")																// 353
# define RPL_ENDOFNAMES(channel)		\
	(" " + channel + " :End of NAMES list\r\n")												// 366
# define ERR_NOSUCHSERVER(server)		\
	(" " + server + " :No such server\r\n")													// 402
# define ERR_NOSUCHCHANNEL(channel)		\
	(" " + channel + " :No such channel\r\n")												// 403
# define ERR_CANNOTSENDTOCHAN(channel)	\
	(" " + channel + " :Cannot send to channel\r\n")										// 404
# define ERR_UNKNOWNCOMMAND(command)	\
	(" " + command + " :Unknown command\r\n")												// 421
# define ERR_NONICKNAMEGIVEN			\
	(" :No nickname given\r\n")																// 431
# define ERR_ERRONEUSNICKNAME(nick)		\
	(" " + nick + " :Erroneous nickname\r\n")												// 432
# define ERR_NICKNAMEINUSE(nick)		\
	(" " + nick + " :Nickname is already in use\r\n")										// 433
# define ERR_USERNOTINCHANNEL(nick, channel)	\
	(" " + nick + " " + channel + " :They aren't on that channel\r\n")						// 441
# define ERR_NOTONCHANNEL(channel)		\
	(" " + channel + " :You're not on that channel\r\n")									// 442
# define ERR_NEEDMOREPARAMS(command)	\
	(" " + command + " :Not enough parameters\r\n")											// 461
# define ERR_ALREADYREGISTRED			\
	(" :Unauthorized command (already registered)\r\n")										// 462
# define ERR_UNKNOWNMODE(channel) \
	(" " + channel + " :is unknown mode char to me for \r\n")								// 472
# define ERR_BADCHANNELKEY(channel) \
	(" " + channel + " :Cannot join channel (+k) \r\n")										// 475
# define ERR_CHANOPRIVSNEEDED(channel)	\
	(" " + channel + " :You're not channel operator\r\n")									// 482
# define  ERR_UMODEUNKNOWNFLAG(mode) \
	(" :Unknown " + mode + " flag \r\n")													// 501


#endif
