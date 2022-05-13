/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:03:26 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/13 11:12:09 by atrouill         ###   ########.fr       */
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
	(" :" SERVERNAME " " VERSION "aiwroOs OovaimnpsrtklbeI\r\n")							//004


# define ERR_NONICKNAMEGIVEN			\
	(" :No nickname given\r\n")																// 431
# define ERR_NICKNAMEINUSE(nick)		\
	(" " + nick + " :Nickname is already in use\r\n")										// 433

#endif
