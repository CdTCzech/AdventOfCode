#pragma once

#include <map>
#include <cstdint>
#include <string>

namespace day9
{
	struct City
	{
		std::string name;
		std::map<std::string, unsigned int> neighbours;
	};

	int64_t part1();
	int64_t part2();
}  // namespace day9