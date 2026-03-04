/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 13:51:36 by gpollast          #+#    #+#             */
/*   Updated: 2026/03/04 19:07:57 by gpollast         ###   ########.fr       */
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

void RPN::rpn(const std::string& str) {
    std::list<int>  lst;
    std::stringstream ss(str);
    std::string token;
    
    while (ss >> token)
    {
        if (token.size() > 1)
            throw BadInput();
        if (isdigit(token[0]))
        {
            lst.push_front(token[0] - '0');
            // std::cout << token << std::endl;
        }
        else if (isOperator(token[0]) && lst.size() >= 2)
            std::cout << token[0] << std::endl;
        else
            throw BadInput();
    }
    for (std::list<int>::iterator it = lst.begin(); it != lst.end(); it++)
        std::cout << *it << std::endl;
    // std::cout << str << std::endl;
}
