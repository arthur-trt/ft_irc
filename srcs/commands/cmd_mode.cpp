/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mode.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldes-cou <ldes-cou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:51:00 by ldes-cou          #+#    #+#             */
/*   Updated: 2022/05/26 18:22:11 by ldes-cou         ###   ########.fr       */
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

   Additional modes may be available later on.
   The flag 'a' SHALL NOT be toggled by the user using the MODE command,
   instead use of the AWAY command is REQUIRED.

   If a user attempts to make themselves an operator using the "+o" or
   "+O" flag, the attempt SHOULD be ignored as users could bypass the
   authentication mechanisms of the OPER command.  There is no
   restriction, however, on anyone `deopping' themselves (using "-o" or
   "-O").

   On the other hand, if a user attempts to make themselves unrestricted
   using the "-r" flag, the attempt SHOULD be ignored.  There is no
   restriction, however, on anyone `deopping' themselves (using "+r").
   This flag is typically set by the server upon connection for
   administrative reasons.  While the restrictions imposed are left up
   to the implementation, it is typical that a restricted user not be
   allowed to change nicknames, nor make use of the channel operator
   status on channels.

   The flag 's' is obsolete but MAY still be used.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_USERSDONTMATCH
           ERR_UMODEUNKNOWNFLAG            RPL_UMODEIS
*/
void	cmd_mode ( IRC *serv, User *user, std::string & args )
{
    (void)user;
    (void)serv;
    std::vector<std::string> parse;
    std::string name;
    std::pair<bool, Channel*>	res;
    
    parse = ft_split(args, " ");
    name = parse[0];
    if (parse.size() < 2)
    {
        serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(461, serv, user)));
		return;
    }
    //check if mode are on the list
    std::vector<std::string> mode(parse.begin() + 1, parse.end());
    if ( parse[1] == "#")
    {
        res = serv->get_channel(name);
        if (res.first)
            res.second->addModetoChan(mode);
    }
    else
    {
        std::cout << "caca" << std::endl;
    }
    std::cout << args << std::endl;
}
