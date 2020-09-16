#pragma once

#include <cstdint>
#include <map>
#include <string>

namespace day13
{
	struct Person
	{
		std::string name;
		std::map<std::string, int> neighbours;
	};

	int64_t part1();
	int64_t part2();
} // namespace day13