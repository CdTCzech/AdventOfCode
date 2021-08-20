#pragma once

#include "Day3.h"

#include <cstdint>

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

	int64_t part1();
	int64_t part2();
} // namespace day6