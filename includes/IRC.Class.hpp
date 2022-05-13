/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.Class.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:17:22 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/13 11:38:59 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_CLASS_HPP
# define IRC_CLASS_HPP

# include "TCPServer.Class.hpp"
# include "User.Class.hpp"
# include "Channel.Class.hpp"
# include "utils.hpp"
# include <map>
# include <string>

# define SPECIALS "[]\\`_^{|}"


class User;
class Channel;

class IRC
{
	public:
		typedef	void	(*command)(IRC *, User *, std::string &);
		TCPServer									_tcp;

	private:

		std::map<int, User*>						_connected_user;
		std::map<std::string, Channel*>				_channels;
		static std::map<std::string, command>		_available_command;


	public:
		IRC ( int port );
		~IRC ();

		void						add_user ( int fd, std::string hostname );
		void						remove_user ( int fd );
		User*						get_user ( int fd );
		std::pair<bool, User*>		get_user ( std::string const & nick_name );

		void						create_channel ( std::string & name, User * chan_operator );
		void						remove_channel ( std::string & name );
		std::pair<bool, Channel*>	get_channel ( std::string & name );


};

#endif
