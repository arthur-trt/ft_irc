/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mode.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldes-cou <ldes-cou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:51:00 by ldes-cou          #+#    #+#             */
/*   Updated: 2022/06/02 16:50:35 by ldes-cou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPL.hpp"
#include "config.hpp"
#include "IRC.Class.hpp"
#include "User.Class.hpp"
#include "utils.hpp"
#include "functions.hpp"
#include <vector>
#include <string>

/*User mode message

	  Command: MODE
   Parameters: <nickname>
			   *( ( "+" / "-" ) *( "i" / "w" / "o" / "O" / "r" ) )

   The user MODE's are typically changes which affect either how the
   client is seen by others or what 'extra' messages the client is sent.

   A user MODE command MUST only be accepted if both the sender of the
   message and the nickname given as a parameter are both the same.  If
   no other parameter is given, then the server will return the current
   settings for the nick.

	  The available modes are as follows:

		   a - user is flagged as away;
		   i - marks a users as invisible;
		   w - user receives wallops;
		   r - restricted user connection;
		   o - operator flag;
		   O - local operator flag;
		   s - marks a user for receipt of server notices.

   Numeric Replies:

		   ERR_NEEDMOREPARAMS              ERR_USERSDONTMATCH
		   ERR_UMODEUNKNOWNFLAG            RPL_UMODEIS
Channel Modes

   The various modes available for channels are as follows:

		O - give "channel creator" status;
		o - give/take channel operator privilege;
		v - give/take the voice privilege;

		a - toggle the anonymous channel flag;
		i - toggle the invite-only channel flag; ok
		m - toggle the moderated channel;
		n - toggle the no messages to channel from clients on the
			outside;
		q - toggle the quiet channel flag;
		p - toggle the private channel flag;
		s - toggle the secret channel flag;
		r - toggle the server reop channel flag;
		t - toggle the topic settable by channel operator only flag;

		k - set/remove the channel key (password); ok
		l - set/remove the user limit to channel;

		b - set/remove ban mask to keep users out; ok
		e - set/remove an exception mask to override a ban mask;
		I - set/remove an invitation mask to automatically override ???
			the invite-only flag;
		367    RPL_BANLIST
              "<channel> <banmask>"
       368    RPL_ENDOFBANLIST
              "<channel> :End of channel ban list"

         - When listing the active 'bans' for a given channel,
           a server is required to send the list back using the
           RPL_BANLIST and RPL_ENDOFBANLIST messages.  A separate
           RPL_BANLIST is sent for each active banmask.  After the
           banmasks have been listed (or if none present) a
           RPL_ENDOFBANLIST MUST be sent.
*/
void	printBannedUsers( IRC *serv, Channel * chan, User * user)
{
	std::vector<std::string> banned = chan->getBannedUser();
	std::string userMessage;
	std::cout << RED << "ICI ?" <<  END << std::endl;
	userMessage = user_answer(user);
	for (size_t i = 0; i < banned.size(); i++)
	{
		std::cout << GREEN << "LA ?" <<  END << std::endl;
		std::cout << banned[i]<< std::endl;
		userMessage += banned[i];
		userMessage += " ";
	}
	userMessage += "\r\n";
	serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(367, serv, user, chan->getName(), userMessage)));
	serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(368, serv, user, chan->getName())));
	chan->send(serv, user, userMessage);
	
	
	
}

void	cmd_mode ( IRC *serv, User *user, std::string & args )
{
	//Parameters: <channel> *( ( "-" / "+" ) *<modes> *<modeparams> )
	//Parameters: <nickname>
			   //*( ( "+" / "-" ) *( "i" / "w" / "o" / "O" / "r" ) )
	(void)user;
	std::vector<std::string> parse;
	std::string name;
	std::pair<bool, Channel*>	chan;
	std::string notice;


	parse = ft_split(args, " ");
	name = trim_copy(parse[0]);
	std::string params = "";
	
	if (parse.size() > 2)
		params = parse[2];
	if (name.find_first_of(CHAN_FIRST, 0) != std::string::npos)
	{
		chan = serv->get_channel(name);
		if (chan.first)
		{
			if (parse.size() < 2)
			{
				serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(324, serv, user, name, chan.second->getMode(), params)));
				return;
			}
			else
			{
				std::string mode = parse[1];
				if (mode == "b")
					printBannedUsers(serv, chan.second, user);
				else if (chan.second->updateMode(mode, params))
					serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(324, serv, user, name, mode, params)));
				else
					serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(472, serv, user, name)));
				notice = user_answer(user);
				notice.append("MODE ");
				notice.append(name + " ");
				notice.append(mode + " ");
				notice.append(params + " ");
				notice.append("\r\n");
				chan.second->send(serv, user, notice);
			}
		}
	}
	else
	{
		std::pair<bool, User*>	some_user;
		some_user = serv->get_user(name);
		if (some_user.first)
		{
			if (parse.size() < 2)
			{
				serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(324, serv, user, name, some_user.second->getMode(), params)));
				return;
			}
			else
			{
				std::string mode = parse[1];
				if (some_user.second->updateMode(mode))
					serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(221, serv, user, mode, params)));
				else
					serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(501, serv, user, mode)));
			}
		}   
	}
}
