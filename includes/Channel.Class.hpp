/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.Class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldes-cou <ldes-cou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:54:27 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/25 16:29:43 by ldes-cou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_CLASS_HPP
# define CHANNEL_CLASS_HPP

# include <map>
# include <vector>
# include "User.Class.hpp"
# include "TCPServer.Class.hpp"
# include "IRC.Class.hpp"

class IRC;
class Channel
{
	private:
		TCPServer				&_server;
		const std::string		_name;
		std::map<User *, bool>	_joined_user;
		std::vector<User *> 	_banned_user;
		size_t					_members_count;
		std::string				_topic;

		Channel ( void );
		Channel ( const Channel & src );
		Channel&	operator= ( const Channel & rhs );

	public:
		Channel ( TCPServer & server, const std::string & name, User * chan_operator );
		~Channel();
		const std::string &				getName ( void ) const;
		const std::map<User *, bool> &	getUsers ( void ) const;
		const std::pair<User *, bool>   getUser ( User * const & user ) const;
		size_t							getMembersCount ( void ) const;

		bool							isBanned ( User * const & user ) const;
		bool							addUser ( User * user );
		bool							kickUser ( User * user );
		bool							removeUser ( User * user );
		void							send ( IRC * serv, User * sender, std::string msg );
		void							send_all ( IRC * serv, std::string msg );

		const std::string &				getTopic ( void ) const;
		void							setTopic ( std::string topic );

		bool							userIsIn ( User * const & user ) const;
		bool							userIsIn ( const std::string & user ) const;

};

#endif
