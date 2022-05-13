/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nick.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:14:16 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/13 11:42:39 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include "utils.hpp"
#include "IRC.Class.hpp"
#include "User.Class.hpp"
#include "functions.hpp"

//static bool	is_valid_nickname ( std::string const & nick_name )
//{
//	if (nick_name.length() > 9)
//		return (false);
//	if (nick_name.find_first_of())
//}

static bool	valid_args ( IRC *serv, User *user, std::string args )
{
	debug ("Args : %s", args.c_str());
	if (args == "")
	{
		serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(431, serv, user)));
		return (false);
	}
	if (serv->get_user(args).first == true)
	{
		serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(433, serv, user, args)));
		return (false);
	}
	return (true);
}

int		cmd_nick ( IRC *serv, User *user, std::string args )
{
	std::string	answer;
	std::string old_nick;

	if (valid_args(serv, user, args))
	{
		old_nick = user->_nick_name;
		user->_nick_name = args;
		if (old_nick != "")
		{
			answer.append(user_answer(user->_nick_name, user->_user_name, user->_hostname));
			answer.append(user->_nick_name);
			answer.append(" NICK ");
			answer.append(args);
			answer.append("\r\n");

			serv->_tcp.add_to_buffer(std::make_pair(user->_fd, answer));
		}
	}
	return (0);
}
