#include "Day14.h"

#include "../FileReader.h"

#include <iterator>
#include <sstream>

namespace day14
{
	int64_t part1()
	{
		const auto time = 2503;
		int64_t maximal = 0;

		for (const auto& line : getLineByLine<ReindeerStats>("Days\\day14.txt", [](std::string& var)
		{
			std::istringstream iss(var);
			std::vector<std::string> splitted(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
			return ReindeerStats{ std::stoi(splitted[3]), std::stoi(splitted[6]), std::stoi(splitted[13]) };
		}))
		{
			int distance = 0;

			int full = time / (line.flyTime + line.restTime);
			int half = time - (full * (line.flyTime + line.restTime));
			if (half >= line.flyTime) distance += line.speed * line.flyTime;
			else distance = half * line.speed;
			distance += full * line.speed * line.flyTime;

			if (distance > maximal) maximal = distance;
		}

		return maximal;
	}

	int64_t part2()
	{
		std::vector<AdvancedReindeerStats> reindeers;

		for (const auto& line : getLineByLine<AdvancedReindeerStats>("Days\\day14.txt", [](std::string& var)
		{
			std::istringstream iss(var);
			std::vector<std::string> splitted(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
			return AdvancedReindeerStats{ std::stoi(splitted[3]), std::stoi(splitted[6]), std::stoi(splitted[13]), true, std::stoi(splitted[6]), 0, 0 };
		}))
		{
			reindeers.push_back(line);
		}

		for (size_t iteration = 0; iteration < 2503; ++iteration)
		{
			for (auto& reindeer : reindeers)
			{
				if (reindeer.phase) reindeer.distance += reindeer.speed;
				--reindeer.secondsRemaining;
				if (reindeer.secondsRemaining == 0)
				{
					if (reindeer.phase) { reindeer.secondsRemaining = reindeer.restTime; }
					else { reindeer.secondsRemaining = reindeer.flyTime; }
					reindeer.phase = !reindeer.phase;
				}
			}

			int64_t maximum = 0;
			for (auto& reindeer : reindeers) if (reindeer.distance > maximum) maximum = reindeer.distance;
			for (auto& reindeer : reindeers) if (reindeer.distance == maximum) ++reindeer.points;
		}

		int64_t maximum = 0;
		for (auto& reindeer : reindeers) if (reindeer.points > maximum) maximum = reindeer.points;
		return maximum;
	}
} // namespace day14