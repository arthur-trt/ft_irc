/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.Class.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:17:22 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/12 17:40:14 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_CLASS_HPP
# define IRC_CLASS_HPP

# include "TCPServer.Class.hpp"
# include "User.Class.hpp"
# include "Channel.Class.hpp"
# include <map>
# include <string>

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

		void		add_user ( int fd, std::string hostname );
		void		remove_user ( int fd );
		User*		get_user ( int fd );

		void		create_channel ( std::string & name, User * chan_operator );
		void		remove_channel ( std::string & name );
		Channel*	get_channel ( std::string & name );


};

#endif
