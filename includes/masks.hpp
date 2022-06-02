/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   masks.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:52:23 by atrouill          #+#    #+#             */
/*   Updated: 2022/06/02 12:11:04 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MASKS_HPP
# define MASKS_HPP

#include <list>
#include <string>
#include "User.Class.hpp"
#include "Channel.Class.hpp"
#include "IRC.Class.hpp"

bool			pattern_match (std::string str, std::string pattern );
std::list<User *>		user_masks(IRC * serv, std::string args);
std::list<Channel *>	channel_masks(IRC * serv, std::string args);

template <typename T>
std::list<T>	masks(IRC *serv, std::string args)
{
	if (args.find_first_of(CHAN_FIRST, 0) != std::string::npos)
	{
		return (channel_masks(serv, args));
	}
	else if (	args.find_first_of("!") != std::string::npos &&
				args.find_first_of("@") != std::string::npos)
	{
		return (user_masks(serv, args));
	}
	return (u_nullptr);
}

#endif
