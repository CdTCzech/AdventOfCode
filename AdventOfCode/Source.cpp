#include <algorithm>
#include <iostream>
#include <string>
#include "FileReader.h"


void day1part1()
{
	for (const auto& line : getLineByLine("day1.txt"))
	{
		int result = 0;

		for (auto character : line)
		{
			if (character == '(') ++result;
			else --result;
		}

		std::cout << result << std::endl;
	}
}

int main()
{
	std::cout << "Day1Part1: "; day1part1();
	system("pause");
	return 0;
}