/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.Class.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:28:02 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/13 11:48:25 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "IRC.Class.hpp"
# include "utils.hpp"

/**
 * @brief Construct a new IRC::IRC object
 *
 * @param port	Listen port for the tcp server
 */
IRC::IRC ( int port ) :
	_tcp(port)
{

}

/**
 * @brief Destroy the IRC::IRC object
 * Deallocate all users and channels
 */
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

/**
 * @brief Add a new user. The User is malloc
 *
 * @param fd fd assign to the user by the tcp server
 * @param hostname hostname of the user
 */
void	IRC::add_user ( int fd, std::string hostname )
{
	User*	tmp = new User(hostname, fd);

	this->_connected_user.insert(std::make_pair(fd, tmp));
}

/**
 * @brief Deallocate and remove a given user.
 * Undefined if user doesn't exist
 *
 * @param fd fd of the user to remove
 */
void	IRC::remove_user( int fd )
{
	delete this->_connected_user[fd];
	this->_connected_user.erase(fd);
}

/**
 * @brief Get a pointer to an user
 *
 * @param fd fd of the user
 * @return User* A pointer to the user
 */
User *	IRC::get_user ( int fd )
{
	return (this->_connected_user[fd]);
}

/**
 * @brief Search an user by nickname
 *
 * @param nick_name	Nick name of the user
 * @return first will be true if user exist, false otherwise.
 * second will be a pointer to the user if exists or null_ptr otherwise
 */
std::pair<bool, User *>	IRC::get_user ( std::string const & nick_name )
{
	std::map<int, User*>::iterator		it = this->_connected_user.begin();

	while (it != this->_connected_user.end())
	{
		if (it->second->_nick_name == nick_name)
			return (std::make_pair(true, it->second));
		it++;
	}
	return (std::make_pair(false, u_nullptr));
}

/**
 * @brief Create and allocate a new channel
 *
 * @param name Channel name
 * @param chan_operator User who created the channel
 */
void	IRC::create_channel ( std::string & name, User * chan_operator )
{
	Channel*	tmp = new Channel(this->_tcp, name, chan_operator);

	this->_channels.insert(std::make_pair(name, tmp));
}

/**
 * @brief Remove and deallocate channel
 * Undefined if channel doesn't exist
 *
 * @param name channel name
 */
void	IRC::remove_channel ( std::string & name )
{
	delete this->_channels[name];
	this->_channels.erase(name);
}

/**
 * @brief Search an channel by name
 *
 * @param name Channel name
 * @return first will be true if channel exist, false otherwise.
 * second will be a pointer to the channel if exists or null_ptr otherwise
 */
std::pair<bool, Channel*>	IRC::get_channel ( std::string & name )
{
	std::map<std::string, Channel*>::iterator	it = this->_channels.find(name);

	if (it != this->_channels.end())
	{
		return (std::make_pair(true, it->second));
	}
	return (std::make_pair(false, u_nullptr));
}
