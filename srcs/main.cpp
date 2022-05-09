/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:39:29 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/09 14:52:59 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.hpp"
#include "utils.hpp"
#include "User.Class.hpp"
#include "TCPServer.Class.hpp"
#include <map>

void	loop (TCPServer *server)
{
	int							tmp_fd;
	std::pair<int, std::string>	buffer;
	std::map<int, User>			users;

	while (true)
	{
		server->pending_activity();
		tmp_fd = server->incoming_connection();
		if (tmp_fd != 0)
		{
			User	tmp(tmp_fd);
			users.insert(std::make_pair(tmp_fd, tmp));
		}
		buffer = server->receive_data();
		if (buffer.first != 0)
		{
			if (buffer.second == "Disconnected\n")
			{
				users.erase(buffer.first);
			}
			if (users[buffer.first]._nick_name == "")
			{
				std::cout << trim(buffer.second) << " will be your nick_name" << std::endl;
				users[buffer.first]._nick_name = trim_copy(buffer.second);
			}
			else
			{
				std::cout << users[buffer.first]._nick_name << " say : ";
				std::cout << buffer.second;
			}
		}
	}
}

int	main(int argc, char **argv)
{
	int	port;

	port = (argc == 2) ? std::atoi(argv[1]) : PORT;

	TCPServer	server(port);

	loop (&server);

	return (0);
}
