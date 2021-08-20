#include "Day12.h"

#include "../FileReader.h"

#include <map>

namespace day12
{
	int64_t part1()
	{
		const auto& line = getLine("Days\\day12.txt");

		int64_t result = 0;
		std::string buffer;

		for (const auto character : line)
		{
			if (character == '-' && buffer.empty()) { buffer += character; }
			else if (character >= '0' && character <= '9') { buffer += character; }
			else if (!buffer.empty())
			{
				result += std::stoi(buffer);
				buffer.clear();
			}
			else buffer.clear();
		}

		return result;
	}

	int64_t part2()
	{
		const auto& line = getLine("Days\\day12.txt");
		std::map<size_t, size_t> toSkip;
		int64_t result = 0;
		std::string buffer;

		for (size_t index = 0; index < line.size(); ++index)
		{
			if (line[index + 0] == ':' && line[index + 1] == '\"' && line[index + 2] == 'r' &&
				line[index + 3] == 'e' && line[index + 4] == 'd' && line[index + 5] == '\"')
			{
				size_t start = index;
				int counter = 0;

				while (counter != -1)
				{
					--start;
					if (start == static_cast<size_t>(-1)) return 0;
					if (line[start] == '{') { --counter; }
					else if (line[start] == '}') { ++counter; }
				}

				counter = 0;

				while (counter != -1)
				{
					++index;
					if (index == line.size()) return 0;
					if (line[index] == '{') { ++counter; }
					else if (line[index] == '}') { --counter; }
				}

				toSkip.insert({ start, index });
			}
		}

		for (size_t index = 0; index < line.size(); ++index)
		{
			if (toSkip.find(index) != toSkip.end())
			{
				if (!buffer.empty())
				{
					result += std::stoi(buffer);
					buffer.clear();
				}

				index = toSkip.at(index);
				continue;
			}

			if (line[index] == '-' && buffer.empty()) { buffer += line[index]; }
			else if (line[index] >= '0' && line[index] <= '9') { buffer += line[index]; }
			else if (!buffer.empty())
			{
				result += std::stoi(buffer);
				buffer.clear();
			}
			else buffer.clear();
		}

		return result;
	}
} // namespace day12