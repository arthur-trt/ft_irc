/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_topic.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:56:47 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/20 17:45:16 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPL.hpp"
#include "utils.hpp"
#include "IRC.Class.hpp"
#include "commands.hpp"
#include "functions.hpp"
#include <vector>
#include <string>

static bool	valid_args ( IRC *serv, User *user, std::string & args )
{
	if (args == "")
	{
		serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(461, serv, user, "TOPIC")));
		return (false);
	}
	return (true);
}

void	cmd_topic (IRC *serv, User *user, std::string & args)
{
	std::vector<std::string>	split;
	std::string					channel, topic;
	std::string					answer;
	std::pair<bool, Channel*>	chan;

	if (valid_args(serv, user, args))
	{
		split = ft_split(args, ":");
		channel = trim_copy(split[0]);
		chan = serv->get_channel(channel);
		if (chan.first == false)
			return ;
		if (chan.second->userIsIn(user) == false)
		{
			serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(442, serv, user, channel)));
			return ;
		}
		if (args.find_first_of(":") == std::string::npos)
		{
			// GET TOPIC
			topic = chan.second->getTopic();
			if (topic == "")
			{
				serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(331, serv, user, channel)));
				return;
			}
			answer = send_rpl(332, serv, user, channel);
			answer.append(topic);
			answer.append("\r\n");
			serv->_tcp.add_to_buffer(std::make_pair(user->_fd, answer));
		}
		else
		{
			// SET TOPIC
			topic = trim_copy(split[1]);
			if (chan.second->getUser(user).second == false) // Is not operator
			{
				serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(482, serv, user, channel)));
				return ;
			}
			chan.second->setTopic(topic);
			answer = user_answer(user);
			answer.append("TOPIC ");
			answer.append(channel);
			answer.append(" :");
			answer.append(topic);
			answer.append("\r\n");
			chan.second->send_all(serv, answer);
		}
	}
}