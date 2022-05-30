/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   masks.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:39:57 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/30 14:27:22 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 *	mask		=	*( nowild / noesc wildone / noesc wildmany )
 *	wildone		=	%x3F (?)
 *	wildmany	=	%x2A (*)
 *	nowild		=	%x01-29 / %x2B-3E / %x40-FF
 *							; any octet except NUL, "*", "?"
 *	noesc		=	%x01-5B / %x5D-FF
 *							; any octet except NUL and "\"
 *	matchone	=	%x01-FF
 *							; matches wildone
 *	matchmany	=	*matchone
 *							; matches wildmany
 *
 */

#include "utils.hpp"
#include "IRC.Class.hpp"
#include "User.Class.hpp"
#include "functions.hpp"
#include <list>


static bool			pattern_match (std::string str, std::string pattern )
{
	size_t n = str.size();
	size_t m = pattern.size();

	if (m == 0)
		return n == 0;

	bool T[n + 1][m + 1];

	std::memset(&T, false, sizeof(T));

	T[0][0] = true;

	for (size_t j = 1; j <= m; ++j)
	{
		if (pattern[j - 1] == '*')
			T[0][j] = T[0][j - 1];
	}
	for (size_t i = 1; i <= n; ++i)
	{
		for (size_t j = 1; j <= m; ++j)
		{
			if (pattern[j - 1] == str[i - 1] || pattern[j - 1] == '?')
				T[i][j] = T[i - 1][j - 1];
			else if (pattern[j - 1] == '*')
				T[i][j] = T[i][j - 1] || T[i - 1][j];
			else
				T[i][j] = false;
		}
	}
	return T[n][m];
}

std::list<User *>	user_masks (IRC * serv, std::string args)
{
	std::list<User *>				res;

	std::map<int, User *>			users;
	std::map<int, User *>::iterator	it;

	std::string				pat_nick, pat_user, pat_hostname;
	std::string::size_type	nick_end, user_end;

	// Obtain the three pattern
	nick_end = args.find('!');
	user_end = args.find('@');
	pat_nick = args.substr(0, nick_end);
	pat_user = args.substr(nick_end + 1, (user_end - nick_end - 1));
	pat_hostname = args.substr(user_end + 1, args.size());

	users = serv->get_user();
	it = users.begin();
	while (it != users.end())
	{
		if (pattern_match(it->second->_nick_name, pat_nick)	&&
			pattern_match(it->second->_user_name, pat_user) &&
			pattern_match(it->second->_hostname, pat_hostname))
		{
			res.push_back(it->second);
		}
		it++;
	}
	return (res);
}

//std::list<Channel *>	channel_masks (IRC * serv, std::string args)
//{
//	(void)serv;
//	(void)args;

//}
