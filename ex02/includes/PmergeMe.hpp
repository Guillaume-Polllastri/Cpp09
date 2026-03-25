/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 20:10:42 by gpollast          #+#    #+#             */
/*   Updated: 2026/03/25 11:37:20 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <deque>
#include <iostream>
#include <exception>
#include <cstdlib>
#include <climits>
#include <cerrno>

struct Pair {
	int		maxValue;
	int		minValue;
	size_t	index;
};

struct Chain {
	int		value;
	size_t	index;
};

class PmergeMe {
	public:
	PmergeMe(std::vector<Chain> vec);
	PmergeMe(std::deque<Chain> deq);
	PmergeMe(const PmergeMe& copy);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();
	

	template<typename Container>
	void	printContainer(const Container& begin, const Container& end) {
		Container	it;
		for (it = begin; it != end; it++)
		{
			std::cout << it->value << ' ';
		}
		std::cout << std::endl;
	};

	template<typename Container>
	void	setContainer(Container& deq, char **av) {
		int	i = 1;
	
	    while (av[i])
	    {
        	errno = 0;
        	char* end;
        	long tmp = std::strtol(av[i], &end, 10);
			
        	if (end == av[i] || *end != '\0')
        	    throw PmergeMe::BadInput();
        	if (errno == ERANGE)
        	    throw PmergeMe::BadInput();
        	if (tmp > INT_MAX || tmp < 0)
        	    throw PmergeMe::BadInput();
			Chain	tmpChain;
			tmpChain.value = static_cast<int>(tmp);
			tmpChain.index = i;
        	deq.push_back(tmpChain);
			i++;
	    }
	}

	void	MergeInsertionSort(std::vector<Chain>& vec);
	void	MergeInsertionSort(std::deque<Chain>& deq);
	
	class BadInput: public std::exception
	{
		public:
			virtual const char* what() const throw();
	};
	private:
		std::vector<Chain>	_vec;
		std::deque<Chain>	_deq;
		bool				_hasRemainingValue;
		int					_remainingValue;
};
