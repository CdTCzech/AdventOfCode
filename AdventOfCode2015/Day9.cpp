#include "Day9.h"

#include "FileReader.h"

#include <algorithm>
#include <iterator>
#include <sstream>

namespace day9
{
	int64_t part1()
	{
		std::map<std::string, City> cities;
		int64_t result = 4'294'967'295;

		for (const auto& line : getLineByLine<std::vector<std::string>>("day9.txt", [](std::string& var)
		{
			std::istringstream iss(var);
			return std::vector<std::string>(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
		}))
		{
			if (cities.find(line[0]) == cities.end()) cities.insert({ line[0], City{ line[0],{} } });
			if (cities.find(line[2]) == cities.end()) cities.insert({ line[2], City{ line[2],{} } });

			cities.at(line[0]).neighbours.insert({ line[2], static_cast<unsigned int>(std::stoi(line[4])) });
			cities.at(line[2]).neighbours.insert({ line[0], static_cast<unsigned int>(std::stoi(line[4])) });
		}

		std::vector<std::string> unique;
		for (auto& city : cities) unique.push_back(city.first);
		std::sort(unique.begin(), unique.end());

		do {
			unsigned int sum = 0;
			for (size_t i = 0; i < unique.size() - 1; ++i)
			{
				sum += cities[unique[i]].neighbours[unique[i + 1]];
			}

			if (sum < result) result = sum;
		} while (std::next_permutation(unique.begin(), unique.end()));

		return result;
	}

	int64_t part2()
	{
		std::map<std::string, City> cities;
		int64_t result = 0;

		for (const auto& line : getLineByLine<std::vector<std::string>>("day9.txt", [](std::string& var)
		{
			std::istringstream iss(var);
			return std::vector<std::string>(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
		}))
		{
			if (cities.find(line[0]) == cities.end()) cities.insert({ line[0], City{ line[0],{} } });
			if (cities.find(line[2]) == cities.end()) cities.insert({ line[2], City{ line[2],{} } });

			cities.at(line[0]).neighbours.insert({ line[2], static_cast<unsigned int>(std::stoi(line[4])) });
			cities.at(line[2]).neighbours.insert({ line[0], static_cast<unsigned int>(std::stoi(line[4])) });
		}

		std::vector<std::string> unique;
		for (auto& city : cities) unique.push_back(city.first);
		std::sort(unique.begin(), unique.end());

		do {
			unsigned int sum = 0;
			for (size_t i = 0; i < unique.size() - 1; ++i)
			{
				sum += cities[unique[i]].neighbours[unique[i + 1]];
			}

			if (sum > result) result = sum;
		} while (std::next_permutation(unique.begin(), unique.end()));

		return result;
	}
} // namespace day9