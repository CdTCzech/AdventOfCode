#include "Day11.h"

#include "FileReader.h"

namespace day11
{
	void increaseString(std::string& line, const size_t index)
	{
		if (line[index] != 'z')
		{
			++line[index];
		}
		else
		{
			line[index] = 'a';
			increaseString(line, index - 1);
		}
	}

	std::string part1()
	{
		auto line = getLine("day11.txt");

		auto increasing = false;
		auto banned = false;
		auto pairs = false;

		while (!increasing || !banned || !pairs)
		{
			increasing = false;
			banned = false;
			pairs = false;

			increaseString(line, line.size() - 1);

			for (size_t index = 0; index < line.size() - 2; ++index)
			{
				if (line[index] + 1 == line[index + 1] &&
					line[index] + 2 == line[index + 2])
				{
					increasing = true;
					break;
				}
			}

			if (line.find_first_of("iol") == std::string::npos) banned = true;

			auto first = true;
			auto temp = ' ';

			for (size_t index = 0; index < line.size() - 1; ++index)
			{
				if (line[index] == line[index + 1])
				{
					if (first)
					{
						first = false;
						temp = line[index];
						++index;
					}
					else if (line[index] != temp)
					{
						pairs = true;
						break;
					}
				}
			}
		}

		return line;
	}

	std::string part2()
	{
		std::string line = "hepxxyzz";

		auto increasing = false;
		auto banned = false;
		auto pairs = false;

		while (!increasing || !banned || !pairs)
		{
			increasing = false;
			banned = false;
			pairs = false;

			increaseString(line, line.size() - 1);

			for (size_t index = 0; index < line.size() - 2; ++index)
			{
				if (line[index] + 1 == line[index + 1] &&
					line[index] + 2 == line[index + 2])
				{
					increasing = true;
					break;
				}
			}

			if (line.find_first_of("iol") == std::string::npos) banned = true;

			auto first = true;
			auto temp = ' ';

			for (size_t index = 0; index < line.size() - 1; ++index)
			{
				if (line[index] == line[index + 1])
				{
					if (first)
					{
						first = false;
						temp = line[index];
						++index;
					}
					else if (line[index] != temp)
					{
						pairs = true;
						break;
					}
				}
			}
		}

		return line;
	}
}  // namespace day11