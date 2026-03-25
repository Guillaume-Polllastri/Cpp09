/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 20:10:39 by gpollast          #+#    #+#             */
/*   Updated: 2026/03/25 11:37:46 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sstream>
#include <utility>
#include <cstring>

PmergeMe::PmergeMe(std::vector<Chain> vec): _vec(vec), _deq(), _hasRemainingValue(false), _remainingValue(0) {}

PmergeMe::PmergeMe(std::deque<Chain> deq): _vec(), _deq(deq), _hasRemainingValue(false), _remainingValue(0) {}

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

const char* PmergeMe::BadInput::what() const throw() {
	return "Error Please enter a positive integer sequence as an argument";
}

/* ************************************************************************** */
// STD::VECTOR
/* ************************************************************************** */

static	std::vector<Pair>	makePair(std::vector<Chain>& vec, bool& _hasRemainingValue, int& _remainingValue) {
	std::vector<Pair>	pairs;
	pairs.reserve(vec.size() / 2);

	size_t	indexValue = 0;
	size_t		i;
	for (i = 0; (i + 1) < vec.size(); i += 2)
	{
		int a = vec[i].value;
		int	b = vec[i + 1].value;

		Pair	p;
		p.maxValue = a < b ? b : a;
		p.minValue = a < b ? a : b;
		p.index = indexValue;
		indexValue++;
		pairs.push_back(p);
	}
	_hasRemainingValue = (i < vec.size());
	if (_hasRemainingValue)
		_remainingValue = vec[i].value;
	return (pairs);
}

static void insertPairRecursive(std::vector<Pair>& pairs, size_t pos, const Pair& value) {
    if (pos == 0 || pairs[pos - 1].maxValue <= value.maxValue) {
        pairs[pos] = value;
        return;
    }
    pairs[pos] = pairs[pos - 1];
    insertPairRecursive(pairs, pos - 1, value);
}

static void sortPairByMaxValuesRecursive(std::vector<Pair>& pairs, size_t n) {
    if (n <= 1)
        return;

    sortPairByMaxValuesRecursive(pairs, n - 1);

    Pair last = pairs[n - 1];
    insertPairRecursive(pairs, n - 1, last);
}

static void sortPairByMaxValues(std::vector<Pair>& pairs) {
    sortPairByMaxValuesRecursive(pairs, pairs.size());
}

static size_t	searchMaxIndex(const std::vector<Chain>& mainChain, size_t index)
{
	size_t	maxIndex = 0;

	for (std::vector<Chain>::const_iterator it = mainChain.begin(); it != mainChain.end(); it++) {
		if (it->index == index)
			return	maxIndex;
		maxIndex++;
	}
	return maxIndex;
}

static void binaryInsert(std::vector<Chain>& container, Chain newElement) {
    size_t left = 0;
    size_t right = searchMaxIndex(container, newElement.index);
    
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (container[mid].value < newElement.value)
            left = mid + 1;
        else
            right = mid;
    }
    
    container.insert(container.begin() + left, newElement);
}

