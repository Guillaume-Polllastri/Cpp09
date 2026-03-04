/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 13:52:23 by gpollast          #+#    #+#             */
/*   Updated: 2026/03/04 18:39:00 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int main(int ac, char **av)
{
    if (ac != 2)
        return (1);
    try
    {
        RPN::rpn(av[1]);
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return (0);
}
