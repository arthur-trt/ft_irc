/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:31:21 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/24 16:00:56 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_HPP
# define FUNCTIONS_HPP

# include <string>
# include <vector>
# include <string>
# include "IRC.Class.hpp"
# include "User.Class.hpp"

std::string	send_rpl(int rpl_num, IRC *serv, User *user, std::string args = "", std::string args2 = "");
std::string	user_answer(const std::string & nick, const std::string & username, const std::string & host);
std::string	user_answer(const User * user);

void		ltrim(std::string &s);
void		rtrim(std::string &s);
void		trim(std::string &s);
std::string ltrim_copy(std::string s);
std::string rtrim_copy(std::string s);
std::string trim_copy(std::string s);
char						    my_toupper ( char ch );
void						  	str_upper ( std::string & s );
std::vector<std::string>		ft_split(std::string s, std::string splitter);
std::string						ft_to_string(int value);

#endif
