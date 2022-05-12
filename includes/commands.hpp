/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:07:44 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/12 15:37:42 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

#include "IRC.Class.hpp"
#include "User.Class.hpp"

int		cmd_nick ( IRC *serv, User *user, std::string args );
int		cmd_parse ( std::string entry, IRC *serv, User *user );
int		cmd_user ( IRC *serv, User *user, std::string args );

#endif
