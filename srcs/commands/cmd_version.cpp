/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_version.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpons <tpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:56:19 by tpons             #+#    #+#             */
/*   Updated: 2022/06/08 14:42:39 by tpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <cctype>
#include "utils.hpp"
#include "IRC.Class.hpp"
#include "User.Class.hpp"
#include "commands.hpp"
#include "functions.hpp"

/**
 * @brief 
 * 	Command: VERSION
   	Parameters: [ <target> ]
	
   	The VERSION command is used to query the version of the server
   	program.  An optional parameter <target> is used to query the version
   	of the server program which a client is not directly connected to.
	
	Our server doesn't handle server to server connection, so any target
	that isn't ou server will be considered as an ERR_NOSUCHSERVER.
	
   	Wildcards are allowed in the <target> parameter.
	
   	Numeric Replies:
	   ERR_NOSUCHSERVER				RPL_VERSION
	
	351	RPL_VERSION
			"<version>.<debuglevel> <server> :<comments>"
			
	-   Reply by the server showing its version details.
		The <version> is the version of the software being
		used (including any patchlevel revisions) and the
		<debuglevel> is used to indicate if the server is
		running in "debug mode".
		The "comments" field may contain any comments about
		the version or further version details.
 *
 */

#if DEBUG
	std::string	g_debug_level("DEBUGGING");
#else
	std::string	g_debug_level("");
#endif

void	cmd_version ( IRC *serv, User *user, std::string & args )
{
	std::string	comments("this is a beta, please be kind :D");
	if (args !=  "")
	{
		if (!pattern_match(serv->_tcp.getHostname(), args))
		{
			serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(402, serv, user, args)));
			return ;
		}
	}
	serv->_tcp.add_to_buffer(std::make_pair(user->_fd, send_rpl(351, serv, user, g_debug_level, comments)));
}