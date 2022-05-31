/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_who.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:37:24 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/31 13:32:09 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <cctype>
#include "utils.hpp"
#include "IRC.Class.hpp"
#include "User.Class.hpp"
#include "functions.hpp"

/**
 * http://chi.cs.uchicago.edu/chirc/assignment3.html#who
 * :master.ircgod.com 352 a * userart 87.88.174.183 master.ircgod.com arthur H :0 Unknown
 */

//static bool	valid_args ( IRC *serv, User *user, std::string & args )
//{

//}

static void	who_helper ( IRC *serv, User *user, std::string & args )
{
	std::string	answer;

	answer.append(":");
	answer.append(serv->_tcp.getHostname());
	answer.append(" ");
	answer.append("352");
	answer.append(" ");
	if (user->_nick_name == "")
		answer.append("*");
	else
		answer.append(user->_nick_name);
	answer.append(" ");
	answer.append(args);
	answer.append("\r\n");
	serv->_tcp.add_to_buffer(std::make_pair(user->_fd, answer));
}

void	cmd_who ( IRC *serv, User *user, std::string & args )
{
	std::string	answer;

	if (args == "0")
		args = "*";
	if (args.find_first_of(CHAN_FIRST) != 0)
	{
		std::list<User *>			res;
		std::list<User *>::iterator	it;

		res = user_masks(serv, args);
		it = res.begin();
		while (it != res.end())
		{
			answer =	"* " + (*it)->_user_name + " " + (*it)->_hostname
						+ " " + serv->_tcp.getHostname() + " " + (*it)->_nick_name
						+ " H :0 " + (*it)->_real_name;
			who_helper(serv, user, answer);
			it++;
		}
		serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(315, serv, user, args)));
	}
	else
	{
		std::list<Channel *>				res;
		std::list<Channel *>::iterator		it_chan;
		std::map<User *, bool>				users;
		std::map<User *, bool>::iterator	it_users;

		res = channel_masks(serv, args);
		it_chan = res.begin();
		while (it_chan != res.end())
		{
			users = (*it_chan)->getUsers();
			it_users = users.begin();
			while (it_users != users.end())
			{
				answer = (*it_chan)->getName() + " " + it_users->first->_user_name + " " + it_users->first->_hostname
						+ " " + serv->_tcp.getHostname() + " " + it_users->first->_nick_name
						+ " H :0 " + it_users->first->_real_name;
				who_helper(serv, user, answer);
				it_users++;
			}
			it_chan++;
		}
		serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(315, serv, user, args)));
	}
}
