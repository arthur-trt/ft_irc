/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_join.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:27:31 by atrouill          #+#    #+#             */
/*   Updated: 2022/06/10 11:55:10 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPL.hpp"
#include "utils.hpp"
#include "IRC.Class.hpp"
#include "commands.hpp"
#include "functions.hpp"

/**
 * @todo:
 * -> Reply from the server
 * -> Error code
 * -> Channel mode
 * -> VIDA LOCA
 *
 */


/*
Command: JOIN
   Parameters: ( <channel> *( "," <channel> ) [ <key> *( "," <key> ) ] )
               / "0"

   The JOIN command is used by a user to request to start listening to
   the specific channel.  Servers MUST be able to parse arguments in the
   form of a list of target, but SHOULD NOT use lists when sending JOIN
   messages to clients.

   Once a user has joined a channel, he receives information about
   all commands his server receives affecting the channel.  This
   includes JOIN, MODE, KICK, PART, QUIT and of course PRIVMSG/NOTICE.
   This allows channel members to keep track of the other channel
   members, as well as channel modes.

   If a JOIN is successful, the user receives a JOIN message as
   confirmation and is then sent the channel's topic (using RPL_TOPIC) and
   the list of users who are on the channel (using RPL_NAMREPLY), which
   MUST include the user joining.

   Note that this message accepts a special argument ("0"), which is
   a special request to leave all channels the user is currently a member
   of.  The server will process this message as if the user had sent
   a PART command (See Section 3.2.2) for each channel he is a member
   of.

   Numeric Replies:

           ERR_NEEDMOREPARAMS    ok         ERR_BANNEDFROMCHAN	ok
           ERR_INVITEONLYCHAN    ok         ERR_BADCHANNELKEY ok
           ERR_CHANNELISFULL               	ERR_BADCHANMASK
           ERR_NOSUCHCHANNEL     ok        	ERR_TOOMANYCHANNELS
		   ERR_UNAVAILRESOURCE
           RPL_TOPIC			ok
*/

static bool	is_valid_channame ( std::string const & channel_name )
{
	if (	channel_name[0] != '#' && channel_name[0] != '&'
		&&	channel_name[0] != '+' && channel_name[0] != '!')
	{
		return (false);
	}
	for (size_t i = 1; i < channel_name.length(); i++)
	{
		if (	channel_name[i] == ':' || channel_name[i] == ','
			||	channel_name[i] == ' ' || channel_name[i] == 10
			||	channel_name[i] == 13  || channel_name[i] == 07)
		{
			return (false);
		}
	}
	return (true);
}

bool check_password(Channel *chan, std::vector<std::string> parse, IRC* serv, User *user, size_t i)
{
	std::vector<std::string>	keys;

	if (parse.size() > 1)
	{
		keys = ft_split(parse[1], ",");
		if (keys.size() >= i)
		{
			if (chan->getPassword() != keys[i])
			{
				serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(475, serv, user)));
				return false;
			}
		}
	}
	else
	{
		serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(475, serv, user)));
 		return false;
	}
	return true;
}

void join(std::vector<std::string> parse, IRC *serv, User *user)
{
	std::vector<std::string>	chans;
	std::pair<bool, Channel*>	res;
	Channel*					tmp;
	std::string					notice;

	chans = ft_split(parse[0], ",");
	for (size_t i = 0; i < chans.size(); i++)
	{
		std::string chan = trim_copy(chans[i]);
		if (is_valid_channame(chan))
		{
			notice = (user_answer(user));
			notice.append("JOIN ");
			notice.append(chan);
			notice.append("\r\n");
			res = serv->get_channel(chan);
			if (res.first && !res.second->userIsIn(user))
			{
				if (res.second->isBanned(user))
				{
					serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(474, serv, user, res.second->getName())));
				}
				else if(res.second->inviteOnly() && !res.second->isInvited(user))
				{
					serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(473, serv, user, res.second->getName())));
				}
				else
				{
					if (res.second->_members_count >= res.second->getUserLimit())
					{
						serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(471, serv, user, res.second->getName())));
					}
					else if (res.second->needsPass())
					{
						if (check_password(res.second, parse, serv, user, i))
						{
							res.second->addUser(user);
							res.second->send_all(serv, notice);
							user->_channel_joined.push_back(res.second);
							if (res.second->getTopic() != "")
								cmd_topic(serv, user, chan);
							cmd_names(serv, user, chan);
						}
					}
					else
					{
						res.second->addUser(user);
						res.second->send_all(serv, notice);
						user->_channel_joined.push_back(res.second);
						if (res.second->getTopic() != "")
							cmd_topic(serv, user, chan);
						cmd_names(serv, user, chan);
					}
				}
			}
			else if (!res.first)
			{
				tmp = serv->create_channel(chan, user);
				tmp->send_all(serv, notice);
				user->_channel_joined.push_back(tmp);
				tmp->_operators.push_back(user->_nick_name);
				if (tmp->getTopic() != "")
					cmd_topic(serv, user, chan);
				cmd_names(serv, user, chan);
			}
		}
		else
		{
			serv->_tcp.add_to_buffer(std::make_pair(
				user->_fd,
				send_rpl(476, serv, user, chan)
			));
		}
	}
}


void	cmd_join ( IRC *serv, User *user, std::string & args )
{
	std::vector<std::string>	parse;

	parse = ft_split(args, " ");
	if (args == "")
	{
		serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(461, serv, user))); //not enough parameters
		return;
	}
	if (parse.back() == "0")
	{
		std::list<Channel *>			users_chan;
		std::list<Channel *>::iterator	chan_it;
		std::string						chan_name;

		users_chan = user->_channel_joined;
		chan_it = users_chan.begin();
		while (chan_it != users_chan.end())
		{
			chan_name = (*chan_it)->getName();
			cmd_part(serv, user, chan_name);
			chan_it++;
		}
		user->_channel_joined.clear();
	}
	join(parse, serv, user);
}
