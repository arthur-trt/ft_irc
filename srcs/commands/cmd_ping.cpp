/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ping.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 09:51:42 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/23 16:56:23 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPL.hpp"
#include "utils.hpp"
#include "IRC.Class.hpp"
#include "commands.hpp"
#include "functions.hpp"

void	cmd_ping ( IRC *serv, User *user, std::string & args )
{
	serv->_tcp.add_to_buffer(std::make_pair(user->_fd, "PONG " + args + "\r\n"));
}
