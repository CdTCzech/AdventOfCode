#pragma once

#include "Utils.h"

#include <experimental/generator>
#include <fstream>
#include <functional>
#include <string>


template <typename T = std::string>
auto getLine(const char* filename, std::function<T(std::string&)> func = [](std::string& var) { return var; })
{
	std::ifstream infile(filename);

	if (!infile.good())
	{
		throw utils::AoCException(std::string("Reading file") + filename, __FILE__, __LINE__);
	}

	std::string line;

	std::getline(infile, line);
	return func(line);
}

template <typename T = std::string>
std::experimental::generator<T> getLineByLine(const char* filename, std::function<T(std::string&)> func = [](std::string& var) { return var; })
{
	std::ifstream infile(filename);

	if (!infile.good())
	{
		throw utils::AoCException(std::string("Reading file") + filename, __FILE__, __LINE__);
	}

	std::string line;

	while (std::getline(infile, line))
	{
		co_yield func(line);
	}
}
