#include "Day4.h"

#include "FileReader.h"

#include "Libraries/md5.h"

namespace day4
{
	int64_t part1()
	{
		const auto& line = getLine("day4.txt");
		for (unsigned int number = 0; number < 1000000; ++number)
		{
			auto hash = md5(line + std::to_string(number));
			if (hash.substr(0, 5) == "00000")
			{
				return number;
			}
		}
		return 0;
	}

	int64_t part2()
	{
		const auto& line = getLine("day4.txt");
		for (unsigned int number = 282749; number < 10000000; ++number)
		{
			auto hash = md5(line + std::to_string(number));
			if (hash.substr(0, 6) == "000000")
			{
				return number;
			}
		}
		return 0;
	}
}  // namespace day4