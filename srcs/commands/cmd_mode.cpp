/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mode.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:51:00 by ldes-cou          #+#    #+#             */
/*   Updated: 2022/05/30 16:06:50 by ldes-cou         ###   ########.fr       */
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
        i - toggle the invite-only channel flag;
        m - toggle the moderated channel;
        n - toggle the no messages to channel from clients on the
            outside;
        q - toggle the quiet channel flag;
        p - toggle the private channel flag;
        s - toggle the secret channel flag;
        r - toggle the server reop channel flag;
        t - toggle the topic settable by channel operator only flag;

        k - set/remove the channel key (password);
        l - set/remove the user limit to channel;

        b - set/remove ban mask to keep users out;
        e - set/remove an exception mask to override a ban mask;
        I - set/remove an invitation mask to automatically override
            the invite-only flag;
*/

void	cmd_mode ( IRC *serv, User *user, std::string & args )
{
    //1.check if chan or user exists
    //2.check if mode is available in available_chan/user mode 
    //3.add in Chan or User
    //Parameters: <channel> *( ( "-" / "+" ) *<modes> *<modeparams> )
    (void)user;
    std::vector<std::string> parse;
    std::string name;
    std::pair<bool, Channel*>	chan;
    std::string notice;
    

    std::cout << " args  ===" << args << std::endl;  
    parse = ft_split(args, " ");
    name = trim_copy(parse[0]);
    
    if (parse.size() < 2)
    {
        serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(461, serv, user)));
		return;
    }
    //std::vector<std::string> reparse = ft_split(parse[1], " ");
    std::string mode = parse[1];
    std::cout << "receiving  mode == " << mode << std::endl;
    std::cout << "reparse.size() ==" << parse.size() << std::endl;
    std::string params = "";
    if (parse.size() > 2)
        params = parse[2];
    //std::cout <<"params == "<<  params << std::endl;

    chan = serv->get_channel(name);
    if (chan.first)
    {
        chan.second->addMode(mode);
        chan.second->updateMode(mode, params);
        std::cout << "needsPass" << chan.second->needsPass() << std::endl;
        serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(324, serv, user, name, mode, params)));
        // notice = user_answer(user);
        // notice += ("MODE " + name + mode + params + "/r/n");
        // chan.second->send_all(serv, notice);
    }
    else
    {
        std::cout << "c'est pas un nom de chan" << std::endl;
    }
    // else
    // {
    //     std::pair<bool, User*>	some_user;
    //     some_user = serv->get_user(name);
    //     if (some_user.first)
    //     {
    //         std::cout << "coucou " << params << std::cout;
    //         //some_user.second->addMode(mode);
    //         //some_user.second->updateMode(mode, params);
    //     }
    //     else
    //     {
    //         std::cout << "wrong username" << std::endl;
    //     }
    // }
}
