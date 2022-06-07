/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:07:44 by atrouill          #+#    #+#             */
/*   Updated: 2022/06/07 18:39:05 by atrouill         ###   ########.fr       */
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
void	cmd_privmsg ( IRC *serv, User *user, std::string & args );
void	cmd_names ( IRC *serv, User *user, std::string & args );
void	cmd_ping ( IRC *serv, User *user, std::string & args );
void	cmd_topic (IRC *serv, User *user, std::string & args);
void	cmd_part ( IRC *serv, User *user, std::string & args );
void	cmd_quit ( IRC *serv, User *user, std::string & args );
void	cmd_notice (IRC *serv, User *user, std::string & args);
void	cmd_kick ( IRC *serv, User *user, std::string & args );
void	cmd_mode ( IRC *serv, User *user, std::string & args );
void	cmd_who ( IRC *serv, User *user, std::string & args );
void	cmd_list ( IRC *serv, User *user, std::string & args );
void    cmd_invite ( IRC *serv, User *user, std::string & args );
void	cmd_oper ( IRC *serv, User *user, std::string & args );
void	cmd_motd ( IRC *serv, User *user, std::string & args );

#endif
