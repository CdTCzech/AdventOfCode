#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>

#include "Libraries/md5.h"
#include "FileReader.h"


namespace day1
{
	void part1()
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

	void part2()
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
}

namespace day2
{
	struct Dimensions
	{
		int l;
		int w;
		int h;
	};

	void part1()
	{
		auto result = 0;

		for (const auto& line : getLineByLine<Dimensions>("day2.txt", [](std::string& var)
		{
			std::replace(var.begin(), var.end(), 'x', ' ');
			std::istringstream iss(var);
			int l, w, h;
			iss >> l >> w >> h;
			return Dimensions{ l, w, h };
		}))
		{
			auto sideA = line.l * line.w;
			auto sideB = line.l * line.h;
			auto sideC = line.w * line.h;
			auto sideM = std::min(sideA, std::min(sideB, sideC));
			result += 2 * sideA + 2 * sideB + 2 * sideC + sideM;
		}

		std::cout << result << std::endl;
	}

	void part2()
	{
		auto result = 0;

		for (const auto& line : getLineByLine<Dimensions>("day2.txt", [](std::string& var)
		{
			std::replace(var.begin(), var.end(), 'x', ' ');
			std::istringstream iss(var);
			int l, w, h;
			iss >> l >> w >> h;
			return Dimensions{ l, w, h };
		}))
		{
			auto ribbon = (line.l + line.w + line.h - std::max(line.l, std::max(line.w, line.h))) * 2;
			auto bow = line.l * line.w * line.h;
			result += ribbon + bow;
		}

		std::cout << result << std::endl;
	}
}

namespace day3
{
	struct Point
	{
		int x;
		int y;

		bool operator< (const Point& other) const
		{
			if (x < other.x) return true;
			if (x == other.x && y < other.y) return true;
			return false;
		}
	};

	void part1()
	{
		Point currentPosition{ 0, 0 };
		std::set<Point> points;

		for (const auto& line : getLineByLine("day3.txt"))
		{
			for (auto character : line)
			{
				points.insert(currentPosition);

				if (character == '^') ++currentPosition.y;
				else if (character == 'v') --currentPosition.y;
				else if (character == '<') --currentPosition.x;
				else if (character == '>') ++currentPosition.x;
			}

			std::cout << points.size() << std::endl;
		}
	}

	void part2()
	{
		Point currentPositionSanta{ 0, 0 };
		Point currentPositionRobo{ 0, 0 };
		Point* current;
		std::set<Point> points;

		for (const auto& line : getLineByLine("day3.txt"))
		{
			bool isSantaTurn = true;
			for (auto character : line)
			{
				if (isSantaTurn) current = &currentPositionSanta;
				else current = &currentPositionRobo;

				isSantaTurn = !isSantaTurn;

				points.insert(*current);

				if (character == '^') ++current->y;
				else if (character == 'v') --current->y;
				else if (character == '<') --current->x;
				else if (character == '>') ++current->x;
			}

			std::cout << points.size() << std::endl;
		}
	}
}

namespace day4
{
	void part1()
	{
		for (const auto& line : getLineByLine("day4.txt"))
		{
			for (unsigned int number = 0; number < 1000000; ++number)
			{
				auto hash = md5(line + std::to_string(number));
				if (hash.substr(0, 5) == "00000")
				{
					std::cout << std::to_string(number) << std::endl;
					break;
				}
			}
		}
	}

	void part2()
	{
		for (const auto& line : getLineByLine("day4.txt"))
		{
			for (unsigned int number = 282749; number < 10000000; ++number)
			{
				auto hash = md5(line + std::to_string(number));
				if (hash.substr(0, 6) == "000000")
				{
					std::cout << std::to_string(number) << std::endl;
					break;
				}
			}
		}
	}
}

int main()
{
	std::cout << "Day1Part1: "; day1::part1();
	std::cout << "Day1Part2: "; day1::part2();
	std::cout << "Day2Part1: "; day2::part1();
	std::cout << "Day2Part2: "; day2::part2();
	std::cout << "Day3Part1: "; day3::part1();
	std::cout << "Day3Part2: "; day3::part2();
	std::cout << "Day4Part1: "; day4::part1();
	std::cout << "Day4Part2: "; day4::part2();
	system("pause");
	return 0;
}
