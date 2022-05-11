/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:49:25 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/11 14:53:59 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

/**
 * @brief Remove space from start
 * 
 * @param s string to trim
 */
void	ltrim ( std::string &s )
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
			std::not1(std::ptr_fun<int, int>(std::isspace))));
}

/**
 * @brief Remove space from end of the string
 * 
 * @param s string to rtrim
 */
void	rtrim ( std::string &s )
{
	s.erase(std::find_if(s.rbegin(), s.rend(),
			std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

/**
 * @brief Remove space at the beggining and the end of a string
 * 
 * @param s String to trim
 */
void	trim ( std::string &s )
{
	ltrim(s);
	rtrim(s);
}

// trim from start (copying)
std::string	ltrim_copy ( std::string s )
{
	ltrim(s);
	return s;
}

// trim from end (copying)
std::string	rtrim_copy ( std::string s )
{
	rtrim(s);
	return s;
}

// trim from both ends (copying)
std::string	trim_copy ( std::string s )
{
	trim(s);
	return s;
}

char		my_toupper ( char ch )
{
    return static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
}

void			str_upper ( std::string & s )
{
	for (size_t i = 0; i < s.length(); i++)
	{
		s[i] = my_toupper(s[i]);
	}
	
}