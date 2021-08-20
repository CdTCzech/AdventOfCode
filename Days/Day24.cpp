#include "Day24.h"

#include "../FileReader.h"

#include <algorithm>
#include <numeric>

namespace day24
{
	template <typename Iterator>
	bool next_combination(const Iterator first, Iterator k, const Iterator last)
	{
		if ((first == last) || (first == k) || (last == k)) { return false; }
		Iterator i1 = first;
		Iterator i2 = last;
		++i1;
		if (last == i1) { return false; }
		i1 = last;
		--i1;
		i1 = k;
		--i2;
		while (first != i1)
		{
			if (*--i1 < *i2)
			{
				Iterator j = k;
				while (!(*i1 < *j)) ++j;
				std::iter_swap(i1, j);
				++i1;
				++j;
				i2 = k;
				std::rotate(i1, j, last);
				while (last != j)
				{
					++j;
					++i2;
				}
				std::rotate(k, i2, last);
				return true;
			}
		}
		std::rotate(first, k, last);
		return false;
	}

	bool findNextGroup(const int64_t howManyToFind, const int64_t sumToFind, std::vector<int64_t>& findVector)
	{
		if (howManyToFind == 0)
		{
			return true;
		}

		for (size_t i = 1; i < findVector.size(); ++i)
		{
			do
			{
				int64_t pkgSum;
				if (howManyToFind == 1) { pkgSum = std::accumulate(findVector.begin(), findVector.end(), static_cast<int64_t>(0)); }
				else { pkgSum = std::accumulate(findVector.begin(), findVector.begin() + i, static_cast<int64_t>(0)); }

				if (pkgSum == sumToFind)
				{
					std::vector<int64_t> subsetVec(findVector.begin(), findVector.begin() + i);
					std::vector<int64_t> newFindVec;
					for (auto number : findVector)
					{
						if (std::find(subsetVec.begin(), subsetVec.end(), number) == subsetVec.end())
						{
							newFindVec.push_back(number);
						}
					}

					return findNextGroup(howManyToFind - 1, sumToFind, newFindVec);
				}
			} while (next_combination(findVector.begin(), findVector.begin() + i, findVector.end()));
		}

		return false;
	}

	int64_t getQuantumEntanglement(const int64_t groups)
	{
		std::vector<int64_t> packages;
		std::vector<std::tuple<int64_t, std::vector<int64_t>>> subsets;
		for (const auto& line : getLineByLine<std::string>("Days\\day24.txt", [](std::string& var) { return var; }))
		{
			packages.push_back(std::stoul(line));
		}

		const auto sum = std::accumulate(packages.begin(), packages.end(), static_cast<int64_t>(0));
		const auto third = sum / groups;
		int64_t start = 0;
		int64_t stop = 0;

		for (auto i = packages.size() - 1; i > 0; --i)
		{
			start += packages[i];
			if (start > third)
			{
				start = packages.size() - i;
				break;
			}
		}

		for (size_t i = 0; i < packages.size(); ++i)
		{
			stop += packages[i];
			if (stop > third)
			{
				stop = i - 1;
				break;
			}
		}

		for (auto i = start; i <= stop; ++i)
		{
			do
			{
				const auto pkgSum = std::accumulate(packages.begin(), packages.begin() + i, static_cast<int64_t>(0));
				if (pkgSum == third)
				{
					uint64_t acc = std::accumulate(packages.begin(), packages.begin() + i, static_cast<int64_t>(1), std::multiplies<>());
					subsets.emplace_back(acc, std::vector<int64_t>(packages.begin(), packages.begin() + i));
				}
			} while (next_combination(packages.begin(), packages.begin() + i, packages.end()));

			std::sort(subsets.begin(), subsets.end());

			for (auto& subset : subsets)
			{
				std::vector<int64_t> secondVec;
				auto subsetVec = std::get<1>(subset);
				for (auto number : packages)
				{
					if (std::find(subsetVec.begin(), subsetVec.end(), number) == subsetVec.end())
					{
						secondVec.push_back(number);
					}
				}

				if (findNextGroup(groups - 1, third, secondVec))
				{
					return std::get<0>(subset);
				}
			}
		}

		return 0;
	}

	int64_t part1()
	{
		return getQuantumEntanglement(3);
	}

	int64_t part2()
	{
		return getQuantumEntanglement(4);
	}
} // namespace day24