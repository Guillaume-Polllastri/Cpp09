/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 13:51:36 by gpollast          #+#    #+#             */
/*   Updated: 2026/03/05 10:37:03 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <list>
#include <iostream>
#include <sstream>
#include <stdbool.h>
#include <cstring>

RPN::RPN() {}

RPN::RPN(const RPN& copy) {
    (void) copy;
}

RPN&    RPN::operator=(const RPN& other) {
    (void)other;
    return *this;
}

RPN::~RPN() {}

static bool isOperator(char c)
{
    if (strchr("+ - / *", c))
        return true;
    return false;
}

static void	rpnCalculator(std::list<int>& lst, char c)
{
	int	a = lst.back();
	lst.pop_back();
	int	b = lst.back();
	lst.pop_back();
	int result = 0;
	switch (c)
	{
		case ('+'):
			result = b + a;
			break;
		case ('-'):
			result = b - a;
			break;
		case ('/'):
			if (a == 0)
				throw RPN::DivideByZero();
			result = b / a;
			break;
		case ('*'):
			result = b * a;
	}
	lst.push_back(result);
}

static void	printRPNResult(std::list<int>& lst)
{
    for (std::list<int>::iterator it = lst.begin(); it != lst.end(); it++)
        std::cout << *it << ' ';
    std::cout << std::endl;
}

void RPN::rpn(const std::string& str) {
    std::list<int>  lst;
    std::stringstream ss(str);
    std::string token;
    
    while (ss >> token)
    {
        if (token.size() > 1)
            throw BadInput();
        if (isdigit(token[0]))
            lst.push_back(token[0] - '0');
        else if (isOperator(token[0]) && lst.size() >= 2)
			rpnCalculator(lst, token[0]);
        else
            throw BadInput();
    }
	printRPNResult(lst);
}
