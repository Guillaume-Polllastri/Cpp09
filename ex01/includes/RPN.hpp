/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 13:52:14 by gpollast          #+#    #+#             */
/*   Updated: 2026/03/25 11:47:44 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>
#include <string>
#include <exception>

class RPN {
    private:
        RPN();
        RPN(const RPN& copy);
        RPN& operator=(const RPN& other);
        ~RPN();
    
    public:
        static void rpn(const std::string& str);
        
    	class BadInput: public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class DivideByZero: public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		class IntOverflow: public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
};