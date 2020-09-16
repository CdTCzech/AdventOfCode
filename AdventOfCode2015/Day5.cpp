#include "Day5.h"

#include "FileReader.h"

namespace day5
{
	int64_t part1()
	{
		int64_t result = 0;

		for (const auto& line : getLineByLine<std::string>("day5.txt", [](std::string& var) { return var; }))
		{
			auto vowels = 0;
			auto twice = false;
			auto banned = false;
			auto previous = '\0';

			for (const auto& character : line)
			{
				if (character == 'a' || character == 'e' || character == 'i' || character == 'o' || character == 'u') {
					++vowels;
				}

				if (previous == character) twice = true;

				if ((previous == 'a' && character == 'b') ||
					(previous == 'c' && character == 'd') ||
					(previous == 'p' && character == 'q') ||
					(previous == 'x' && character == 'y'))
					banned = true;

				previous = character;
			}

			if (vowels >= 3 && twice && !banned) ++result;
		}

		return result;
	}

	int64_t part2()
	{
		int64_t result = 0;

		for (const auto& line : getLineByLine<std::string>("day5.txt", [](std::string& var) { return var; }))
		{
			auto pair = false;
			auto between = false;

			for (unsigned int i = 0; i < line.size() - 2; ++i)
			{
				if (line[i] == line[i + 2])
				{
					between = true;
					break;
				}
			}

			for (unsigned int i = 0; i < line.size() - 3; ++i)
			{
				auto end = false;

				for (auto j = i + 2; j < line.size() - 1; ++j)
				{
					if (line[i] == line[j] && line[i + 1] == line[j + 1])
					{
						pair = true;
						end = true;
						break;
					}
				}

				if (end == true) break;
			}

			if (pair && between) ++result;
		}

		return result;
	}
} // namespace day5