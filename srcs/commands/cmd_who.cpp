/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_who.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:37:24 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/30 14:15:08 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <cctype>
#include "utils.hpp"
#include "IRC.Class.hpp"
#include "User.Class.hpp"
#include "functions.hpp"

//static bool	valid_args ( IRC *serv, User *user, std::string & args )
//{

//}

void	cmd_who ( IRC *serv, User *user, std::string & args )
{
	std::list<User *>			res;
	std::list<User *>::iterator	it;

	(void)serv;
	(void)user;
	res = user_masks(serv, args);
	it = res.begin();
	while (it != res.end())
	{
		std::cout << "Match : " << (*it)->_nick_name << std::endl;
		it++;
	}
}
