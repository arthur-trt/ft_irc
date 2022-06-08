/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.Class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldes-cou <ldes-cou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:48:17 by atrouill          #+#    #+#             */
/*   Updated: 2022/06/08 18:50:57 by ldes-cou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include "utils.hpp"
#include "Channel.Class.hpp"
#include "masks.hpp"
#define out(x) std::cout << x << std::endl;

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
	this->_password = "";
	this->_user_limit = INT32_MAX;
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
	this->_password = "";

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
		_password = rhs._password;
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


bool		Channel::isBanned ( User * const & user ) const
{
	std::vector<std::string>::const_iterator	it;

	it = this->_banned_user.begin();
	while (it != this->_banned_user.end())
	{
		if (user_masks(user, (*it)))
			return (true);
		it++;
	}
	return (false);
}

bool					Channel::needsPass(void)
{
	std::vector<std::string>::iterator it = std::find(_mode.begin(), _mode.end(), "+k");
	if (it != _mode.end())
		return true;
	return false;
}


void	Channel::setPassword (char mode, char op, std::string password )
{
	if (op == '+')
	{
		this->_password = password;
		if (!isModeThere(mode))
			_mode.push_back("+k");
	}
	else
	{
		std::vector<std::string>::iterator kit;
		kit = std::find(_mode.begin(), _mode.end(), "k");
		if (kit != _mode.end())
			_mode.erase(kit);
	}

}

void	Channel::setOperator(char mode, char op, std::string user_name)
{
	(void)mode;
	if (op == '+')
	{
		std::vector<std::string>::iterator it;
		it = std::find(_operators.begin(), _operators.end(), user_name);
		if (it != _operators.end())
			_operators.push_back(user_name);
	}
	else if (op == '-')
	{
		std::vector<std::string>::iterator it;
		it = std::find(_operators.begin(), _operators.end(), user_name);
		if (it != _operators.end())
			_operators.erase(it);
		std::vector<std::string>::iterator kit;
		kit = std::find(_mode.begin(), _mode.end(), "o");
		if (kit != _mode.end())
			_mode.erase(kit);
	}
}

bool	Channel::isOperator(User const &user) const
{
	std::vector<std::string>::const_iterator it;
	for (it = _operators.begin(); it < _operators.end(); it++)
	{
		if (*it == user._nick_name)
		return (true);
	}
	return (false);
}

void	Channel::ban(char mode, char op, std::string params)
{
	(void)mode;
	if (op == '+')
	{
			if (params != "")
				_banned_user.push_back(params);
	}	
	if (op == '-')
	{
		if (params != "")
		{
			std::vector<std::string>::iterator it;
			it = std::find(_mode.begin(), _mode.end(), "b");
			if (it != _mode.end())
				_mode.erase(it);
			std::vector<std::string>::iterator kit;
			kit = std::find(_banned_user.begin(), _banned_user.end(), params);
			if (kit != _banned_user.end())
				_banned_user.erase(kit);
		}
	}
}
void	Channel::invite(char mode, char op, std::string params)
{
	if (op == '+')
	{
		if (!isModeThere(mode))
		{
			_mode.push_back("i");
			_invited_user.push_back(params);
		}
	}
	else if (op == '-')
	{
		std::vector<std::string>::iterator it;
		it = std::find(_mode.begin(), _mode.end(), "i");
		if (it != _mode.end())
			_mode.erase(it);
	}
}
void	Channel::limit(char mode, char op, std::string params)
{
	if (op == '+')
	{
		std::stringstream ss;
		if (!isModeThere(mode))
			_mode.push_back("l");
		ss << params;
		ss >> _user_limit;
	}
	if (op == '-')
	{
		std::vector<std::string>::iterator it;
		it = std::find(_mode.begin(), _mode.end(), "l");
		if (it != _mode.end())
			_mode.erase(it);
		_user_limit = INT32_MAX;
	}
}
bool	Channel::updateMode(std::string new_mode, std::vector<std::string> params)
{
	typedef void (Channel::*Modes)(char mode, char op, std::string arg);
	const char chan_mode[5] = {'k', 'o', 'b', 'i', 'l'};

	char op = new_mode[0];
	new_mode = &new_mode[1];
	bool ret (false);
	if (op != '+' && op != '-')
		return (ret); 
	Modes changeMode[5] = {&Channel::setPassword, &Channel::setOperator, &Channel::ban, &Channel::invite, &Channel::limit};
	for (int i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < new_mode.length(); j++)
		{
			if (chan_mode[i] == new_mode[j])
			{
				if (params.size() <= j)
					params.push_back("");
				(this->*(changeMode[i]))(new_mode[j], op, params[j]);
				ret = true;
			}
		}
	}
	return (ret);
}


void	Channel::addInvited ( std::string nickname)
{
	_invited_user.push_back(nickname);
}
bool	Channel::isModeThere(char mode)
{
	
	std::vector<std::string>::const_iterator it;
	for (it = _mode.begin(); it < _mode.end(); it++)
	{
		if (mode == (*it)[0])
			return (true);
	}
	return (false);		
}


bool	Channel::isInvited(User *user)
{
	std::vector<std::string>::iterator kit;
	kit = std::find(_mode.begin(), _mode.end(), "i");
	if (kit != _mode.end())
	{
		std::vector<std::string>::const_iterator it;
		it = std::find(_invited_user.begin(), _invited_user.end(), user->_nick_name);
		if (it != _invited_user.end())
		{
			return (true);
		}
		return (false);
	}
	return (true);
}

bool	Channel::inviteOnly() const
{
	std::vector<std::string>::const_iterator it;
	if (std::find(_mode.begin(), _mode.end(), "i") != _mode.end())
		return (true);
	return (false);
}



/****************************** 			GETTERS 			***********************************/

const size_t &				Channel::getUserLimit( void ) const
{
	return (_user_limit);
}

const std::vector<std::string> &Channel::getBannedUser( void ) const
{
	return (_banned_user);
}

const std::map<User *, bool> &	Channel::getUsers ( void ) const
{
	return (this->_joined_user);
}

const std::string &				Channel::getTopic ( void ) const
{
	return (this->_topic);
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

const std::string	Channel::getMode(void) const
{
	std::string mode_str;
	
	std::vector<std::string>::const_iterator it;
	for(it = _mode.begin(); it < _mode.end(); it++)
		mode_str += *it;
	return (mode_str);
}

const std::string &	Channel::getPassword ( void ) const
{
	return (this->_password);
}