/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:07:36 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/11 15:17:55 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include "commands.hpp"
#include "User.Class.hpp"
#include <string>

int		cmd_parse ( std::string entry, User *user )
{
	std::string	tmp = ltrim_copy(entry);
	size_t	pos = tmp.find_first_of(' ');

	std::string	cmd, args;

	cmd = trim_copy(tmp.substr(0, pos));
	str_upper(cmd);
	args = trim_copy(tmp.substr(pos, tmp.length()));
	
	if (cmd == "NICK") {}
}
