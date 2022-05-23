/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:07:36 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/23 16:59:24 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include "commands.hpp"
#include "IRC.Class.hpp"
#include "User.Class.hpp"
#include "functions.hpp"
#include <vector>
#include <string>


int		cmd_parse ( std::string entry, IRC *serv, User *user )
{
	std::vector<std::string>	commands;
	IRC::command				cmd_ptr;

	commands = ft_split(entry, "\n");
	while (commands.size())
	{
		debug("Receive %s", commands.front().c_str());
		std::string	tmp = ltrim_copy(commands.front());
		size_t	pos = tmp.find_first_of(' ');

		std::string	cmd, args;

		if (pos != std::string::npos)
		{
			cmd = trim_copy(tmp.substr(0, pos));
			args = trim_copy(tmp.substr(pos, tmp.length()));
		}
		else
		{
			cmd = trim_copy(entry);
			args = "";
		}
		str_upper(cmd);
		cmd_ptr = serv->get_cmd(cmd);
		if (cmd_ptr != &cmd_not_found)
			cmd_ptr(serv, user, args);
		else
			cmd_ptr(serv, user, cmd);
		commands.erase(commands.begin());
	}
	return (0);
}
