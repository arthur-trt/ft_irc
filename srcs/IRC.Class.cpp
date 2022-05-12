/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.Class.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:28:02 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/12 15:57:23 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "IRC.Class.hpp"

IRC::IRC ( int port ) :
	_tcp(port)
{

}

IRC::~IRC ( void )
{
	std::map<int, User*>::iterator	it = this->_connected_user.begin();

	while (it != this->_connected_user.end())
	{
		delete (it->second);
		it++;
	}

}

void	IRC::add_user ( int fd, std::string hostname )
{
	User*	tmp = new User(hostname, fd);

	this->_connected_user.insert(std::make_pair(fd, tmp));
}

void	IRC::remove_user( int fd )
{
	delete this->_connected_user[fd];
	this->_connected_user.erase(fd);
}

User *	IRC::get_user ( int fd )
{
	return (this->_connected_user[fd]);
}
