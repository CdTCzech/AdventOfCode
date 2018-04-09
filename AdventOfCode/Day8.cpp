#include "Day8.h"

#include "FileReader.h"

namespace day8
{
	int64_t part1()
	{
		int64_t result = 0;

		for (const auto& line : getLineByLine<std::string>("day8.txt", [](std::string& var) { return var; }))
		{
			result += line.size();

			for (size_t index = 0; index < line.size(); ++index)
			{
				if (line[index] == '\\')
				{
					if (line[index + 1] == 'x') index += 3;
					else index += 1;
				}
				else if (line[index] == '\"') result += 1;

				result -= 1;
			}
		}

		return result;
	}

	int64_t part2()
	{
		int64_t result = 0;

		for (const auto& line : getLineByLine<std::string>("day8.txt", [](std::string& var) { return var; }))
		{
			result += 2;

			for (const auto character : line)
			{
				if (character == '\\' || character == '\"') result += 1;
			}
		}

		return result;
	}
}  // namespace day8