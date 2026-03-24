/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 13:52:23 by gpollast          #+#    #+#             */
/*   Updated: 2026/03/24 09:46:19 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int main(int ac, char **av)
{
    if (ac != 2)
	{
		std::cerr << "Error the program need 1 parameter" << std::endl;
        return (1);
	}
    try
    {
        RPN::rpn(av[1]);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return (0);
}
