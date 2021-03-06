/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ignore.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:42:51 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/17 11:28:20 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "IRC.Class.hpp"
# include "functions.hpp"
# include "commands.hpp"

/**
 * @brief This command when a valid command is send by the client, but is not 
 * implemented. So we basicaly do nothing
 * 
 * @param serv 
 * @param user 
 * @param args 
 */
void	cmd_ignore ( IRC *serv, User *user, std::string & args )
{
	(void)serv;
	(void)user;
	(void)args;
}
