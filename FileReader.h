#pragma once

#include "Utils.h"

#include <experimental/generator>

#include <fstream>
#include <functional>
#include <string>


template <typename T = std::string>
auto getLine(const std::string filename, std::function<T(std::string&)> func = [](std::string& var) { return var; })
{
	std::ifstream infile(filename);

	if (!infile.good())
	{
		throw EXCEPTION("Reading file " + filename);
	}

	std::string line;

	std::getline(infile, line);
	return func(line);
}

template <typename T = std::string>
std::experimental::generator<T> getLineByLine(const std::string filename, std::function<T(std::string&)> func = [](std::string& var) { return var; })
{
	std::ifstream infile(filename);

	if (!infile.good())
	{
		throw EXCEPTION("Reading file " + filename);
	}

	std::string line;

	while (std::getline(infile, line))
	{
		co_yield func(line);
	}
}
