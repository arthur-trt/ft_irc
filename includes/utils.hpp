/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:36:06 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/11 19:28:39 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <string>
# include <vector>
# include "TCPServer.Class.hpp"
# include "User.Class.hpp"

#if DEBUG
  #include <stdio.h>
  #define _GLIBCXX_DEBUG 1
  #define _GNU_SOURCE 1
  #define debug(x, ...)      do{fprintf(stderr, "%s:%s(%u): " x "\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);}while(0)
#else
  #define debug(x, ...)      /* x */
#endif

std::string	send_rpl(int rpl_num, TCPServer *serv, User *user);

void ltrim(std::string &s);
void rtrim(std::string &s);
void trim(std::string &s);
std::string ltrim_copy(std::string s);
std::string rtrim_copy(std::string s);
std::string trim_copy(std::string s);
char		    my_toupper ( char ch );
void		  	str_upper ( std::string & s );
std::vector<std::string>		ft_split(std::string s, std::string splitter);
std::string				  	ft_to_string(size_t value);

#endif
