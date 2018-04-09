#include "Day25.h"

namespace day25
{
	int64_t part1()
	{
		int64_t result = 20'151'125;
		const int64_t multiplier = 252'533;
		const int64_t devider = 33'554'393;
		const int64_t rowToFind = 2'978;
		const int64_t columnToFind = 3'083;

		const auto oneRowBeforeStart = rowToFind + columnToFind - 2;
		auto index = (oneRowBeforeStart * 1) + ((oneRowBeforeStart * (oneRowBeforeStart - 1)) / 2) + columnToFind - 1;

		while (index)
		{
			result = (result * multiplier) % devider;
			--index;
		}

		return result;
	}
}  // namespace day25