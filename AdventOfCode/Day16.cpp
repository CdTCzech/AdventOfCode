#include "Day16.h"

#include "FileReader.h"

#include <algorithm>
#include <iterator>
#include <map>
#include <sstream>

namespace day16
{
	int64_t part1()
	{
		std::map<std::string, unsigned int> myAunt;
		myAunt.insert({ "children",		3 });
		myAunt.insert({ "cats",			7 });
		myAunt.insert({ "samoyeds",		2 });
		myAunt.insert({ "pomeranians",	3 });
		myAunt.insert({ "akitas",		0 });
		myAunt.insert({ "vizslas",		0 });
		myAunt.insert({ "goldfish",		5 });
		myAunt.insert({ "trees",		3 });
		myAunt.insert({ "cars",			2 });
		myAunt.insert({ "perfumes",		1 });

		for (const auto& line : getLineByLine<std::vector<std::string>>("day16.txt", [](std::string& var)
		{
			std::replace(var.begin(), var.end(), ':', ' ');
			std::replace(var.begin(), var.end(), ',', ' ');
			std::istringstream iss(var);
			std::vector<std::string> splitted(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
			return splitted;
		}))
		{
			if (myAunt[line[2]] == std::stoi(line[3]) &&
				myAunt[line[4]] == std::stoi(line[5]) &&
				myAunt[line[6]] == std::stoi(line[7]))
			{
				return std::stoll(line[1]);
			}
		}

		return {};
	}

	int64_t part2()
	{
		std::map<std::string, int> myAunt;
		myAunt.insert({ "children",		3 });
		myAunt.insert({ "cats",			7 });
		myAunt.insert({ "samoyeds",		2 });
		myAunt.insert({ "pomeranians",	3 });
		myAunt.insert({ "akitas",		0 });
		myAunt.insert({ "vizslas",		0 });
		myAunt.insert({ "goldfish",		5 });
		myAunt.insert({ "trees",		3 });
		myAunt.insert({ "cars",			2 });
		myAunt.insert({ "perfumes",		1 });

		for (const auto& line : getLineByLine<std::vector<std::string>>("day16.txt", [](std::string& var)
		{
			std::replace(var.begin(), var.end(), ':', ' ');
			std::replace(var.begin(), var.end(), ',', ' ');
			std::istringstream iss(var);
			std::vector<std::string> splitted(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
			return splitted;
		}))
		{
			unsigned int result = 0;
			for (unsigned int i = 2; i < 8; i += 2)
			{
				if (line[i] == "cats" || line[i] == "trees")
				{
					if (myAunt[line[i]] < std::stoi(line[i + 1])) ++result;
				}
				else if (line[i] == "pomeranians" || line[i] == "goldfish")
				{
					if (myAunt[line[i]] > std::stoi(line[i + 1])) ++result;
				}
				else if (myAunt[line[i]] == std::stoi(line[i + 1])) ++result;
			}

			if (result == 3)
			{
				return std::stoll(line[1]);
			}
		}

		return {};
	}
}  // namespace day16