/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:39:57 by gpollast          #+#    #+#             */
/*   Updated: 2026/03/12 19:01:16 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <string>
#include <exception>

class BitcoinExchange {
	private:
		std::map<std::string, double>	_data;
	
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& copy);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();

		int	fillData(const std::string& fileData);
		double	getRateValueFromDate(const std::string& date);
		int	readInputFile(const std::string& inputFileName);
	
		class BadInput: public std::exception
		{
			public:
				virtual const char* what() const throw() {
					return "Error: bad input => ";
				}
		};
};

