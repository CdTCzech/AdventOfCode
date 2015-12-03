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

void day1part2()
{
	for (const auto& line : getLineByLine("day1.txt"))
	{
		int floor = 0, result = 0;

		for (size_t i = 0; i < line.size(); ++i)
		{
			if (line[i] == '(') ++floor;
			else --floor;

			if (floor == -1)
			{
				result = i;
				break;
			}
		}

		std::cout << result + 1 << std::endl;
	}
}

int main()
{
	std::cout << "Day1Part1: "; day1part1();
	std::cout << "Day1Part2: "; day1part2();
	system("pause");
	return 0;
}