#include "Day2.h"

#include "../FileReader.h"

#include <algorithm>
#include <sstream>

namespace day2
{
	int64_t part1()
	{
		int64_t result = 0;

		for (const auto& line : getLineByLine<Dimensions>("Days\\day2.txt", [](std::string& var)
		{
			std::replace(var.begin(), var.end(), 'x', ' ');
			std::istringstream iss(var);
			int l, w, h;
			iss >> l >> w >> h;
			return Dimensions{ l, w, h };
		}))
		{
			auto sideA = line.l * line.w;
			auto sideB = line.l * line.h;
			auto sideC = line.w * line.h;
			auto sideM = std::min(sideA, std::min(sideB, sideC));
			result += 2 * sideA + 2 * sideB + 2 * sideC + sideM;
		}

		return result;
	}

	int64_t part2()
	{
		int64_t result = 0;

		for (const auto& line : getLineByLine<Dimensions>("Days\\day2.txt", [](std::string& var)
		{
			std::replace(var.begin(), var.end(), 'x', ' ');
			std::istringstream iss(var);
			int l, w, h;
			iss >> l >> w >> h;
			return Dimensions{ l, w, h };
		}))
		{
			auto ribbon = (line.l + line.w + line.h - std::max(line.l, std::max(line.w, line.h))) * 2;
			auto bow = line.l * line.w * line.h;
			result += ribbon + bow;
		}

		return result;
	}
} // namespace day2