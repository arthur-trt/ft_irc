/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:03:26 by atrouill          #+#    #+#             */
/*   Updated: 2022/06/02 15:53:08 by atrouill         ###   ########.fr       */
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
# define RPL_INVITING(channel, nick)			\
	(" " + nick + channel + "\r\n")																// 341
# define RPL_NAMREPLY(channel)			\
	(" = " + channel + " :")																// 353
# define RPL_ENDOFNAMES(channel)		\
	(" " + channel + " :End of NAMES list\r\n")												// 366
# define ERR_NOSUCHNICK(nick)		\
	(" " + nick + " :No such nick/channel\r\n")												// 401
# define ERR_NOSUCHSERVER(server)		\
	(" " + server + " :No such server\r\n")													// 402
# define ERR_NOSUCHCHANNEL(channel)		\
	(" " + channel + " :No such channel\r\n")												// 403
# define ERR_CANNOTSENDTOCHAN(channel)	\
	(" " + channel + " :Cannot send to channel\r\n")										// 404
# define ERR_NORECIPIENT(command)		\
	(" :No recipient given " + command + "\r\n")											// 411
# define ERR_NOTEXTTOSEND				\
	(" :No text to send\r\n")																// 412
# define ERR_NOTOPLEVEL(mask)			\
	(" " + mask + " :No toplevel domain specified\r\n")										// 413
# define ERR_WILDTOPLEVEL(mask)			\
	(" " + mask + " :Wildcard in toplevel domain\r\n")										// 414
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
# define ERR_USERONCHANNEL(nick, channel)		\
	(" " + nick + channel + " :is already on channel\r\n")									// 443
# define ERR_NOTREGISTERED				\
	(" :You have not registered\r\n")														// 451
# define ERR_NEEDMOREPARAMS(command)	\
	(" " + command + " :Not enough parameters\r\n")											// 461
# define ERR_ALREADYREGISTRED			\
	(" :Unauthorized command (already registered)\r\n")										// 462
# define ERR_KEYSET(channel)	\
	(" " + channel + ":Channel key already set\r\n")										// 467
# define ERR_UNKNOWNMODE(channel) \
	(" " + channel + " :is unknown mode char to me for \r\n")								// 472
# define ERR_INVITEONLYCHAN(channel) \
	(" " + channel + " :Cannot join channel (+i)\r\n")										// 473
# define ERR_BANNEDFROMCHAN(channel) \
	(" " + channel + " :Cannot join channel (+b)\r\n")										// 474
# define ERR_BADCHANNELKEY(channel) \
	(" " + channel + " :Cannot join channel (+k) \r\n")										// 475
# define ERR_CHANOPRIVSNEEDED(channel)	\
	(" " + channel + " :You're not channel operator\r\n")									// 482
# define  ERR_UMODEUNKNOWNFLAG(mode) \
	(" :Unknown " + mode + " flag \r\n")													// 501
# define  ERR_USERSDONTMATCH \
	(" :Cannot change mode for other users \r\n")											// 502


#endif
