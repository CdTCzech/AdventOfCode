#include "Day18.h"

#include "FileReader.h"

#include <array>

namespace day18
{
	int64_t part1()
	{
		std::array<std::array<char, 102>, 102> one{};
		std::array<std::array<char, 102>, 102> two{};

		for (size_t i = 0; i < 102; ++i)
		{
			one[i][0] = '.';
			two[i][0] = '.';

			one[0][i] = '.';
			two[0][i] = '.';

			one[i][101] = '.';
			two[i][101] = '.';

			one[101][i] = '.';
			two[101][i] = '.';
		}

		size_t lineNumber = 1;

		for (const auto& line : getLineByLine<std::string>("day18.txt", [](std::string& var) { return var; }))
		{
			for (size_t i = 0; i < line.size(); ++i) one[lineNumber][i + 1] = line[i];
			++lineNumber;
		}

		auto* read = &one;
		auto* write = &two;

		for (auto i = 0; i < 100; ++i)
		{
			if (i % 2 == 1)
			{
				read = &two;
				write = &one;
			}
			else
			{
				read = &one;
				write = &two;
			}

			for (size_t y = 1; y < 101; ++y)
			{
				for (size_t x = 1; x < 101; ++x)
				{
					unsigned int neighboursOn = 0;
					if ((*read)[y + 1][x + 1] == '#') ++neighboursOn;
					if ((*read)[y][x + 1] == '#') ++neighboursOn;
					if ((*read)[y - 1][x + 1] == '#') ++neighboursOn;
					if ((*read)[y - 1][x] == '#') ++neighboursOn;
					if ((*read)[y - 1][x - 1] == '#') ++neighboursOn;
					if ((*read)[y][x - 1] == '#') ++neighboursOn;
					if ((*read)[y + 1][x - 1] == '#') ++neighboursOn;
					if ((*read)[y + 1][x] == '#') ++neighboursOn;

					if (((*read)[y][x] == '#') && (neighboursOn == 2 || neighboursOn == 3)) { (*write)[y][x] = '#'; }
					else if (((*read)[y][x] == '.') && (neighboursOn == 3)) { (*write)[y][x] = '#'; }
					else { (*write)[y][x] = '.'; }
				}
			}
		}

		int64_t result = 0;
		for (const auto& line : one)
		{
			for (const auto& element : line) if (element == '#') ++result;
		}

		return result;
	}

	int64_t part2()
	{
		std::array<std::array<char, 102>, 102> one{};
		std::array<std::array<char, 102>, 102> two{};

		for (size_t i = 0; i < 102; ++i)
		{
			one[i][0] = '.';
			two[i][0] = '.';

			one[0][i] = '.';
			two[0][i] = '.';

			one[i][101] = '.';
			two[i][101] = '.';

			one[101][i] = '.';
			two[101][i] = '.';
		}

		size_t lineNumber = 1;

		for (const auto& line : getLineByLine<std::string>("day18.txt", [](std::string& var) { return var; }))
		{
			for (size_t i = 0; i < line.size(); ++i) one[lineNumber][i + 1] = line[i];
			++lineNumber;
		}

		one[1][1] = '#';
		one[1][100] = '#';
		one[100][1] = '#';
		one[100][100] = '#';

		auto* read = &one;
		auto* write = &two;

		for (auto i = 0; i < 100; ++i)
		{
			if (i % 2 == 1)
			{
				read = &two;
				write = &one;
			}
			else
			{
				read = &one;
				write = &two;
			}

			for (size_t y = 1; y < 101; ++y)
			{
				for (size_t x = 1; x < 101; ++x)
				{
					unsigned int neighboursOn = 0;
					if ((*read)[y + 1][x + 1] == '#') ++neighboursOn;
					if ((*read)[y][x + 1] == '#') ++neighboursOn;
					if ((*read)[y - 1][x + 1] == '#') ++neighboursOn;
					if ((*read)[y - 1][x] == '#') ++neighboursOn;
					if ((*read)[y - 1][x - 1] == '#') ++neighboursOn;
					if ((*read)[y][x - 1] == '#') ++neighboursOn;
					if ((*read)[y + 1][x - 1] == '#') ++neighboursOn;
					if ((*read)[y + 1][x] == '#') ++neighboursOn;

					if (((*read)[y][x] == '#') && (neighboursOn == 2 || neighboursOn == 3)) { (*write)[y][x] = '#'; }
					else if (((*read)[y][x] == '.') && (neighboursOn == 3)) { (*write)[y][x] = '#'; }
					else { (*write)[y][x] = '.'; }
				}
			}

			(*write)[1][1] = '#';
			(*write)[1][100] = '#';
			(*write)[100][1] = '#';
			(*write)[100][100] = '#';
		}

		int64_t result = 0;
		for (const auto& line : one)
		{
			for (const auto& element : line) if (element == '#') ++result;
		}

		return result;
	}
}  // namespace day18