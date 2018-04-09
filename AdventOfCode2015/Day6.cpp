#include "Day6.h"

#include "FileReader.h"

#include <algorithm>
#include <sstream>

namespace day6
{
	int64_t part1()
	{
		std::vector<std::vector<bool>> grid(1000, std::vector<bool>(1000, false));
		int64_t result = 0;

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
					if (line.type == Type::toggle) grid[y][x] = !grid[y][x];
					else if (line.type == Type::off) grid[y][x] = false;
					else grid[y][x] = true;
				}
			}
		}

		for (const auto& y : grid)
		{
			for (const auto x : y)
			{
				if (x) ++result;
			}
		}

		return result;
	}

	int64_t part2()
	{
		std::vector<std::vector<int>> grid(1000, std::vector<int>(1000, 0));
		int64_t result = 0;

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

		for (const auto& y : grid)
		{
			for (const auto x : y)
			{
				result += x;
			}
		}

		return result;
	}
}  // namespace day6