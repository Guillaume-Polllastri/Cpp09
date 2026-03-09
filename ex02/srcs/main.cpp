/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 20:09:27 by gpollast          #+#    #+#             */
/*   Updated: 2026/03/09 18:50:57 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <ctime>
#include <iomanip>

int	main(int ac, char **av)
{
	try
	{
		if (ac < 2)
			throw PmergeMe::BadInput();
	
		std::vector<int>	vec;
		
		PmergeMe	p1(vec);
		p1.setContainer(vec, av);
		std::cout << "Before: ";
		p1.printContainer(vec.begin(), vec.end());

		clock_t	startVector = clock();
		p1.MergeInsertionSort(vec);
		clock_t	endVector = clock();

		std::cout << "After:  ";
		p1.printContainer(vec.begin(), vec.end());

		std::deque<int>		deq;
		PmergeMe	p2(deq);
		p2.setContainer(deq, av);

		clock_t	startDeque = clock();
		p2.MergeInsertionSort(deq);
		clock_t	endDeque = clock();

		double	timeVector = static_cast<double>(endVector - startVector) / CLOCKS_PER_SEC * 1000000;
		double	timeDeque = static_cast<double>(endDeque - startDeque) / CLOCKS_PER_SEC * 1000000;

		std::cout << std::fixed << std::setprecision(5);
        std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : " << timeVector << " us" << std::endl;
        std::cout << "Time to process a range of " << deq.size() << " elements with std::deque : " << timeDeque << " us" << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}