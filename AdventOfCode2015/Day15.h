#pragma once

#include <cstdint>

namespace day15
{
	struct Cookie
	{
		int capacity;
		int durability;
		int flavor;
		int texture;
		int calories;
	};

	int64_t part1();
	int64_t part2();
} // namespace day15