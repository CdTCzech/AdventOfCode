#pragma once

#include <experimental/generator>
#include <fstream>
#include <functional>
#include <string>
#include <vector>


template <typename T>
std::experimental::generator<std::vector<T>> getLineByLine(std::string filename,
	std::function<std::vector<T>(std::string&)> func = [](std::string& var) { return std::vector<T>(); })
{
	std::ifstream infile(filename);
	std::string line;

	while (getline(infile, line))
	{
		yield func(line);
	}
}

auto getLineByLine(std::string filename)
{
	std::ifstream infile(filename);
	std::string line;

	while (getline(infile, line))
	{
		yield line;
	}
}