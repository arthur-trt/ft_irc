/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.Class.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:28:02 by atrouill          #+#    #+#             */
/*   Updated: 2022/06/04 11:54:16 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "IRC.Class.hpp"
# include "utils.hpp"
# include "commands.hpp"

/**
 * @brief Construct a new IRC::IRC object
 *
 * @param port	Listen port for the tcp server
 */
IRC::IRC ( int port, std::string password ) :
	_tcp(port),
	_password(password)
{
	this->build_commands_map();
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
 * @brief Get the password of a IRC serv
 *
 * @return The IRC password
 */
const std::string &		IRC::get_password ( void ) const
{
	return (this->_password);
}

/**
 * @brief Function only called by the constructor for build the command map
 *
 */
void	IRC::build_commands_map ( void )
{
	this->_available_command.insert(std::make_pair("USER", &cmd_user));
	this->_available_command.insert(std::make_pair("NICK", &cmd_nick));
	this->_available_command.insert(std::make_pair("PASS", &cmd_pass));
	this->_available_command.insert(std::make_pair("CAP", &cmd_ignore));
	this->_available_command.insert(std::make_pair("JOIN", &cmd_join));
	this->_available_command.insert(std::make_pair("PRIVMSG", &cmd_privmsg));
	this->_available_command.insert(std::make_pair("NAMES", &cmd_names));
	this->_available_command.insert(std::make_pair("PING", &cmd_ping));
	this->_available_command.insert(std::make_pair("TOPIC", &cmd_topic));
	this->_available_command.insert(std::make_pair("PART", &cmd_part));
	this->_available_command.insert(std::make_pair("MODE", &cmd_mode));
	this->_available_command.insert(std::make_pair("QUIT", &cmd_quit));
	this->_available_command.insert(std::make_pair("NOTICE", &cmd_notice));
	this->_available_command.insert(std::make_pair("KICK", &cmd_kick));
	this->_available_command.insert(std::make_pair("MODE", &cmd_kick));
	this->_available_command.insert(std::make_pair("WHO", &cmd_who));
	this->_available_command.insert(std::make_pair("LIST", &cmd_list));
	this->_available_command.insert(std::make_pair("INVITE", &cmd_invite));
	this->_available_command.insert(std::make_pair("OPER", &cmd_oper));
}

/**
 * @brief Get the CPP function according to IRC Commands
 *
 * @param command typedef of function pointer used by command
 * @return a pointer function
 */
IRC::command	IRC::get_cmd ( const std::string & command ) const
{
	std::map<std::string, IRC::command>::const_iterator	it;

	debug("Command asked : %s", command.c_str());
	it = this->_available_command.find(command);
	if (it != this->_available_command.end())
	{
		return (it->second);
	}
	return (&cmd_not_found);
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
std::pair<bool, User *>	IRC::get_user ( std::string const & nick_name ) const
{
	std::map<int, User*>::const_iterator	it = this->_connected_user.begin();

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
Channel*	IRC::create_channel ( std::string & name, User * chan_operator )
{
	std::map<std::string, Channel*>::iterator					it;
	std::pair<std::map<std::string, Channel*>::iterator, bool>	res;
	Channel*	tmp = new Channel(this->_tcp, name, chan_operator);

	res = this->_channels.insert(std::make_pair(name, tmp));
	if (res.second)
	{
		return ((res.first->second));
	}
	return (u_nullptr);
}

/**
 * @brief Remove and deallocate channel
 * Undefined if channel doesn't exist
 *
 * @param name channel name
 */
void	IRC::remove_channel ( const std::string & name )
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
const std::pair<bool, Channel*> IRC::get_channel ( std::string & name ) const
{
	std::map<std::string, Channel*>::const_iterator	it = this->_channels.find(name);

	if (it != this->_channels.end())
	{
		return (std::make_pair(true, it->second));
	}
	return (std::make_pair(false, u_nullptr));
}

/**
 * @brief Get all the channel on the server
 *
 * @return Map of channels. First is name of the channel, second pointer to the channel
 */
const std::map<std::string, Channel*> & IRC::get_channel ( void ) const
{
	return (this->_channels);
}

void						IRC::send_everyone ( const std::string & msg )
{
	std::map<int, User*>::const_iterator	it;

	it = this->_connected_user.begin();
	while (it != this->_connected_user.end())
	{
		if (it->second->_connected == true)
		{
			this->_tcp.add_to_buffer(std::make_pair(it->first, msg));
		}
		++it;
	}
}

const std::map<int, User*> &		IRC::get_user ( void ) const
{
	return (this->_connected_user);
}
