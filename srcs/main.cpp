/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:39:29 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/11 18:21:17 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.hpp"
#include "commands.hpp"
#include "utils.hpp"
#include "User.Class.hpp"
#include "TCPServer.Class.hpp"
#include <map>

void	loop (TCPServer *server)
{
	std::pair<int, std::string>		in_connection;
	std::pair<int, std::string>		buffer;
	std::map<int, User>				users;
	std::map<int, User>::iterator	it;

	while (true)
	{
		server->pending_activity();
		in_connection = server->incoming_connection();
		if (in_connection.first != 0)
		{
			User	tmp(in_connection.second, in_connection.first);
			users.insert(std::make_pair(in_connection.first, tmp));
		}
		buffer = server->receive_data();
		if (buffer.first != 0)
		{
			if (buffer.second == "Disconnected\n")
			{
				users.erase(buffer.first);
			}
			else
			{
				cmd_parse(buffer.second, server, &(users[buffer.first]));
			}
			//else if (users[buffer.first]._nick_name == "")
			//{
			//	std::cout << trim_copy(buffer.second) << " will be your nick_name" << std::endl;
			//	users[buffer.first]._nick_name = trim_copy(buffer.second);
			//}
			//else
			//{
			//	it = users.begin();

			//	while (it != users.end())
			//	{
			//		if (it->second._fd != buffer.first)
			//		{
			//			std::string	msg = "";
			//			msg.append(users[buffer.first]._nick_name);
			//			msg.append(" say: ");
			//			msg.append(buffer.second);

			//			send(it->second._fd, msg.c_str(), msg.size(), 0);
			//		}
			//		it++;
			//	}
			//	// // Command goes here
			//	std::cout << users[buffer.first]._nick_name << " say : ";
			//	std::cout << buffer.second;
			//}
		}
		server->send_buffer();
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
