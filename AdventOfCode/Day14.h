#pragma once

#include <cstdint>

namespace day14
{
	struct ReindeerStats
	{
		int speed;
		int flyTime;
		int restTime;
	};

	// TODO: derivate from ReindeerStats somehow?
	struct AdvancedReindeerStats
	{
		int speed;
		int flyTime;
		int restTime;
		bool phase;
		int secondsRemaining;
		int distance;
		int points;
	};

	int64_t part1();
	int64_t part2();
}  // namespace day14