/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 20:10:42 by gpollast          #+#    #+#             */
/*   Updated: 2026/03/09 18:19:43 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <deque>
#include <iostream>
#include <exception>
#include <cstdlib>

struct Pair {
	int		maxValue;
	int		minValue;
	size_t	index;
};

class PmergeMe {
	public:
	PmergeMe(std::vector<int> vec);
	PmergeMe(std::deque<int> deq);
	PmergeMe(const PmergeMe& copy);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();
	

	template<typename Container>
	void	printContainer(const Container& begin, const Container& end) {
		Container	it;
		for (it = begin; it != end; it++)
		{
			std::cout << *it << ' ';
		}
		std::cout << std::endl;
	};

	template<typename Container>
	void	setContainer(Container& deq, char **av) {
		int	i = 1;
	
	    while (av[i])
	    {
	        // if (token.size() > 1) PARSING à faire plus tard
	        //     throw PmergeMe::BadInput();
	        deq.push_back(atoi(av[i]));
			i++;
	    }
	}

	void	MergeInsertionSort(std::vector<int>& vec);
	void	MergeInsertionSort(std::deque<int>& deq);
	
	class BadInput: public std::exception
	{
		public:
			virtual const char* what() const throw() {
				return "Error Please enter a positive integer sequence as an argument";
			}
	};
	private:
		std::vector<int>	_vec;
		std::deque<int>		_deq;
		bool				_hasRemainingValue;
		int					_remainingValue;
};
