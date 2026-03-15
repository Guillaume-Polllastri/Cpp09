/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:40:03 by gpollast          #+#    #+#             */
/*   Updated: 2026/03/15 19:34:07 by gpollast         ###   ########.fr       */
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
			throw InvalidDate();
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

static bool	isValidYear(const std::string& year)
{
	for (size_t i = 0; i < year.length(); i++)
	{
		if (!isdigit(year[i]))
			return false;
	}
	return true;
}

static bool	isValidMonth(const std::string& month)
{
	for (size_t i = 0; i < month.size(); i++)
	{
		if (!isdigit(month[i]))
			return false;
	}

	int	month_value = atoi(month.c_str());
	if (month_value <= 0 || month_value > 12)
		return false;
	return true;
}

static bool	isValideDay(const std::string& year, const std::string& month, const std::string& day)
{
	int	year_value = atoi(year.c_str());
	bool	is_bissextil;

	if (year_value % 400 == 0)
		is_bissextil = true;
	else if (year_value % 100 == 0)
		is_bissextil = false;
	else if (year_value % 4 == 0)
		is_bissextil = true;
	else
		is_bissextil = false;

	bool	isThirty = false;
	bool	isThirtyOne = false;
	bool	isTwentyNine = false;
	bool	isTwentyEight = false;
	
	int month_value = atoi(month.c_str());
	if (month_value < 8 && (month_value % 2) != 0)
		isThirtyOne = true;
	else if (month_value > 7 && (month_value % 2) == 0)
		isThirtyOne = true;
	else if (month_value == 2 && is_bissextil)
		isTwentyNine = true;
	else if (month_value == 2 && !is_bissextil)
		isTwentyEight = true;
	else
		isThirty = true;

	int	day_value = atoi(day.c_str());
	if (isThirtyOne && (day_value <= 0 || day_value > 31))
		return false;
	if (isThirty && (day_value <= 0 || day_value > 30))
		return false;
	if (isTwentyNine && (day_value <= 0 || day_value > 29))
		return false;
	if (isTwentyEight && (day_value <= 0 || day_value > 28))
		return false;
		
	return true;
}

static bool	parseDate(const std::string& date)
{
	if (date.length() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;

	std::string	year, month, day;

	year = date.substr(0, 4);
	if (!isValidYear(year))
		return false;
	month = date.substr(5, 2);
	if (!isValidMonth(month))
		return false;
	day = date.substr(8, 2);
	if (!isValideDay(year, month, day))
		return false;
	return true;
}

static bool	parseValue(double value, char *endptr)
{
	if (errno == ERANGE || *endptr != '\0')
	{
		std::cout << "Error: double overflow!" << std::endl;
		return false;
	}
	if (value < 0)
	{
		std::cout << "Error: not a positive number." << std::endl;
		return false;
	}
	if (value > 1000)
	{
		std::cout << "Error: too large a number." << std::endl;
		return false;
	}
	return true;
}

int	BitcoinExchange::processInputFile(const std::string& inputFileName) {
	std::ifstream	inputFile(inputFileName.c_str());
	std::string	line;

	if (!inputFile)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}

	if (!std::getline(inputFile, line) || line != "date | value")
	{
		std::cerr << "Error: invalid header." << std::endl;
		return 1;
	}

	while (std::getline(inputFile, line))
	{
		std::stringstream	ss(line);
		std::string	date, sep, value_str;
		
		if (!(ss >> date >> sep >> value_str) || sep != "|")
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		if (!parseDate(date))
		{
			std::cout << "Error: invalid date => " << date << std::endl;
			continue;	
		}

		char	*endptr;
		double	value = strtod(value_str.c_str(), &endptr);
		
		if (!parseValue(value, endptr))
			continue;
		if (getRateValueFromDate(date) >= 0)
			std::cout << date << " => " << value_str << " = " << value * getRateValueFromDate(date) << std::endl;
	}
	inputFile.close();
	return 0;
}
