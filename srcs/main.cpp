/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:39:29 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/05 16:35:14 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.hpp"
#include "User.Class.hpp"
#include "TCPServer.Class.hpp"

void	loop (TCPServer *server)
{
	(void)server;
}

int	main(int argc, char **argv)
{
	int	port;

	port = (argc == 2) ? std::atoi(argv[1]) : PORT;
	
	TCPServer	server(port);

	loop (&server);

	return (0);
}
