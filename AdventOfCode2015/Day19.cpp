#include "Day19.h"

#include "FileReader.h"

#include <iterator>
#include <map>
#include <set>
#include <sstream>

namespace day19
{
	int64_t part1()
	{
		std::map<std::string, std::vector<std::string>> replacements;
		std::set<std::string> result;

		for (const auto& line : getLineByLine<std::vector<std::string>>("day19_1.txt", [](std::string& var)
		{
			std::istringstream iss(var);
			std::vector<std::string> splitted(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
			return splitted;
		}))
		{
			if (replacements.find(line[0]) == replacements.end()) replacements.insert({ line[0],{ line[2] } });
			else replacements.at(line[0]).push_back(line[2]);
		}

		auto line = getLine("day19_2.txt");

		for (size_t i = 0; i < line.size() - 1; ++i)
		{
			std::string key{ line[i] };
			if (replacements.find(key) != replacements.end())
			{
				for (const auto& replacement : replacements.at(key))
				{
					auto temp = line;
					temp.replace(i, 1, replacement);
					result.insert(temp);
				}
			}

			key += line[i + 1];
			if (replacements.find(key) != replacements.end())
			{
				for (const auto& replacement : replacements.at(key))
				{
					auto temp = line;
					temp.replace(i, 2, replacement);
					result.insert(temp);
				}
			}
		}

		const std::string key{ line[line.size() - 1] };
		if (replacements.find(key) != replacements.end())
		{
			for (const auto& replacement : replacements.at(key))
			{
				auto temp = line;
				temp.replace(line.size() - 1, 1, replacement);
				result.insert(temp);
			}
		}

		return result.size();
	}

	int64_t part2()
	{
		auto line = getLine("day19_2.txt");

		auto total = 0;
		for (auto& element : line) if (element >= 'A' && element <= 'Z') ++total;

		auto ar = 0;
		auto rn = 0;
		auto y = 0;
		for (size_t i = 0; i < line.size() - 1; ++i)
		{
			if (line[i] == 'A' && line[i + 1] == 'r') ++ar;
			if (line[i] == 'R' && line[i + 1] == 'n') ++rn;
			if (line[i] == 'Y') ++y;
		}

		return (total - ar - rn - 2 * y - 1);
	}
} // namespace day19