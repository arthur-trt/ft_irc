/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:39:29 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/23 18:32:37 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.hpp"
#include "commands.hpp"
#include "utils.hpp"
#include "IRC.Class.hpp"
#include <map>

void	loop (IRC *server)
{
	std::pair<int, std::string>				in_connection;
	std::pair<int, std::string>				buffer;
	std::map<int, std::string>				cmd_in;
	std::map<int, std::string>::iterator	it_cmd;
	std::map<int, std::string>::iterator	old_it;
	bool									looping = true;

	while (looping)
	{
		server->_tcp.pending_activity();
		in_connection = server->_tcp.incoming_connection();
		if (in_connection.first != 0)
		{
			server->add_user(in_connection.first, in_connection.second);
			if (server->get_password() == "")
			{
				server->get_user(in_connection.first)->_pass_send = true;
			}
		}
		buffer = server->_tcp.receive_data();
		if (buffer.first != 0)
		{
			if (buffer.second == "Disconnected\n")
			{
				server->remove_user(buffer.first);
			}
			else if (buffer.second == "STOP_SERVER\n" || buffer.second == "STOP_SERVER\r\n")
			{
				looping = false;
			}
			else
			{
				cmd_in[buffer.first].append(buffer.second);
			}
		}
		it_cmd = cmd_in.begin();
		while (it_cmd != cmd_in.end())
		{
			if (it_cmd->second.find_first_of("\n") != std::string::npos)
			{
				cmd_parse(it_cmd->second, server, server->get_user(it_cmd->first));
				old_it = it_cmd;
				it_cmd++;
				cmd_in.erase(old_it);
			}
			else
			{
				it_cmd++;
			}
		}
		server->_tcp.send_buffer();
	}
}

int	main(int argc, char **argv)
{
	std::string	password;
	int			port;

	port = (argc >= 2) ? std::atoi(argv[1]) : PORT;
	password = (argc == 3) ? argv[2] : "";

	IRC	server(port, password);

	loop (&server);

	return (0);
}
