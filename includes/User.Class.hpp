/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.Class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 11:38:28 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/03 16:46:28 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_CLASS_HPP
# define USER_CLASS_HPP

# include <string>

class User
{
	private:
		std::string		_user_name;
		std::string		_nick_name;
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

		User ( const std::string & user_name, const std::string & nick_name, const int fd );

		~User ( void );


};

#endif
