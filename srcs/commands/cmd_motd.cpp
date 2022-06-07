/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_motd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:08:03 by atrouill          #+#    #+#             */
/*   Updated: 2022/06/07 18:38:36 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPL.hpp"
#include "utils.hpp"
#include "IRC.Class.hpp"
#include "commands.hpp"
#include "functions.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

void	cmd_motd ( IRC *serv, User *user, std::string & args )
{
	if (args !=  "")
	{
		if (!pattern_match(serv->_tcp.getHostname(), args))
		{
			return ;
		}
	}

	std::fstream	motd_file;

	debug("Trying to open %s", MOTD_FILE);
	motd_file.open(MOTD_FILE, std::ios::in);
	std::string line;
	if (motd_file && motd_file.is_open())
	{
		serv->_tcp.add_to_buffer(std::make_pair(
			user->_fd,
			send_rpl(375, serv, user, SERVERNAME)
		));
		while (getline(motd_file, line))
		{
			serv->_tcp.add_to_buffer(std::make_pair(
				user->_fd,
				send_rpl(372, serv, user, line)
			));
		}
		serv->_tcp.add_to_buffer(std::make_pair(
			user->_fd,
			send_rpl(376, serv, user)
		));
		motd_file.close();
	}
	else
	{
		serv->_tcp.add_to_buffer(std::make_pair(
			user->_fd,
			send_rpl(422, serv, user)
		));
	}
}
