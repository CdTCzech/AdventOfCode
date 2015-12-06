#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

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

namespace day5
{
	void part1()
	{
		int result = 0;

		for (const auto& line : getLineByLine("day5.txt"))
		{
			int vowels = 0;
			bool twice = false;
			bool banned = false;
			char previous = '\0';

			for (const auto& character : line)
			{
				if (character == 'a' || character == 'e' || character == 'i'
					|| character == 'o' || character == 'u')
					++vowels;

				if (previous == character) twice = true;

				if ((previous == 'a' && character == 'b') ||
					(previous == 'c' && character == 'd') ||
					(previous == 'p' && character == 'q') ||
					(previous == 'x' && character == 'y'))
					banned = true;

				previous = character;
			}

			if (vowels >= 3 && twice && !banned) ++result;
		}

		std::cout << result << std::endl;
	}

	void part2()
	{
		int result = 0;

		for (const auto& line : getLineByLine("day5.txt"))
		{
			bool pair = false;
			bool between = false;

			for (unsigned int i = 0; i < line.size() - 2; ++i)
			{
				if (line[i] == line[i + 2])
				{
					between = true;
					break;
				}
			}

			for (unsigned int i = 0; i < line.size() - 3; ++i)
			{
				bool end = false;

				for (auto j = i + 2; j < line.size() - 1; ++j)
				{
					if (line[i] == line[j] && line[i + 1] == line[j + 1])
					{
						pair = true;
						end = true;
						break;
					}
				}

				if (end == true) break;
			}

			if (pair && between) ++result;
		}

		std::cout << result << std::endl;
	}
}

namespace day6
{
	enum class Type
	{
		on,
		off,
		toggle
	};

	struct Command
	{
		day3::Point start;
		day3::Point end;
		Type type;
	};

	void part1()
	{
		std::vector<std::vector<bool>> grid(1000, std::vector<bool>(1000, false));
		unsigned int result = 0;

		for (const auto& line : getLineByLine<Command>("day6.txt", [] (std::string& var)
		{
			std::replace(var.begin(), var.end(), ',', ' ');
			std::istringstream iss(var);
			std::string buffer;
			Command command;
			if (var[1] == 'o')
			{
				command.type = Type::toggle;
				iss >> buffer >> command.start.x >> command.start.y >> buffer >> command.end.x >> command.end.y;
			}
			else
			{
				command.type = (var[6] == 'f') ? Type::off : Type::on;
				iss >> buffer >> buffer >> command.start.x >> command.start.y >> buffer >> command.end.x >> command.end.y;
			}
			return command;
		}))
		{
			for (auto y = line.start.y; y <= line.end.y; ++y)
			{
				for (auto x = line.start.x; x <= line.end.x; ++x)
				{
					if (line.type == Type::toggle) grid[y][x] = !grid[y][x];
					else if (line.type == Type::off) grid[y][x] = false;
					else grid[y][x] = true;
				}
			}
		}

		for (const auto y : grid)
		{
			for (const auto x : y)
			{
				if (x == true) ++result;
			}
		}

		std::cout << result << std::endl;
	}

	void part2()
	{
		std::vector<std::vector<int>> grid(1000, std::vector<int>(1000, 0));
		unsigned int result = 0;

		for (const auto& line : getLineByLine<Command>("day6.txt", [](std::string& var)
		{
			std::replace(var.begin(), var.end(), ',', ' ');
			std::istringstream iss(var);
			std::string buffer;
			Command command;
			if (var[1] == 'o')
			{
				command.type = Type::toggle;
				iss >> buffer >> command.start.x >> command.start.y >> buffer >> command.end.x >> command.end.y;
			}
			else
			{
				command.type = (var[6] == 'f') ? Type::off : Type::on;
				iss >> buffer >> buffer >> command.start.x >> command.start.y >> buffer >> command.end.x >> command.end.y;
			}
			return command;
		}))
		{
			for (auto y = line.start.y; y <= line.end.y; ++y)
			{
				for (auto x = line.start.x; x <= line.end.x; ++x)
				{
					if (line.type == Type::toggle) grid[y][x] += 2;
					else if (line.type == Type::on) grid[y][x] += 1;
					else
					{
						if (grid[y][x] > 0) grid[y][x] -= 1;
					}
				}
			}
		}

		for (const auto y : grid)
		{
			for (const auto x : y)
			{
				result += x;
			}
		}

		std::cout << result << std::endl;
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
	std::cout << "Day5Part1: "; day5::part1();
	std::cout << "Day5Part2: "; day5::part2();
	std::cout << "Day6Part1: "; day6::part1();
	std::cout << "Day6Part2: "; day6::part2();
	system("pause");
	return 0;
}
 