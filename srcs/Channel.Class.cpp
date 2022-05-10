/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.Class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:48:17 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/10 14:21:44 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include "Channel.Class.hpp"

/**
 * @brief Construct a new Channel:: Channel object
 *
 * @param server Main TCPServer
 * @param name	Channel name
 * @param chan_operator Channel operator (user who created channel)
 */
Channel::Channel ( TCPServer & server, const std::string & name, User * chan_operator ) :
	_server(server),
	_name(name),
	_members_count(0)
{
	std::cout	<< "New channel !" 									<< std::endl
				<< "\tName : " << name								<< std::endl
				<< "\tOperator : " << (chan_operator)->_user_name	<< std::endl;
	this->_joined_user.insert(std::make_pair(chan_operator, true));
	this->_members_count++;
}

/**
 * @brief Construct a new Channel:: Channel object
 *
 * @param src Channel to copy
 */
Channel::Channel ( const Channel & src ) :
	_server(src._server),
	_name(src._name),
	_joined_user(src._joined_user),
	_members_count(src._members_count)
{
	debug("Copy constructor for Channel");
}

/**
 * @brief Assignation operator
 *
 * @param rhs
 * @return
 */
Channel &	Channel::operator= ( const Channel & rhs )
{
	if (this != &rhs)
	{
		_server = rhs._server;
		_joined_user = rhs._joined_user;
		_members_count = rhs._members_count;
	}
	return (*this);
}

/**
 * @brief Obtain channel name
 *
 * @return Channel name
 */
const std::string &	Channel::getName ( void ) const
{
	return (this->_name);
}

/**
 * @brief Add a user to the channel
 *
 * @param user User instance to add
 * @return true	If the user have been added
 * @return false It the user is already present
 */
bool				Channel::addUser ( User * user )
{
	if (this->_joined_user.count(user) == 0)
	{
		this->_joined_user.insert(std::make_pair(user, false));
		this->_members_count++;
		return (true);
	}
	return (false);
}

bool				Channel::kickUser ( User * user )
{
	if (this->_joined_user.count(user) != 0)
	{
		this->_joined_user.erase(user);
		this->_members_count--;
		if (this->_members_count == 0)
		{
			// delete channel
		}
		return (true);
	}
	return (false);
}
