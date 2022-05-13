/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:07:44 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/13 18:28:10 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

#include "IRC.Class.hpp"
#include "User.Class.hpp"

int		cmd_parse ( std::string entry, IRC *serv, User *user );

void	cmd_ignore ( IRC *serv, User *user, std::string & args );
void	cmd_not_found ( IRC *serv, User *user, std::string & args );
void	cmd_pass ( IRC *serv, User *user, std::string & args );
void	cmd_nick ( IRC *serv, User *user, std::string & args );
void	cmd_user ( IRC *serv, User *user, std::string & args );
void	cmd_join ( IRC *serv, User *user, std::string & args );

#endif
