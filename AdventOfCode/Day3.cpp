#include "Day3.h"

#include "FileReader.h"

#include <set>

namespace day3
{
	int64_t part1()
	{
		Point currentPosition{ 0, 0 };
		std::set<Point> points;

		const auto& line = getLine("day3.txt");
		for (auto character : line)
		{
			points.insert(currentPosition);

			if (character == '^') { ++currentPosition.y; }
			else if (character == 'v') { --currentPosition.y; }
			else if (character == '<') { --currentPosition.x; }
			else if (character == '>') { ++currentPosition.x; }
		}

		return points.size();
	}

	int64_t part2()
	{
		Point currentPositionSanta{ 0, 0 };
		Point currentPositionRobo{ 0, 0 };
		Point* current;
		std::set<Point> points;

		const auto& line = getLine("day3.txt");
		auto isSantaTurn = true;
		for (auto character : line)
		{
			if (isSantaTurn) { current = &currentPositionSanta; }
			else { current = &currentPositionRobo; }

			isSantaTurn = !isSantaTurn;

			points.insert(*current);

			if (character == '^') { ++current->y; }
			else if (character == 'v') { --current->y; }
			else if (character == '<') { --current->x; }
			else if (character == '>') { ++current->x; }
		}

		return points.size();
	}
}  // namespace day3