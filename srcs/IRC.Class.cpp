/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.Class.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:28:02 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/12 17:45:36 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "IRC.Class.hpp"

IRC::IRC ( int port ) :
	_tcp(port)
{

}

IRC::~IRC ( void )
{
	std::map<int, User*>::iterator				it_u = this->_connected_user.begin();
	std::map<std::string, Channel*>::iterator	it_c = this->_channels.begin();
	
	while (it_u != this->_connected_user.end())
	{
		delete (it_u->second);
		it_u++;
	}
	while (it_c != this->_channels.end())
	{
		delete (it_c->second);
		it_c++;
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

void	IRC::create_channel ( std::string & name, User * chan_operator )
{
	Channel*	tmp = new Channel(this->_tcp, name, chan_operator);

	this->_channels.insert(std::make_pair(name, tmp));
}

void	IRC::remove_channel ( std::string & name )
{
	delete this->_channels[name];
	this->_channels.erase(name);
}