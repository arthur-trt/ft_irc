/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:14:54 by atrouill          #+#    #+#             */
/*   Updated: 2022/06/10 11:51:02 by tpons            ###   ########.fr       */
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

void	cmd_list ( IRC *serv, User *user, std::string & args )
{
	std::vector<std::string>					params;
	std::vector<std::string>					chans_args;
	std::map<std::string, Channel*>				chans;
	std::map<std::string, Channel*>::iterator	it_chans;
	std::pair<bool, Channel *>					tmp;

	params = ft_split(args, " ");
	if (params.size() > 1)
	{
		if (!pattern_match(serv->_tcp.getHostname(), params[1]))
		{
			serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(402, serv, user, params[1])));
			return ;
		}
		params.pop_back();
	}
	if (params.size() == 1)
	{
		chans_args = ft_split(params[0], ",");
		while (chans_args.size() != 0)
		{
			tmp = serv->get_channel(chans_args.back());
			if (tmp.first)
			{
				chans.insert(std::make_pair(chans_args.back(), tmp.second));
			}
			else
			{
				serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(403, serv, user, chans_args.back())));
			}
			chans_args.pop_back();
		}
	}
	else
	{
		chans = serv->get_channel();
	}
	it_chans = chans.begin();
	while (it_chans != chans.end())
	{
		serv->_tcp.add_to_buffer(
			std::make_pair(
				user->_fd,
				send_rpl(322, serv, user, it_chans->first, it_chans->second->getTopic())
			)
		);
		it_chans++;
	}
	serv->_tcp.add_to_buffer(std::make_pair(
		user->_fd,
		send_rpl(323, serv, user)
	));
}
