/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 20:10:39 by gpollast          #+#    #+#             */
/*   Updated: 2026/03/09 18:19:45 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sstream>
#include <utility>

PmergeMe::PmergeMe(std::vector<int> vec): _vec(vec), _deq(), _hasRemainingValue(false), _remainingValue(0) {}

PmergeMe::PmergeMe(std::deque<int> deq): _vec(), _deq(deq), _hasRemainingValue(false), _remainingValue(0) {}

PmergeMe::PmergeMe(const PmergeMe& copy): _vec(copy._vec), _deq(copy._deq), _hasRemainingValue(copy._hasRemainingValue), _remainingValue(copy._remainingValue) {}

PmergeMe&	PmergeMe::operator=(const PmergeMe& other) {
	if (this != &other)
	{
		_vec = other._vec;
		_deq = other._deq;
		_hasRemainingValue = other._hasRemainingValue;
		_remainingValue = other._remainingValue;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

/* ************************************************************************** */
// STD::VECTOR
/* ************************************************************************** */

static	std::vector<Pair>	makePair(std::vector<int>& vec, bool& _hasRemainingValue, int& _remainingValue) {
	std::vector<Pair>	pairs;
	pairs.reserve(vec.size() / 2);

	size_t	indexValue = 0;
	size_t		i;
	for (i = 0; (i + 1) < vec.size(); i += 2)
	{
		int a = vec[i];
		int	b = vec[i + 1];

		Pair	p;
		p.maxValue = a < b ? b : a;
		p.minValue = a < b ? a : b;
		p.index = indexValue;
		indexValue++;
		pairs.push_back(p);
	}
	_hasRemainingValue = (i < vec.size());
	if (_hasRemainingValue)
		_remainingValue = vec[i];
	return (pairs);
}

static void	sortPairByMaxValues(std::vector<Pair>& pairs) {
	for (size_t x = 1; x < pairs.size(); x++)
	{
		Pair p = pairs[x];
		int y = x;
		while (y > 0 && pairs[y - 1].maxValue > p.maxValue)
		{
			pairs[y] = pairs[y - 1];
			y--;
		}
		pairs[y] = p;
	}
}

static void binaryInsert(std::vector<int>& container, int value) {
    size_t left = 0;
    size_t right = container.size();
    
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (container[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }
    
    container.insert(container.begin() + left, value);
}

static std::vector<size_t> generateJacobsthalOrder(size_t size) {
    if (size == 0)
        return std::vector<size_t>();
    
    std::vector<size_t> order;
    order.push_back(1);
    
    if (size == 1)
        return order;
    
    size_t jacob_prev = 1;
    size_t jacob_curr = 1;
    
    while (jacob_curr < size) {
        size_t jacob_next = jacob_curr + 2 * jacob_prev;
        size_t limit = jacob_next < size ? jacob_next : size - 1;
        
        for (size_t i = limit; i > jacob_curr; --i) {
            order.push_back(i);
        }
        
        jacob_prev = jacob_curr;
        jacob_curr = jacob_next;
    }
    
    return order;
}

void	PmergeMe::MergeInsertionSort(std::vector<int>& vec) {
	if (vec.size() <= 1)
		return ;
	
	std::vector<Pair>	pairs = makePair(vec, _hasRemainingValue, _remainingValue);
	
	sortPairByMaxValues(pairs);

	std::vector<int>	mainChain;
	std::vector<int>	pendChain;

	for (size_t i = 0; i < pairs.size(); i++)
	{
		mainChain.push_back(pairs[i].maxValue);
		pendChain.push_back(pairs[i].minValue);
	}
	if (!pendChain.empty())
		mainChain.insert(mainChain.begin(), pendChain[0]);
	
    std::vector<size_t> insertOrder = generateJacobsthalOrder(pendChain.size());
    
    for (size_t k = 0; k < insertOrder.size(); ++k) {
        binaryInsert(mainChain, pendChain[insertOrder[k]]);
    }
    
    if (_hasRemainingValue) {
        binaryInsert(mainChain, _remainingValue);
    }
	
    vec = mainChain;
}

/* ************************************************************************** */
// STD::DEQUE
/* ************************************************************************** */

static std::deque<Pair> makePair(std::deque<int>& deq, bool& _hasRemainingValue, int& _remainingValue) {
    std::deque<Pair> pairs;

    size_t	indexValue = 0;
    size_t	i;
    for (i = 0; (i + 1) < deq.size(); i += 2)
    {
        int a = deq[i];
        int	b = deq[i + 1];

        Pair	p;
        p.maxValue = a < b ? b : a;
        p.minValue = a < b ? a : b;
        p.index = indexValue;
        indexValue++;
        pairs.push_back(p);
    }
    _hasRemainingValue = (i < deq.size());
    if (_hasRemainingValue)
        _remainingValue = deq[i];
    return (pairs);
}

static void	sortPairByMaxValues(std::deque<Pair>& pairs) {
    for (size_t x = 1; x < pairs.size(); x++)
    {
        Pair p = pairs[x];
        int y = x;
        while (y > 0 && pairs[y - 1].maxValue > p.maxValue)
        {
            pairs[y] = pairs[y - 1];
            y--;
        }
        pairs[y] = p;
    }
}

static void binaryInsert(std::deque<int>& container, int value) {
    size_t left = 0;
    size_t right = container.size();

    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (container[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }

    container.insert(container.begin() + left, value);
}

static std::deque<size_t> generateJacobsthalOrderDeque(size_t size) {
    if (size == 0)
        return std::deque<size_t>();

    std::deque<size_t> order;
    order.push_back(1);

    if (size == 1)
        return order;

    size_t jacob_prev = 1;
    size_t jacob_curr = 1;

    while (jacob_curr < size) {
        size_t jacob_next = jacob_curr + 2 * jacob_prev;
        size_t limit = jacob_next < size ? jacob_next : size - 1;

        for (size_t i = limit; i > jacob_curr; --i) {
            order.push_back(i);
        }

        jacob_prev = jacob_curr;
        jacob_curr = jacob_next;
    }

    return order;
}

void	PmergeMe::MergeInsertionSort(std::deque<int>& deq) {
    if (deq.size() <= 1)
        return ;

    std::deque<Pair> pairs = makePair(deq, _hasRemainingValue, _remainingValue);

    sortPairByMaxValues(pairs);

    std::deque<int> mainChain;
    std::deque<int> pendChain;

    for (size_t i = 0; i < pairs.size(); i++)
    {
        mainChain.push_back(pairs[i].maxValue);
        pendChain.push_back(pairs[i].minValue);
    }
    if (!pendChain.empty())
        mainChain.insert(mainChain.begin(), pendChain[0]);

    std::deque<size_t> insertOrder = generateJacobsthalOrderDeque(pendChain.size());

    for (size_t k = 0; k < insertOrder.size(); ++k) {
        binaryInsert(mainChain, pendChain[insertOrder[k]]);
    }

    if (_hasRemainingValue) {
        binaryInsert(mainChain, _remainingValue);
    }

    deq = mainChain;
}
