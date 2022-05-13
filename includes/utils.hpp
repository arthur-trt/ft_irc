/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrouill <atrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:36:06 by atrouill          #+#    #+#             */
/*   Updated: 2022/05/13 10:31:20 by atrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <string>
# include <vector>
# include "IRC.Class.hpp"
# include "User.Class.hpp"

#if DEBUG
	#include <stdio.h>
	#define _GLIBCXX_DEBUG 1
	#define _GNU_SOURCE 1
	#define debug(x, ...)      do{fprintf(stderr, "%s:%s(%u): " x "\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);}while(0)
#else
	#define debug(x, ...)      /* x */
#endif

/*
** @brief Type of the null pointer constant.
** Permetted implicit conversions to null pointer ,
** similary conversions for all type of contant null pointer.
**
** From : (Take a look)
** https://www.amazon.com/dp/0201924889
*/
static class nullptr_t
{
		public:
				/*
				** @brief For conversion to any type
				** of null non-member pointer.
				*/
				template<class T>
				operator T*() const { return (0); }

				/*
				** @brief For conversion to any type of null
				** member pointer.
				*/
				template<class C, class T>
				operator T C::*() const { return (0); }

		private:

				/*
				** @brief It's imposible to get an address of
				** a nullptr.
				*/
				void operator&() const;

} u_nullptr = {};

#endif
