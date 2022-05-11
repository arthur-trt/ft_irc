/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nick.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:14:16 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/11 15:21:37 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include "User.Class.hpp"

int		cmd_nick ( User *user, std::string args )
{
	user->_nick_name = args;
	return (0);
}