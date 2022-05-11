/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:07:36 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/11 18:26:19 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include "commands.hpp"
#include "TCPServer.Class.hpp"
#include "User.Class.hpp"
#include <vector>
#include <string>

class TCPServer;
class User;

int		cmd_parse ( std::string entry, TCPServer *serv, User *user )
{
	std::vector<std::string>	commands;

	commands = ft_split(entry, "\r\n");
	while (commands.size())
	{
		debug("Receive %s", commands.front().c_str());
		std::string	tmp = ltrim_copy(commands.front());
		size_t	pos = tmp.find_first_of(' ');

		std::string	cmd, args;

		cmd = trim_copy(tmp.substr(0, pos));
		str_upper(cmd);
		args = trim_copy(tmp.substr(pos, tmp.length()));

		if (cmd == "NICK")
		{
			cmd_nick(serv, user, args);
		}
		else if (cmd == "USER")
		{
			cmd_user(serv, user, args);
		}
		commands.erase(commands.begin());
	}
	return (0);
}
