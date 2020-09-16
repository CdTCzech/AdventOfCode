#include "Day17.h"

#include "FileReader.h"

#include <algorithm>

namespace day17
{
	void combinations(std::vector<std::vector<int>>& result, std::vector<int>& numbers, size_t startPosition, std::vector<int> current, int count)
	{
		current.push_back(numbers[startPosition]);
		count += numbers[startPosition];

		if (count == 150) result.push_back(current);
		else if (count < 150)
		{
			for (size_t i = startPosition + 1; i < numbers.size(); ++i)
			{
				combinations(result, numbers, i, current, count);
			}
		}
	}

	int64_t part1()
	{
		std::vector<int> numbers;
		std::vector<std::vector<int>> result;

		for (const auto& line : getLineByLine<int>("day17.txt", [](std::string& var)
		{
			return std::stoi(var);
		}))
		{
			numbers.push_back(line);
		}

		std::sort(numbers.begin(), numbers.end(), std::greater<>());

		for (size_t i = 0; i < numbers.size(); ++i)
		{
			combinations(result, numbers, i, {}, 0);
		}

		return result.size();
	}

	int64_t part2()
	{
		std::vector<int> numbers;
		std::vector<std::vector<int>> results;

		for (const auto& line : getLineByLine<int>("day17.txt", [](std::string& var)
		{
			return std::stoi(var);
		}))
		{
			numbers.push_back(line);
		}

		std::sort(numbers.begin(), numbers.end(), std::greater<>());

		for (size_t i = 0; i < numbers.size(); ++i)
		{
			combinations(results, numbers, i, {}, 0);
		}

		auto minimum = numbers.size();
		for (const auto& var : results) if (var.size() < minimum) minimum = var.size();

		int64_t result = 0;
		for (const auto& var : results) if (var.size() == minimum) ++result;

		return result;
	}
} // namespace day17