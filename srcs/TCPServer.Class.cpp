/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCPServer.Class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:34:21 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/05 16:56:52 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "TCPServer.Class.hpp"

TCPServer::TCPServer( void )
{
}


TCPServer::TCPServer ( int port )
{
	int		optval = 1;

	std::memset(&_clients_socket, 0, MAX_CLIENTS_CONNECTION);

	if ((_main_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		std::cerr << std::strerror(errno) << std::endl;
		exit (EXIT_FAILURE);
	}
	if (setsockopt(_main_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
	{
		std::cerr << std::strerror(errno) << std::endl;
		exit (EXIT_FAILURE);
	}

	std::memset(&_address, 0, sizeof(_address));
	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = INADDR_ANY;
	_address.sin_port = htons(port);

	if (bind(_main_socket, (struct sockaddr *)&_address, sizeof(_address)) < 0)
	{
		std::cerr << std::strerror(errno) << std::endl;
		exit (EXIT_FAILURE);
	}
}

int		TCPServer::pending_socket ( void )
{
	
}
