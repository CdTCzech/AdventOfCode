#include "Day20.h"

#include "../FileReader.h"

#include <algorithm>

namespace day20
{
	int64_t part1()
	{
		const auto line = getLine<int>("Days\\day20.txt", [](std::string& var) { return std::stoi(var); });
		const auto size = line / 10;

		std::vector<int> houses(size, 0);

		for (auto i = 1; i <= size; ++i)
		{
			const auto value = i * 10;
			for (auto j = 1; j <= (size / i); ++j)
			{
				houses[i * j - 1] += value;
			}

			if (houses[i - 1] >= line)
			{
				return i;
			}
		}

		return 0;
	}

	int64_t part2()
	{
		const auto line = getLine<int>("Days\\day20.txt", [](std::string& var) { return std::stoi(var); });
		const auto size = line / 11;

		std::vector<int> houses(size, 0);

		for (auto i = 1; i <= size; ++i)
		{
			const auto value = i * 11;
			for (auto j = 1; j <= std::min((size / i), 50); ++j)
			{
				houses[i * j - 1] += value;
			}

			if (houses[i - 1] >= line)
			{
				return i;
			}
		}

		return 0;
	}
} // namespace day20