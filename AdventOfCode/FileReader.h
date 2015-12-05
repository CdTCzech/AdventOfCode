#pragma once

#include <experimental/generator>
#include <fstream>
#include <functional>
#include <string>


template <typename T = std::string>
auto getLineByLine(std::string filename, std::function<T(std::string&)> func = [] (std::string& var) { return var; } )
{
	std::ifstream infile(filename);
	std::string line;

	while (getline(infile, line))
	{
		yield func(line);
	}
}
