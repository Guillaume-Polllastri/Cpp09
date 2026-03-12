/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:38:42 by gpollast          #+#    #+#             */
/*   Updated: 2026/03/12 19:02:57 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

#include <iostream>

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Error: could not open filee." << std::endl;
		return (1);
	}
	BitcoinExchange	be;
	be.fillData("data.csv");
	be.readInputFile(av[1]);
	// if (be.getRateValueFromDate("2000-01-06") >= 0)
	// 	std::cout << be.getRateValueFromDate("2000-01-06") << std::endl;
	return (0);
}
