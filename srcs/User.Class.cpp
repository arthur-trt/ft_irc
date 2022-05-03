/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.Class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 11:39:06 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/03 16:48:18 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.Class.hpp"
#include "utils.hpp"

User::User ( void )
{
	debug("Empty user constructor");
}

User::User ( const std::string & user_name, const std::string & nick_name, const int fd ) :
	_user_name(user_name),
	_nick_name(nick_name),
	_fd(fd)
{
	debug("User constructor for %s", _user_name.c_str());
}

User::~User ( void )
{
	_fd = 0;
	debug("User destructor for %s", _user_name.c_str());
}
