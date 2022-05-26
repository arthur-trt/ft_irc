/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mode.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldes-cou <ldes-cou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:51:00 by ldes-cou          #+#    #+#             */
/*   Updated: 2022/05/26 15:10:27 by ldes-cou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPL.hpp"
#include "config.hpp"
#include "IRC.Class.hpp"
#include "User.Class.hpp"
#include "utils.hpp"
#include "functions.hpp"
#include <vector>
#include <string>

void	cmd_mode ( IRC *serv, User *user, std::string & args )
{
    (void)serv;
    (void)user;
    std::cout << args << std::endl;
}
