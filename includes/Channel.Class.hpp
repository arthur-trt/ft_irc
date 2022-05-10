/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.Class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:54:27 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/10 14:07:17 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_CLASS_HPP
# define CHANNEL_CLASS_HPP

# include <map>
# include "User.Class.hpp"
# include "TCPServer.Class.hpp"

class Channel
{
	private:
		TCPServer				&_server;
		const std::string		_name;
		std::map<User *, bool>	_joined_user;
		size_t					_members_count;

		Channel ( void );
		Channel ( const Channel & src );
		Channel&	operator= ( const Channel & rhs );

	public:
		Channel ( TCPServer & server, const std::string & name, User * chan_operator );
		const std::string &	getName ( void ) const;
		bool				addUser ( User * user );
		bool				kickUser ( User * user );

};

#endif
