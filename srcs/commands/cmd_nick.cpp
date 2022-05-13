/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nick.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:14:16 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/12 21:22:57 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include "utils.hpp"
#include "IRC.Class.hpp"
#include "User.Class.hpp"

static bool	parsing ( IRC *serv, User *user, std::string args )
{
	
}

int		cmd_nick ( IRC *serv, User *user, std::string args )
{
	std::string	answer;
	std::string old_nick;

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

	return (0);
}
