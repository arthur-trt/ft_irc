/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCPServer.Class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:34:21 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/06 16:25:40 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "TCPServer.Class.hpp"
# include "utils.hpp"

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

	//std::memset(&_address, 0, sizeof(_address));
	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = INADDR_ANY;
	_address.sin_port = htons(port);

	if (bind(_main_socket, (struct sockaddr *)&_address, sizeof(_address)) < 0)
	{
		std::cerr << std::strerror(errno) << std::endl;
		exit (EXIT_FAILURE);
	}
	std::cout << "Listener on port " << port << std::endl;
	if (listen(_main_socket, 5) < 0)
	{
		debug("listen");
		exit(EXIT_FAILURE);
	}
}

void		TCPServer::pending_activity ( void )
{
	int	max_sd;

	FD_ZERO(&_listen_socket);
	FD_SET(_main_socket, &_listen_socket);
	max_sd = _main_socket;

	for (size_t i = 0; i < MAX_CLIENTS_CONNECTION; i++)
	{
		if (_clients_socket[i] > 0)
			FD_SET(_clients_socket[i], &_listen_socket);
		if (_clients_socket[i] > max_sd)
			max_sd = _clients_socket[i];
	}

	if ((select( max_sd + 1, &_listen_socket, NULL, NULL, NULL) < 0
		&& (errno != EINTR)))
	{
		debug("select");
		std::cerr << std::strerror(errno) << std::endl;
	}
}

int		TCPServer::incoming_connection ( void )
{
	int	new_socket;
	socklen_t	addr_len = sizeof(_address);

	if (FD_ISSET(_main_socket, &_listen_socket))
	{
		new_socket = accept(_main_socket, (struct sockaddr *)&_address, &addr_len);
		if (new_socket < 0)
		{
			debug("accept");
			std::cerr << std::strerror(errno) << std::endl;
			exit(EXIT_FAILURE);
		}
		std::cout	<< "New connection." << std::endl
					<< "\tsocket fd : " << new_socket << std::endl
					<< "\tip : " << inet_ntoa(_address.sin_addr) << std::endl
					<< "\tport : " << ntohs(_address.sin_port) << std::endl;
		if (send(new_socket, MOTD, std::strlen(MOTD), 0) != std::strlen(MOTD))
		{
			std::cerr << "Error when sending MOTD" << std::endl;
		}
		for (size_t i = 0; i < MAX_CLIENTS_CONNECTION; i++)
		{
			if (_clients_socket[i] == 0)
			{
				_clients_socket[i] = new_socket;
				return (new_socket);
			}
		}
	}
	return (0);
}
