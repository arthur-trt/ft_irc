/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.Class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldes-cou <ldes-cou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:48:17 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/25 15:30:08 by ldes-cou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
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

Channel::~Channel ( void )
{
	std::cout	<< "Channel " << this->_name <<  " deleted !" << std::endl;
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

/**
 * @brief Remove a user of the channel. Delete the channel if member_counts is 0
 *
 * @param user User to remove
 * @return true	If the user have been actuallye remove
 * @return false If the user was not in the channel
 */
bool				Channel::kickUser ( User * user )
{
	std::map<User *, bool>::iterator	it;

	it = this->_joined_user.find(user);
	if (it != this->_joined_user.end())
	{
		it->first->_channel_joined.remove(this);
		this->_joined_user.erase(user);
		this->_members_count--;
		return (true);
	}
	return (false);
}

/**
 * @brief Same as kickUser, but don't change anything on the list of joined_user on the User instance
 *
 * @param user User to remove
 * @return true	If the user have been actuallye remove
 * @return false If the user was not in the channel
 */
bool				Channel::removeUser ( User * user )
{
	std::map<User *, bool>::iterator	it;

	it = this->_joined_user.find(user);
	if (it != this->_joined_user.end())
	{
		this->_joined_user.erase(user);
		this->_members_count--;
		return (true);
	}
	return (false);
}

/**
 * @brief Send a message to all users in a channel except the sender
 *
 * @param serv IRC server instance
 * @param sender Pointer to the sender
 * @param msg Message to send
 */
void				Channel::send ( IRC * serv, User * sender, std::string msg )
{
	std::map<User *, bool>::iterator	it;

	it = this->_joined_user.begin();
	while (it != this->_joined_user.end())
	{
		if (it->first != sender)
		{
			debug("Send to : %s", it->first->_nick_name.c_str());
			serv->_tcp.add_to_buffer(std::make_pair(it->first->_fd, msg));
		}
		it++;
	}
}

/**
 * @brief Send a message to all users connected to a channel
 *
 * @param serv IRC serv
 * @param msg Message to send
 */
void				Channel::send_all ( IRC * serv, std::string msg )
{
	std::map<User *, bool>::iterator	it;

	it = this->_joined_user.begin();
	while (it != this->_joined_user.end())
	{
		debug("Send to : %s", it->first->_nick_name.c_str());
		serv->_tcp.add_to_buffer(std::make_pair(it->first->_fd, msg));
		it++;
	}
}

const std::map<User *, bool> &	Channel::getUsers ( void ) const
{
	return (this->_joined_user);
}

const std::string &				Channel::getTopic ( void ) const
{
	return (this->_topic);
}

void							Channel::setTopic ( std::string topic )
{
	this->_topic = topic;
}

bool							Channel::userIsIn ( User * const & user ) const
{
	if (this->_joined_user.count(user) == 1)
		return (true);
	return (false);
}

bool							Channel::userIsIn ( const std::string & user ) const
{
	std::map<User *, bool>::const_iterator	it;

	it = this->_joined_user.begin();
	while (it != this->_joined_user.end())
	{
		if (it->first->_nick_name == user)
			return (true);
		it++;
	}
	return (false);
}

const std::pair<User *, bool>  Channel::getUser ( User * const & user ) const
{
	std::map<User *, bool>::const_iterator	it;

	it = this->_joined_user.find(user);
	return (*it);
}

size_t					Channel::getMembersCount ( void ) const
{
	return (this->_members_count);
}


bool						Channel::isBanned ( User * const & user ) const
{
	std::vector<User *>::const_iterator	it;

	it = this->_banned_user.begin();
	while (it != this->_banned_user.end())
	{
		if ((*it)->_nick_name == user->_nick_name)
			return (true);
		it++;
	}
	return (false);
}
