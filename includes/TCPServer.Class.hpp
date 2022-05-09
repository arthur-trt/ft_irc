/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCPServer.Class.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:50:26 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/09 12:24:41 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TCPSERVER_CLASS_HPP
# define TCPSERVER_CLASS_HPP

# include "config.hpp"

# include <unistd.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <sys/time.h>
# include <algorithm>
# include <cstring>
# include <cerrno>

class TCPServer
{
	private:
		struct sockaddr_in	_address;
		int					_clients_socket[MAX_CLIENTS_CONNECTION];
		fd_set				_listen_socket;
		int					_main_socket;

	public:
		TCPServer( void );

		TCPServer ( int port = PORT );

		void						pending_activity ( void );

		int							incoming_connection ( void );

		std::pair<int, std::string>	receive_data ( void );

};

#endif
