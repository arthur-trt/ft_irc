/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_invite.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldes-cou <ldes-cou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:04:28 by ldes-cou          #+#    #+#             */
/*   Updated: 2022/06/09 14:42:22 by ldes-cou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPL.hpp"
#include "utils.hpp"
#include "IRC.Class.hpp"
#include "commands.hpp"
#include "functions.hpp"
/*
        ERR_NEEDMOREPARAMS     ok         ERR_NOSUCHNICK ok
        ERR_NOTONCHANNEL      ok          ERR_USERONCHANNEL ok
        ERR_CHANOPRIVSNEEDED  ok
        RPL_INVITING          ok          
*/

void cmd_invite ( IRC *serv, User *user, std::string & args )
{
    std::vector<std::string>	parse;
	std::pair<bool, Channel*>	chan;
    std::string                 nick;
    std::string                 chan_name;
    std::string                 user_invited;
    
    parse = ft_split(args, " ");
    if (parse.size() > 0)
        nick = trim_copy(parse[0]);
    else
        return;
    if (parse.size() < 2)
    {
        serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(461, serv, user, "INVITE")));
        return;
    }
    chan_name = trim_copy(parse[1]);
    chan = serv->get_channel(chan_name);
    if (chan.first)
    {
        if (!chan.second->isOperator(*user) && (chan.second->inviteOnly() == true)) // check si le chan est +i && user != operator
        {
            serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(482, serv, user, chan.second->getName())));
            return;
        }
        std::pair<bool, User *> new_user;
        new_user = serv->get_user(nick);
        if (new_user.first)
        {
            if (!chan.second->userIsIn(user->_nick_name))
                serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(441, serv, user, user->_nick_name)));
            else if (chan.second->userIsIn(nick))
                serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(443, serv, user, nick)));
            else
            {
                chan.second->addInvited(nick);
                serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(341, serv, user, chan_name, nick)));
                std::string notice = (user_answer(user));
                notice.append("INVITE ");
                notice.append(nick + " ");
                notice.append(chan_name);
                notice.append("\r\n");
                serv->_tcp.add_to_buffer(std::make_pair(new_user.second->_fd, notice));
            }
        }
        else
            serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(401, serv, user, chan_name)));
    }
    else
        serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(401, serv, user, nick)));
}
    