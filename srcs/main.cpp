/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:39:29 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/12 15:54:24 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.hpp"
#include "commands.hpp"
#include "utils.hpp"
#include "IRC.Class.hpp"
#include <map>

void	loop (IRC *server)
{
	std::pair<int, std::string>		in_connection;
	std::pair<int, std::string>		buffer;
	std::map<int, User>::iterator	it;

	while (true)
	{
		server->_tcp.pending_activity();
		in_connection = server->_tcp.incoming_connection();
		if (in_connection.first != 0)
		{
			server->add_user(in_connection.first, in_connection.second);
		}
		buffer = server->_tcp.receive_data();
		if (buffer.first != 0)
		{
			if (buffer.second == "Disconnected\n")
			{
				server->remove_user(buffer.first);
			}
			else if (buffer.second == "QUIT\n")
			{
				break;
			}
			else
			{
				cmd_parse(buffer.second, server, server->get_user(buffer.first));
			}
		}
		server->_tcp.send_buffer();
	}
}

int	main(int argc, char **argv)
{
	int	port;

	port = (argc == 2) ? std::atoi(argv[1]) : PORT;

	IRC	server(port);

	loop (&server);

	return (0);
}
