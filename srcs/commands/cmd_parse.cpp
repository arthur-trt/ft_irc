/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:07:36 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/11 11:53:11 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include "commands.hpp"
#include <string>

int		cmd_parse ( std::string entry )
{
	std::string	tmp = trim_copy(entry);
	size_t	pos = tmp.find_first_of(' ');

	std::string	cmd, args;

	//cmd = tmp.substr(0, pos)
	//args = tmp.substr(pos, )
}
