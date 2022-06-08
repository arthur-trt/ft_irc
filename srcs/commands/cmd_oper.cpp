/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_oper.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldes-cou <ldes-cou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:53:00 by atrouill          #+#    #+#             */
/*   Updated: 2022/06/08 16:32:14 by ldes-cou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPL.hpp"
#include "utils.hpp"
#include "IRC.Class.hpp"
#include "commands.hpp"
#include "functions.hpp"
#include <vector>
#include <string>

void	cmd_oper ( IRC *serv, User *user, std::string & args )
{
	std::vector<std::string>	splited;

	splited = ft_split(args, " ");
	if (splited.size() < 2)
	{
		serv->_tcp.add_to_buffer(std::make_pair(
			user->_fd,
			send_rpl(461, serv, user, "OPER")
		));
	}	
	else if (trim_copy(splited[0]) == OPER_USER && trim_copy(splited[1]) == OPER_PASS)
	{
		user->_isOperator = true;
		std::string	mode_args = (user->_nick_name + " +o");
		cmd_mode(serv, user, mode_args);
		serv->_tcp.add_to_buffer(std::make_pair(
			user->_fd,
			send_rpl(381, serv, user)
		));
	}
	else
	{
		serv->_tcp.add_to_buffer(std::make_pair(
			user->_fd,
			send_rpl(464, serv, user)
		));
	}
}
