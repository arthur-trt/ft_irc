/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_not_found.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:46:13 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/13 15:48:44 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPL.hpp"
#include "utils.hpp"
#include "IRC.Class.hpp"
#include "commands.hpp"
#include "functions.hpp"

void	cmd_not_found ( IRC *serv, User *user, std::string & args )
{
	serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(421, serv, user, args)));
}
