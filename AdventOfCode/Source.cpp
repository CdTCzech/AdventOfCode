#include <algorithm>
#include <iostream>
#include <sstream>
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

void day2part1()
{
	auto result = 0;

	for (const auto& line : getLineByLine<int>("day2.txt", [](std::string& var)
	{
		std::vector<int> dimensions;
		std::replace(var.begin(), var.end(), 'x', ' ');
		std::istringstream iss(var);
		int l, w, h;
		iss >> l >> w >> h;
		dimensions.push_back(l);
		dimensions.push_back(w);
		dimensions.push_back(h);
		return dimensions;
	}))
	{
		auto sideA = line[0] * line[1];
		auto sideB = line[0] * line[2];
		auto sideC = line[1] * line[2];
		auto sideM = std::min(sideA, std::min(sideB, sideC));
		result += 2 * sideA + 2 * sideB + 2 * sideC + sideM;
	}

	std::cout << result << std::endl;
}

int main()
{
	std::cout << "Day1Part1: "; day1part1();
	std::cout << "Day1Part2: "; day1part2();
	std::cout << "Day2Part1: "; day2part1();
	system("pause");
	return 0;
}