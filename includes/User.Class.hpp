/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.Class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 11:38:28 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/11 16:19:32 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_CLASS_HPP
# define USER_CLASS_HPP

# include <string>

class User
{
	public:
		std::string		_user_name;
		std::string		_nick_name;
		std::string		_real_name;
		std::string		_host_name;
		/**
		 * Fd of the socket in use for the connection
		 */
		int		_fd;
		///**
		// * Is the user alive ?
		// */
		//bool			_alive = true;
		///**
		// * Is the user operator ?
		// */
		//bool			_isOperator;

	public:
		User ( void );

		User ( const std::string & host_name, const int fd );

		User ( const std::string & user_name, const std::string & nick_name, const std::string & _host_name, const int fd );

		User ( const User & src );

		User&	operator= ( const User & rhs );

		~User ( void );


};

#endif
