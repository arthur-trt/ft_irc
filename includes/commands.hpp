/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:07:44 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/11 18:12:13 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

#include "TCPServer.Class.hpp"
#include "User.Class.hpp"

int		cmd_nick ( TCPServer *serv, User *user, std::string args );
int		cmd_parse ( std::string entry, TCPServer *serv, User *user );
int		cmd_user ( TCPServer *serv, User *user, std::string args );

#endif
