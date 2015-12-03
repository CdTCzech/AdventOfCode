#pragma once

#include <experimental/generator>
#include <fstream>
#include <string>


auto getLineByLine(std::string filename)
{
	std::ifstream infile(filename);
	std::string line;

	while (getline(infile, line))
	{
		yield line;
	}
}