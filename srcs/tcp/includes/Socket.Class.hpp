/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.Class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 10:01:02 by atrouill          #+#    #+#             */
/*   Updated: 2022/04/30 10:11:25 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_CLASS_HPP
# define SOCKET_CLASS_HPP

# include <sys/socket.h>

namespace tcp
{
	class Socket
	{
		protected:
			int					_fd;
			sockaddr_storage	_addr;
				
		public:
			/**
			 * @brief Default constructor.
			 * Create an unnamed socket.
			 */
			Socket	( void );
			
			virtual ~Socket ( void );

			/**
			 * @brief Return the fd of the socket
			 * 
			 * @return Fd of the socket (-1 if not initialized) 
			 */
			int		fd ( void );
			
						
	};
}

#endif