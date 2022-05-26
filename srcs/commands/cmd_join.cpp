/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_join.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldes-cou <ldes-cou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:27:31 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/26 13:12:18 by ldes-cou         ###   ########.fr       */
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

void	cmd_join ( IRC *serv, User *user, std::string & args )
{
	std::vector<std::string>	chans;
	std::vector<std::string>	keys;
	std::vector<std::string>	parse;
	std::pair<bool, Channel*>	res;
	Channel*					tmp;
	std::string					notice;

	parse = ft_split(args, " ");
	chans = ft_split(parse[0], ",");
	keys = ft_split(parse[1], ",");
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
