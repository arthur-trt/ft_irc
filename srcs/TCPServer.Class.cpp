/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCPServer.Class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:34:21 by atrouill          #+#    #+#             */
/*   Updated: 2022/06/10 11:12:23 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "TCPServer.Class.hpp"
# include "utils.hpp"

extern sig_atomic_t	g_looping;

/**
 * @brief Construct a new TCPServer::TCPServer object
 *
 * @param port Port to listen
 */
TCPServer::TCPServer ( int port )
{
	int		optval = 1;
	char	hostname[1024];

	gethostname(hostname, 1024);
	this->_hostname = std::string(hostname);

	std::memset(&_clients_socket, 0, MAX_CLIENTS_CONNECTION * sizeof(int));

	#if IPV6 == 1
		if ((_main_socket = socket(AF_INET6, SOCK_STREAM, 0)) == 0)
		{
			debug("Socket failed :");
			std::cerr << std::strerror(errno) << std::endl;
			exit (EXIT_FAILURE);
		}
	# else
		if ((_main_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
		{
			debug("Socket failed :");
			std::cerr << std::strerror(errno) << std::endl;
			exit (EXIT_FAILURE);
		}
	#endif
	if (setsockopt(_main_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
	{
		debug("Setsockoption failed :");
		std::cerr << std::strerror(errno) << std::endl;
		exit (EXIT_FAILURE);
	}

	//std::memset(&_address, 0, sizeof(_address));


	#if IPV6 == 1
		_address.sin6_family = AF_INET6;
		_address.sin6_addr = in6addr_any;
		_address.sin6_port = htons(port);
	# else
		_address.sin_family = AF_INET;
		_address.sin_addr.s_addr = INADDR_ANY;
		_address.sin_port = htons(port);
	#endif

	if (bind(_main_socket, (struct sockaddr *)&_address, sizeof(_address)) < 0)
	{
		debug("bind");
		std::cerr << std::strerror(errno) << std::endl;
		exit (EXIT_FAILURE);
	}
	std::cout << "Listener on port " << port << std::endl;
	if (listen(_main_socket, MAX_CLIENTS_CONNECTION) < 0)
	{
		debug("listen");
		exit(EXIT_FAILURE);
	}
}

/**
 * @brief Wait until activity is detected inside the socket
 *
 */
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

/**
 * @brief Accept new connection and assigne a port and a socket to it
 *
 * @return pair->first is the socket fd. pair->second is the hostname
 */
std::pair<int, std::string>	TCPServer::incoming_connection ( void )
{
	int			new_socket;
	char		_host_name[1024];
	socklen_t	addr_len = sizeof(_address);

	if (g_looping && FD_ISSET(_main_socket, &_listen_socket))
	{
		new_socket = accept(_main_socket, (struct sockaddr *)&_address, &addr_len);
		if (new_socket < 0)
		{
			debug("accept");
			std::cerr << std::strerror(errno) << std::endl;
			exit(EXIT_FAILURE);
		}
		fcntl(new_socket, F_SETFL, O_NONBLOCK);
		getnameinfo((struct sockaddr *)&_address, addr_len, _host_name, 1024, NULL, 0, 0);

		#if IPV6 == 1
			char	ip[INET6_ADDRSTRLEN];
			inet_ntop(AF_INET6, &(_address.sin6_addr), ip, INET6_ADDRSTRLEN);
			std::cout	<< "New connection." << std::endl
						<< "\tsocket fd : " << new_socket << std::endl
						<< "\tip : " << ip << std::endl
						<< "\tport : " << ntohs(_address.sin6_port) << std::endl
						<<	"\thostname : " << _host_name << std::endl;
		# else
			char	ip[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &(_address.sin_addr), ip, INET_ADDRSTRLEN);
			std::cout	<< "New connection." << std::endl
						<< "\tsocket fd : " << new_socket << std::endl
						<< "\tip : " << ip << std::endl
						<< "\tport : " << ntohs(_address.sin_port) << std::endl
						<<	"\thostname : " << _host_name << std::endl;
		#endif

		for (size_t i = 0; i < MAX_CLIENTS_CONNECTION; i++)
		{
			if (_clients_socket[i] == 0)
			{
				_clients_socket[i] = new_socket;
				return (std::make_pair(new_socket, _host_name));
			}
		}
	}
	return (std::make_pair(0, ""));
}

/**
 * @brief Receive data from a previous accepted connection
 *
 * @return std::pair<int, std::string>
 * first is the fd from the incoming connection, second is a string with received data
 */
std::pair<int, std::string>	TCPServer::receive_data ( void )
{
	int			sd;
	int			valread;
	char		buffer[1025];
	socklen_t	addr_len = sizeof(_address);

	for (size_t i = 0; i < MAX_CLIENTS_CONNECTION; i++)
	{
		sd = this->_clients_socket[i];

		if (FD_ISSET(sd, &_listen_socket))
		{
			memset(&buffer, 0, 1025);
			valread = read(sd, buffer, 1024);
			if (valread <= 0)
			{
				getpeername(sd, (struct sockaddr *)&_address, &addr_len);
				#if IPV6 == 1
					char	ip[INET6_ADDRSTRLEN];
					inet_ntop(AF_INET6, &(_address.sin6_addr), ip, INET6_ADDRSTRLEN);
					std::cout	<< "Host disconnected." << std::endl
								<< "\tsocket fd : " << sd << std::endl
								<< "\tip : " << ip << std::endl
								<< "\tport : " << ntohs(_address.sin6_port) << std::endl;
				# else
					char	ip[INET_ADDRSTRLEN];
					inet_ntop(AF_INET, &(_address.sin_addr), ip, INET_ADDRSTRLEN);
					std::cout	<< "New connection." << std::endl
								<< "\tsocket fd : " << sd << std::endl
								<< "\tip : " << ip << std::endl
								<< "\tport : " << ntohs(_address.sin_port) << std::endl;
				#endif
				close (sd);
				_clients_socket[i] = 0;
				return (std::make_pair(sd, std::string("Disconnected\n")));
			}
			else
			{
				if (buffer[0] == '\004')
					buffer[0] = '\0';
				buffer[valread] = '\0';
				return (std::make_pair(sd, std::string(buffer)));
			}
		}
	}
	return (std::make_pair(0, std::string("")));
}

/**
 * @brief Add message to the buffer before sending
 *
 * @param buff std::pair->first is the fd where to send message. std::pair->second is the message to send
 */
void					TCPServer::add_to_buffer ( std::pair<int, std::string> buff )
{
	this->_buffer_out.insert(buff);
}

/**
 * @brief Send and flush everything in the buffer
 */
void					TCPServer::send_buffer ( void )
{
	std::map<int, std::string>::iterator	it = _buffer_out.begin();

	while (it != _buffer_out.end())
	{
		debug("Send to %d : %s", it->first, it->second.c_str());
		send(it->first, it->second.c_str(), std::strlen(it->second.c_str()), MSG_NOSIGNAL);
		it++;
	}
	_buffer_out.clear();
}

/**
 * @brief Get the server hostname
 *
 * @return server hostname
 */
const std::string &		TCPServer::getHostname ( void ) const
{
	return (this->_hostname);
}

const int &				TCPServer::getMainSocket ( void ) const
{
	return (this->_main_socket);
}

/**
 * @brief Close a connection.
 *
 * @param fd fd to close
 */
void					TCPServer::close_connection ( const int & fd )
{
	socklen_t	addr_len = sizeof(_address);

	for (size_t i = 0; i < MAX_CLIENTS_CONNECTION; i++)
	{
		if (this->_clients_socket[i] == fd)
		{
			getpeername(fd, (struct sockaddr *)&_address, &addr_len);
			#if IPV6 == 1
				char	ip[INET6_ADDRSTRLEN];
				inet_ntop(AF_INET6, &(_address.sin6_addr), ip, INET6_ADDRSTRLEN);
				std::cout	<< "Host disconnected." << std::endl
							<< "\tsocket fd : " << fd << std::endl
							<< "\tip : " << ip << std::endl
							<< "\tport : " << ntohs(_address.sin6_port) << std::endl;
			# else
				char	ip[INET_ADDRSTRLEN];
				inet_ntop(AF_INET, &(_address.sin_addr), ip, INET_ADDRSTRLEN);
				std::cout	<< "New connection." << std::endl
							<< "\tsocket fd : " << fd << std::endl
							<< "\tip : " << ip << std::endl
							<< "\tport : " << ntohs(_address.sin_port) << std::endl;
			#endif
			close(fd);
			this->_clients_socket[i] = 0;
			break;
		}
	}
}

void					TCPServer::close_server ( void )
{
	for (size_t i = 0; i < MAX_CLIENTS_CONNECTION; i++)
	{
		if (this->_clients_socket[i] != 0)
		{
			close(this->_clients_socket[i]);
			this->_clients_socket[i] = 0;
		}
	}
	close(_main_socket);
}
