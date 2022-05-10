/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.Class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 11:39:06 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/10 12:15:50 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.Class.hpp"
#include "utils.hpp"

User::User ( void )
{
	debug("Empty user constructor");
}

User::User ( const std::string & host_name, const int fd ) :
	_host_name(host_name),
	_fd(fd)
{
	_user_name = "";
	_nick_name = "";
	_host_name = "";
	debug("user fd constructor called");
}

User::User ( const std::string & user_name, const std::string & nick_name, const std::string & host_name, const int fd ) :
	_user_name(user_name),
	_nick_name(nick_name),
	_host_name(host_name),
	_fd(fd)
{
	debug("User constructor for %s", _user_name.c_str());
}

User::User ( const User & src ) :
	_user_name(src._user_name),
	_nick_name(src._nick_name),
	_host_name(src._host_name),
	_fd(src._fd)
{
	debug("Copy constructor called");
}

User&	User::operator= ( const User & rhs )
{
	if (this != &rhs)
	{
		this->_fd = rhs._fd;
		this->_user_name = rhs._user_name;
		this->_nick_name = rhs._nick_name;
	}
	return (*this);
}

User::~User ( void )
{
	_fd = 0;
	debug("User destructor for %s", _user_name.c_str());
}
