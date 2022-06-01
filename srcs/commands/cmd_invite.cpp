/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_invite.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldes-cou <ldes-cou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:04:28 by ldes-cou          #+#    #+#             */
/*   Updated: 2022/06/01 14:55:39 by ldes-cou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include "utils.hpp"
#include "Channel.Class.hpp"

/*
        ERR_NEEDMOREPARAMS              ERR_NOSUCHNICK
        ERR_NOTONCHANNEL                ERR_USERONCHANNEL
        ERR_CHANOPRIVSNEEDED
        RPL_INVITING                    RPL_AWAY
*/

void cmd_invite(std::vector<std::string> args, IRC *serv, User *user)
{
    std::vector<std::string>	parse;
	std::pair<bool, Channel*>	chan;
	Channel*					tmp;
	// std::string					notice;
    std::string                 name;
    std::string                 user_invited;
    
    parse = ft_split(args, " ");
    name = trim_copy(parse[0]);
    if (parse.size() < 2)
    {
        serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(461, serv, user, "INVITE")));
        return;
    }
    else if (chan.find_first_of(CHAN_FIRST, 0) != std::string::npos)
    {
        chan = serv->get_channel(name);
        if (chan.first)
        {
            std::pair<bool, User*>	new_user;
            new_user = serv->get_user(name);
            if (new_user.first)
                chan.second->_invited_user.push_back(new_user);
            else
                serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(401, serv, user, new_user._nick_name)));
        }
    }
}
    