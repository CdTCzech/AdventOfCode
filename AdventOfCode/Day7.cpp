#include "Day7.h"

#include "FileReader.h"

#include <algorithm>
#include <iterator>
#include <locale>
#include <map>
#include <sstream>

namespace day7
{
	inline bool isNumber(const std::string& toCheck)
	{
		return std::find_if(toCheck.begin(), toCheck.end(), [](char c) { return !std::isdigit(c, std::locale()); }) == toCheck.end();
	}

	unsigned short getResult(const std::string& key, const std::map<std::string, std::vector<std::string>>& instructions, std::map<std::string, unsigned short>& results)
	{
		if (results.find(key) != results.end()) return results.at(key);

		if (isNumber(key)) return std::stoi(key);

		const auto& tokens = instructions.at(key);

		if (tokens.size() == 1)
		{
			results.insert({ key, getResult(tokens[0], instructions, results) });
			return results.at(key);
		}
		if (tokens.size() == 2)
		{
			results.insert({ key, ~getResult(tokens[1], instructions, results) });
			return results.at(key);
		}

		if (tokens[1][0] == 'A') { results.insert({ key, getResult(tokens[0], instructions, results) & getResult(tokens[2], instructions, results) }); }
		else if (tokens[1][0] == 'O') { results.insert({ key, getResult(tokens[0], instructions, results) | getResult(tokens[2], instructions, results) }); }
		else if (tokens[1][0] == 'L') { results.insert({ key, getResult(tokens[0], instructions, results) << getResult(tokens[2], instructions, results) }); }
		else if (tokens[1][0] == 'R') { results.insert({ key, getResult(tokens[0], instructions, results) >> getResult(tokens[2], instructions, results) }); }

		return results.at(key);
	}

	int64_t part1()
	{
		std::map<std::string, std::vector<std::string>> instructions;
		std::map<std::string, unsigned short> results;

		for (const auto& line : getLineByLine<std::vector<std::string>>("day7.txt", [](std::string& var)
		{
			std::istringstream iss(var);
			return std::vector<std::string>(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
		}))
		{
			instructions.insert({ line.back(),{ line.begin(), line.end() - 2 } });
		}
		return getResult("a", instructions, results);
	}

	int64_t part2()
	{
		std::map<std::string, std::vector<std::string>> instructions;
		std::map<std::string, unsigned short> results;

		for (const auto& line : getLineByLine<std::vector<std::string>>("day7.txt", [](std::string& var)
		{
			std::istringstream iss(var);
			return std::vector<std::string>(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
		}))
		{
			instructions.insert({ line.back(),{ line.begin(), line.end() - 2 } });
		}

		const auto part1Result = getResult("a", instructions, results);
		results.clear();

		instructions.at("b").clear();
		instructions.at("b").push_back(std::to_string(part1Result));
		return getResult("a", instructions, results);
	}
}  // namespace day7