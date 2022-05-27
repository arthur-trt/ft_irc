/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_join.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldes-cou <ldes-cou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:27:31 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/27 15:08:29 by ldes-cou         ###   ########.fr       */
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

// static bool	is_valid_channame ( std::string const & channel_name )
// {
// 	if (channel_name[0] != '#' && channel_name[0] != '&'
// 		&& channel_name[0] != '+')
// 	{
// 		return (false);
// 	}
// 	for (size_t i = 1; i < channel_name.length(); i++)
// 	{
// 		if (	channel_name[i] == ':' || channel_name[i] == ','
// 			||	channel_name[i] == ' ' || channel_name[i] == 10
// 			||	channel_name[i] == 13  || channel_name[i] == 07)
// 		{
// 			return (false);
// 		}
// 	}
// 	return (true);
// }

// static bool	valid_args ( IRC *serv, User *user, std::string & args )
// {

// }
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

           ERR_NEEDMOREPARAMS    ok          ERR_BANNEDFROMCHAN
           ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
           ERR_CHANNELISFULL               ERR_BADCHANMASK
           ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
           ERR_TOOMANYTARGETS              ERR_UNAVAILRESOURCE
           RPL_TOPIC
*/
void join(std::vector<std::string> parse, IRC *serv, User *user)
{
	std::vector<std::string>	chans;
	std::pair<bool, Channel*>	res;
	Channel*					tmp;
	std::string					notice;
	
	chans = ft_split(parse[0], ",");
	std::vector<std::string>::iterator it = chans.begin();
	for ( ; it < chans.end(); it ++ )
	{
		std::string chan = trim_copy(*it);
		notice.append(user_answer(user));
		notice.append("JOIN ");
		notice.append(chan);
		notice.append("\r\n");
		res = serv->get_channel(chan);
		if (res.first)
		{
			res.second->addUser(user);
			res.second->send_all(serv, notice);
			user->_channel_joined.push_back(res.second);
			if (res.second->getTopic() != "")
				cmd_topic(serv, user, chan);
		}
		else
		{
			tmp = serv->create_channel(chan, user);
			tmp->send_all(serv, notice);
			user->_channel_joined.push_back(tmp);
			if (tmp->getTopic() != "")
				cmd_topic(serv, user, chan);
		}
		cmd_names(serv, user, chan);
	}
}
// void join_with_password(std::vector<std::string> parse, IRC *serv, User *user)
// {
// 	std::vector<std::string>	chans;
// 	std::vector<std::string>	keys;
// 	chans = ft_split(parse[0], ",");
// 	keys = ft_split(parse[1], ",");
// 	for (size_t i = 0; i < keys.size(); i++)
// 	{
// 		if (chans[i].needsPass)
			
// 		//check chans[i]._mode.find("+k") 
		
// 	}
				 
// }
void	cmd_join ( IRC *serv, User *user, std::string & args )
{
	std::vector<std::string>	parse;

	parse = ft_split(args, " ");
	if (parse.begin() == parse.end())
	{
		serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(461, serv, user))); //not enough parameters
		return;
	}
	if (parse.size() > 1)
		std::cout << "join with pass_word" << std::endl;//join_with_password(parse, serv, user);
	else
		join(parse, serv, user);
}


