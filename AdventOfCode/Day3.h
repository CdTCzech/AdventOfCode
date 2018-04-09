#pragma once

#include <cstdint>

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

	int64_t part1();
	int64_t part2();
}  // namespace day3