static std::vector<size_t> generateJacobsthalOrder(size_t size) {
    if (size <= 1)
        return std::vector<size_t>();
    
    std::vector<size_t> order;
    order.push_back(1);
    
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

void	PmergeMe::MergeInsertionSort(std::vector<Chain>& vec) {
	if (vec.size() <= 1)
		return ;
	
	std::vector<Pair>	pairs = makePair(vec, _hasRemainingValue, _remainingValue);
	
	sortPairByMaxValues(pairs);

	std::vector<Chain>	mainChain;
	std::vector<Chain>	pendChain;

	for (size_t i = 0; i < pairs.size(); i++)
	{
		Chain	main, pend;

		main.value = pairs[i].maxValue;
		main.index = i;
		pend.value = pairs[i].minValue;
		pend.index = i;
		mainChain.push_back(main);
		pendChain.push_back(pend);
	}
	if (!pendChain.empty())
		mainChain.insert(mainChain.begin(), pendChain[0]);
	
    std::vector<size_t> insertOrder = generateJacobsthalOrder(pendChain.size());
    
    for (size_t k = 0; k < insertOrder.size(); ++k) {
        binaryInsert(mainChain, pendChain[insertOrder[k]]);
    }
    
    if (_hasRemainingValue) {
		Chain	remaining;

		remaining.index = mainChain.size();
		remaining.value = _remainingValue;
        binaryInsert(mainChain, remaining);
    }
	
    vec = mainChain;
}

/* ************************************************************************** */
// STD::DEQUE
/* ************************************************************************** */

static	std::deque<Pair>	makePair(std::deque<Chain>& vec, bool& _hasRemainingValue, int& _remainingValue) {
    std::deque<Pair>	pairs;

    size_t	indexValue = 0;
    size_t		i;
    for (i = 0; (i + 1) < vec.size(); i += 2)
    {
        int a = vec[i].value;
        int	b = vec[i + 1].value;

        Pair	p;
        p.maxValue = a < b ? b : a;
        p.minValue = a < b ? a : b;
        p.index = indexValue;
        indexValue++;
        pairs.push_back(p);
    }
    _hasRemainingValue = (i < vec.size());
    if (_hasRemainingValue)
        _remainingValue = vec[i].value;
    return (pairs);
}

static void insertPairRecursiveDeque(std::deque<Pair>& pairs, size_t pos, const Pair& value) {
    if (pos == 0 || pairs[pos - 1].maxValue <= value.maxValue) {
        pairs[pos] = value;
        return;
    }
    pairs[pos] = pairs[pos - 1];
    insertPairRecursiveDeque(pairs, pos - 1, value);
}

static void sortPairByMaxValuesRecursiveDeque(std::deque<Pair>& pairs, size_t n) {
    if (n <= 1)
        return;

    sortPairByMaxValuesRecursiveDeque(pairs, n - 1);

    Pair last = pairs[n - 1];
    insertPairRecursiveDeque(pairs, n - 1, last);
}

static void sortPairByMaxValues(std::deque<Pair>& pairs) {
    sortPairByMaxValuesRecursiveDeque(pairs, pairs.size());
}

static size_t	searchMaxIndex(const std::deque<Chain>& mainChain, size_t index)
{
    size_t	maxIndex = 0;

    for (std::deque<Chain>::const_iterator it = mainChain.begin(); it != mainChain.end(); it++) {
        if (it->index == index)
            return	maxIndex;
        maxIndex++;
    }
    return maxIndex;
}

static void binaryInsert(std::deque<Chain>& container, Chain newElement) {
    size_t left = 0;
    size_t right = searchMaxIndex(container, newElement.index);
    
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (container[mid].value < newElement.value)
            left = mid + 1;
        else
            right = mid;
    }
    
    container.insert(container.begin() + left, newElement);
}

static std::deque<size_t> generateJacobsthalOrderDeque(size_t size) {
    if (size <= 1)
        return std::deque<size_t>();
    
    std::deque<size_t> order;
    order.push_back(1);
    
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

void	PmergeMe::MergeInsertionSort(std::deque<Chain>& vec) {
    if (vec.size() <= 1)
        return ;
    
    std::deque<Pair>	pairs = makePair(vec, _hasRemainingValue, _remainingValue);
    
    sortPairByMaxValues(pairs);

    std::deque<Chain>	mainChain;
    std::deque<Chain>	pendChain;

    for (size_t i = 0; i < pairs.size(); i++)
    {
        Chain	main, pend;

        main.value = pairs[i].maxValue;
        main.index = i;
        pend.value = pairs[i].minValue;
        pend.index = i;
        mainChain.push_back(main);
        pendChain.push_back(pend);
    }
    if (!pendChain.empty())
        mainChain.insert(mainChain.begin(), pendChain[0]);
    
    std::deque<size_t> insertOrder = generateJacobsthalOrderDeque(pendChain.size());
    
    for (size_t k = 0; k < insertOrder.size(); ++k) {
        binaryInsert(mainChain, pendChain[insertOrder[k]]);
    }
    
    if (_hasRemainingValue) {
        Chain	remaining;

        remaining.index = mainChain.size();
        remaining.value = _remainingValue;
        binaryInsert(mainChain, remaining);
    }
    
    vec = mainChain;
}
