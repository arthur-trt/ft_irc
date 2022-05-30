/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.Class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldes-cou <ldes-cou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 11:39:06 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/30 18:19:38 by ldes-cou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.Class.hpp"
#include "utils.hpp"


User::User ( void )
{
	//debug("Empty user constructor");
}

User::User ( const std::string & hostname, const int fd ) :
	_hostname(hostname),
	_fd(fd)
{
	_user_name = "";
	_nick_name = "";
	_real_name = "";
	_pass_send = false;
	_connected = false;
	//available_mode = "+a+i+w+r+o+O+s";
	//debug("user fd constructor called");
}

User::User ( const std::string & user_name, const std::string & nick_name, const std::string & hostname, const int fd ) :
	_user_name(user_name),
	_nick_name(nick_name),
	_hostname(hostname),
	_fd(fd)
{
	_pass_send = false;
	_connected = false;
	//available_mode = "+a+i+w+r+o+O+s";
	//debug("User constructor for %s", _user_name.c_str());
}

User::User ( const User & src ) :
	_user_name(src._user_name),
	_nick_name(src._nick_name),
	_real_name(src._real_name),
	_hostname(src._hostname),
	_fd(src._fd),
	_pass_send(src._pass_send),
	_connected(src._connected)
{
	//available_mode = "+a+i+w+r+o+O+s";
	//debug("Copy constructor called");
}

User&	User::operator= ( const User & rhs )
{
	if (this != &rhs)
	{
		this->_fd = rhs._fd;
		this->_user_name = rhs._user_name;
		this->_real_name = rhs._real_name;
		this->_pass_send = rhs._pass_send;
		this->_connected = rhs._connected;
		this->_nick_name = rhs._nick_name;
		//this->available_mode = "+a+i+w+r+o+O+s";
	}
	return (*this);
}

User::~User ( void )
{
	std::list<Channel *>::iterator	it;

	_fd = 0;
	it = this->_channel_joined.begin();
	while (it != this->_channel_joined.end())
	{
		(*it)->removeUser(this);
		it++;
	}

	//debug("User destructor for %s", _user_name.c_str());
}

void	User::deopping(std::string params)
{
	(void)params;
	std::vector<std::string>::iterator it;
	it = std::find(_mode.begin(), _mode.end(), "+o");
	if (it != _mode.end())
	{
		_mode.erase(it);
		//on every chan ?????
	}
}
void	User::setInvisible(std::string params)
{
	(void)params;
	_mode.push_back("+i");
}

bool	User::updateMode(std::string new_mode, std::string params)
{
	typedef void (User::*Modes)(std::string params);
	const std::string chan_mode[2] = {"-o", "+i"};
    
	Modes changeMode[2] = {&User::deopping, &User::setInvisible};
	for (int i = 0; i < 2; i++)
	{
		if (chan_mode[i] == new_mode)
		{
			(this->*(changeMode[i]))(params);
			return true;
		}
	}
	std::cout << "bah..." << std::endl;
	return false;
	
}