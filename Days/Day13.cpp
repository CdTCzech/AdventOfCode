#include "Day13.h"

#include "../FileReader.h"

#include <algorithm>
#include <iterator>
#include <map>
#include <sstream>
#include <string>

namespace day13
{
	int64_t part1()
	{
		std::map<std::string, Person> persons;
		int64_t result = 0;

		for (const auto& line : getLineByLine<std::vector<std::string>>("Days\\day13.txt", [](std::string& var)
		{
			var[var.size() - 1] = ' ';
			std::istringstream iss(var);
			return std::vector<std::string>(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
		}))
		{
			if (persons.find(line[0]) == persons.end()) persons.insert({ line[0], Person{ line[0], {} } });

			auto multiplier = 1;
			if (line[2][0] == 'l') multiplier = -1;

			persons.at(line[0]).neighbours.insert({ line[10], std::stoi(line[3]) * multiplier });
		}

		std::vector<std::string> unique;
		for (auto& person : persons) unique.push_back(person.first);
		std::sort(unique.begin(), unique.end());

		do {
			auto sum = 0;
			for (size_t i = 0; i < unique.size() - 1; ++i)
			{
				sum += persons[unique[i]].neighbours[unique[i + 1]];
				sum += persons[unique[i + 1]].neighbours[unique[i]];
			}
			sum += persons[unique[0]].neighbours[unique[unique.size() - 1]];
			sum += persons[unique[unique.size() - 1]].neighbours[unique[0]];


			if (sum > result) result = sum;
		} while (std::next_permutation(unique.begin(), unique.end()));

		return result;
	}

	int64_t part2()
	{
		std::map<std::string, Person> persons;
		int64_t result = 0;

		for (const auto& line : getLineByLine<std::vector<std::string>>("Days\\day13.txt", [](std::string& var)
		{
			var[var.size() - 1] = ' ';
			std::istringstream iss(var);
			return std::vector<std::string>(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
		}))
		{
			if (persons.find(line[0]) == persons.end()) persons.insert({line[0], Person{ line[0], {} }});

			auto multiplier = 1;
			if (line[2][0] == 'l') multiplier = -1;

			persons.at(line[0]).neighbours.insert({ line[10], std::stoi(line[3]) * multiplier });
		}

		std::vector<std::string> unique;
		for (auto& person : persons) unique.push_back(person.first);

		persons.insert({ "me", Person{ "me", {} }});
		for (auto& person : unique)
		{
			persons.at("me").neighbours.insert({ person, 0 });
			persons.at(person).neighbours.insert({ "me", 0 });
		}
		unique.emplace_back("me");

		std::sort(unique.begin(), unique.end());

		do {
			auto sum = 0;
			for (size_t i = 0; i < unique.size() - 1; ++i)
			{
				sum += persons[unique[i]].neighbours[unique[i + 1]];
				sum += persons[unique[i + 1]].neighbours[unique[i]];
			}
			sum += persons[unique[0]].neighbours[unique[unique.size() - 1]];
			sum += persons[unique[unique.size() - 1]].neighbours[unique[0]];


			if (sum > result) result = sum;
		} while (std::next_permutation(unique.begin(), unique.end()));

		return result;
	}
} // namespace day13