/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:40:03 by gpollast          #+#    #+#             */
/*   Updated: 2026/03/12 19:01:40 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy): _data(copy._data) {}

BitcoinExchange&	BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other)
	{
		_data = other._data;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

int	BitcoinExchange::fillData(const std::string& fileData) {
	std::ifstream	file(fileData.c_str());
	
	if (!file)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}
	
	std::string	line;
	while (std::getline(file, line))
	{
		// std::cout << line << std::endl;
		std::string	date, valueRate;
		
		std::size_t	sep = line.find(',');
		date = line.substr(0, sep);
		valueRate = line.substr(sep + 1);
		_data[date] = std::strtod(valueRate.c_str(), NULL);
	}
	file.close();
	return 0;
}

double	BitcoinExchange::getRateValueFromDate(const std::string& date) {
	try
	{
		std::map<std::string, double>::iterator	it = _data.lower_bound(date);
		
		if (it != _data.end() && it->first == date)
			return it->second;
		else if (it == _data.begin())
			throw BadInput();
		else
		{
			--it;
			return it->second;
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << date << std::endl;
		return -1;
	}
}

int	BitcoinExchange::readInputFile(const std::string& inputFileName) {
	std::ifstream	inputFile(inputFileName.c_str());
	std::string	line;

	if (!inputFile)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}
	while (std::getline(inputFile, line))
	{
		std::stringstream	ss(line);
		std::string	date, sep, value;
		
		if (!(ss >> date >> sep >> value) || sep != "|")
		{
			std::cerr << "Error: missing element in " << inputFileName << std::endl;
			break;
		}
		_data[date] = std::strtod(value.c_str(), NULL);
		std::cout << line << std::endl;	
	}
	inputFile.close();
	return 0;
}
