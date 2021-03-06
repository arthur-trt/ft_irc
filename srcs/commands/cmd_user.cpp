/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_user.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:55:04 by atrouill          #+#    #+#             */
/*   Updated: 2022/06/09 12:22:45 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPL.hpp"
#include "utils.hpp"
#include "IRC.Class.hpp"
#include "commands.hpp"
#include "functions.hpp"

static bool	valid_args ( IRC *serv, User *user, std::string args )
{
	std::vector<std::string>	parsed;

	if (args.find(':') == std::string::npos || args.find(':') == args.length() - 1)
	{
		serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(461, serv, user, "USER")));
		return (false);
	}
	parsed = ft_split(args.substr(0, args.find(':')), " ");
	if (parsed.size() != 3)
	{
		serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(461, serv, user, "USER")));
		return (false);
	}
	if (user->_user_name != "" || user->_real_name != "")
	{
		serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(462, serv, user)));
		return (false);
	}
	return (true);
}

void	cmd_user ( IRC *serv, User *user, std::string & args )
{
	std::vector<std::string>	parsed;

	if (valid_args(serv, user, args) && user->_pass_send == true)
	{
		parsed = ft_split(args, ":");
		user->_real_name = trim_copy(parsed[1]);
		parsed = ft_split(args, " ");
		user->_user_name = trim_copy(parsed[0]);
		if (user->_nick_name != "" && user->_connected == false)
		{
			user->_connected = true;
			serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(1, serv, user)));
			serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(2, serv, user)));
			serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(3, serv, user)));
			serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(4, serv, user)));
			std::string		tmp = "";
			cmd_motd(serv, user, tmp);
		}
	}
}
