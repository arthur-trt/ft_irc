/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nick.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:14:16 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/20 17:45:02 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <cctype>
#include "utils.hpp"
#include "IRC.Class.hpp"
#include "User.Class.hpp"
#include "functions.hpp"

static bool	is_valid_nickname ( std::string const & nick_name )
{
	if (nick_name.length() > 9)
		return (false);
	if (nick_name.find_first_of(SPECIALS, 0) == std::string::npos
		&& isalpha(nick_name[0]) == 0)
		return (false);
	for (size_t i = 1; i < nick_name.length(); i++)
	{
		if (nick_name.find_first_of(SPECIALS, i) == std::string::npos
			&& isalnum(nick_name[i]) == 0
			&& nick_name[i] != '-')
		{
			return (false);
		}
	}
	return (true);
}

static bool	valid_args ( IRC *serv, User *user, std::string & args )
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
	if (!is_valid_nickname(args))
	{
		serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(432, serv, user, args)));
		return (false);
	}
	return (true);
}

void	cmd_nick ( IRC *serv, User *user, std::string & args )
{
	std::string	answer;
	std::string old_nick;

	if (valid_args(serv, user, args)  && user->_pass_send == true)
	{
		old_nick = user->_nick_name;
		user->_nick_name = args;
		if (old_nick != "")
		{
			answer.append(user_answer(old_nick, user->_user_name, user->_hostname));
			answer.append("NICK ");
			answer.append(args);
			answer.append("\r\n");

			serv->send_everyone(answer);
		}
		if (user->_user_name != "" && user->_connected == false)
		{
			user->_connected = true;
			serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(1, serv, user)));
			serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(2, serv, user)));
			serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(3, serv, user)));
			serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(4, serv, user)));
		}
	}
}
