#include "Day1.h"

#include "FileReader.h"

namespace day1
{
	int64_t part1()
	{
		const auto& line = getLine("day1.txt");
		int64_t result = 0;

		for (auto character : line)
		{
			if (character == '(') { ++result; }
			else { --result; }
		}

		return result;
	}

	int64_t part2()
	{
		const auto& line = getLine("day1.txt");
		int floor = 0;
		int64_t result = 0;

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

		return result + 1;
	}
}  // namespace day1