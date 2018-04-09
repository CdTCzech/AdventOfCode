#pragma once

#include <cstdint>

namespace day22
{
	struct Player
	{
		int HP;
		int MAN;
	};

	struct Boss
	{
		int HP;
		int DMG;
	};

	int64_t part1();
	int64_t part2();
}  // namespace day22