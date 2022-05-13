/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:58:28 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/13 17:15:06 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPL.hpp"
#include "config.hpp"
#include "IRC.Class.hpp"
#include "User.Class.hpp"
#include "utils.hpp"
#include "functions.hpp"

static bool	valid_args ( IRC *serv, User *user, std::string args )
{
	if (args == "")
	{
		serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(461, serv, user, "PASS")));
		return (false);
	}
	if (user->_connected)
	{
		serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(462, serv, user)));
		return (false);
	}
	return (true);
}

void	cmd_pass ( IRC *serv, User *user, std::string & args )
{
	if (valid_args(serv, user, args))
	{
		if (args == serv->get_password())
		{
			user->_pass_send = true;	
		}
	}
}
