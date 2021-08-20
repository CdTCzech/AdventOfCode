#include "Day15.h"

#include "../FileReader.h"

#include <algorithm>
#include <iterator>
#include <sstream>

namespace day15
{
	int64_t part1()
	{
		std::vector<Cookie> cookies;
		int64_t result = 0;

		for (const auto& line : getLineByLine<Cookie>("Days\\day15.txt", [](std::string& var)
		{
			std::replace(var.begin(), var.end(), ',', ' ');
			std::istringstream iss(var);
			std::vector<std::string> splitted(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
			return Cookie{ std::stoi(splitted[2]), std::stoi(splitted[4]), std::stoi(splitted[6]), std::stoi(splitted[8]), std::stoi(splitted[10]) };
		}))
		{
			cookies.push_back(line);
		}

		for (auto i = 1; i <= 100; ++i)
		{
			for (auto j = 1; j <= 100 - i; ++j)
			{
				for (auto k = 1; k <= 100 - i - j; ++k)
				{
					const auto l = 100 - i - j - k;

					const int64_t capacity = i * cookies[0].capacity + j * cookies[1].capacity + k * cookies[2].capacity + l * cookies[3].capacity;
					const int64_t durability = i * cookies[0].durability + j * cookies[1].durability + k * cookies[2].durability + l * cookies[3].durability;
					const int64_t flavor = i * cookies[0].flavor + j * cookies[1].flavor + k * cookies[2].flavor + l * cookies[3].flavor;
					const int64_t texture = i * cookies[0].texture + j * cookies[1].texture + k * cookies[2].texture + l * cookies[3].texture;

					if (capacity <= 0 || durability <= 0 || flavor <= 0 || texture <= 0) continue;

					const auto score = capacity * durability * flavor * texture;

					if (score > result) result = score;
				}
			}
		}

		return result;
	}

	int64_t part2()
	{
		std::vector<Cookie> cookies;
		int64_t result = 0;

		for (const auto& line : getLineByLine<Cookie>("Days\\day15.txt", [](std::string& var)
		{
			std::replace(var.begin(), var.end(), ',', ' ');
			std::istringstream iss(var);
			std::vector<std::string> splitted(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
			return Cookie{ std::stoi(splitted[2]), std::stoi(splitted[4]), std::stoi(splitted[6]), std::stoi(splitted[8]), std::stoi(splitted[10]) };
		}))
		{
			cookies.push_back(line);
		}

		for (auto i = 1; i <= 100; ++i)
		{
			for (auto j = 1; j <= 100 - i; ++j)
			{
				for (auto k = 1; k <= 100 - i - j; ++k)
				{
					const auto l = 100 - i - j - k;

					const int64_t capacity = i * cookies[0].capacity + j * cookies[1].capacity + k * cookies[2].capacity + l * cookies[3].capacity;
					const int64_t durability = i * cookies[0].durability + j * cookies[1].durability + k * cookies[2].durability + l * cookies[3].durability;
					const int64_t flavor = i * cookies[0].flavor + j * cookies[1].flavor + k * cookies[2].flavor + l * cookies[3].flavor;
					const int64_t texture = i * cookies[0].texture + j * cookies[1].texture + k * cookies[2].texture + l * cookies[3].texture;
					const int64_t calories = i * cookies[0].calories + j * cookies[1].calories + k * cookies[2].calories + l * cookies[3].calories;

					if (calories != 500 || capacity <= 0 || durability <= 0 || flavor <= 0 || texture <= 0) continue;

					const auto score = capacity * durability * flavor * texture;

					if (score > result) result = score;
				}
			}
		}

		return result;
	}
} // namespace day15