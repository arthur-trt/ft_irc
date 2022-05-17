/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_names.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:27:31 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/16 22:44:05 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPL.hpp"
#include "utils.hpp"
#include "IRC.Class.hpp"
#include "commands.hpp"
#include "functions.hpp"
#include <vector>
#include <string>

void	cmd_names ( IRC *serv, User *user, std::string & args )
{
	std::string								msg;
	std::pair<bool, Channel *>				res;
	std::vector<std::string>				chan;
	std::map<User *, bool>::iterator		it;
	std::map<User *, bool>					connected_users;
	
	if (args != "")
	{
		chan = ft_split(args, ",");
		for (size_t i = 0; i < chan.size(); i++)
		{
			res = serv->get_channel(chan[i]);
			if (res.first)
			{
				connected_users = res.second->getUsers();
				it = connected_users.begin();
				msg = send_rpl(353, serv, user, chan[i]);
				msg.append(chan[i]);
				msg.append(" :");
				while (it != connected_users.end())
				{
					if (it->second)
						msg.append("@");
					else
						msg.append(" ");
					msg.append(it->first->_nick_name);
					msg.append(" ");
					it++;
				}
				msg.append("\r\n");
				serv->_tcp.add_to_buffer(std::make_pair(user->_fd, msg));
				serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(366, serv, user, chan[i])));
			}			
		}
	}
}