#include "Day10.h"

#include "FileReader.h"

namespace day10
{
	int64_t part1()
	{
		const auto& line = getLine("day10.txt");
		auto temp = line;
		std::string result;

		for (unsigned int iteration = 0; iteration < 40; ++iteration)
		{
			unsigned int count = 1;
			auto last = temp[0];
			result.clear();

			for (size_t index = 1; index < temp.size(); ++index)
			{
				if (temp[index] != last)
				{
					result += std::to_string(count);
					result += last;
					count = 1;
					last = temp[index];
				}
				else ++count;
			}

			result += std::to_string(count);
			result += last;
			temp = result;
		}

		return result.size();
	}

	int64_t part2()
	{
		const auto& line = getLine("day10.txt");
		auto temp = line;
		std::string result;

		for (unsigned int iteration = 0; iteration < 50; ++iteration)
		{
			unsigned int count = 1;
			auto last = temp[0];
			result.clear();

			for (size_t index = 1; index < temp.size(); ++index)
			{
				if (temp[index] != last)
				{
					result += std::to_string(count);
					result += last;
					count = 1;
					last = temp[index];
				}
				else ++count;
			}

			result += std::to_string(count);
			result += last;
			temp = result;
		}

		return result.size();
	}
}  // namespace day10