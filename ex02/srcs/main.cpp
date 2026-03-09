/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 20:09:27 by gpollast          #+#    #+#             */
/*   Updated: 2026/03/09 18:20:09 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main(int ac, char **av)
{
	try
	{
		if (ac < 2)
			throw PmergeMe::BadInput();
	
		std::vector<int>	vec;
		
		PmergeMe	p1(vec);
		p1.setContainer(vec, av);
		p1.MergeInsertionSort(vec);
		p1.printContainer(vec.begin(), vec.end());

		std::deque<int>		deq;
		PmergeMe	p2(deq);
		p2.setContainer(deq, av);
		p2.MergeInsertionSort(deq);
		p2.printContainer(deq.begin(), deq.end());
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}