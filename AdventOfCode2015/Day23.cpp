#include "Day23.h"

#include "FileReader.h"

namespace day23
{
	void simulate(int64_t& regA, int64_t& regB)
	{
		std::vector<std::string> program;
		size_t currentLine = 0;
		for (const auto& line : getLineByLine<std::string>("day23.txt", [](std::string& var) { return var; }))
		{
			program.push_back(line);
		}

		while (currentLine < program.size())
		{
			if (program[currentLine][2] == 'f') // hlf
			{
				if (program[currentLine][4] == 'a') { regA /= 2; }
				else { regB /= 2; }
				++currentLine;
			}
			else if (program[currentLine][2] == 'l') // tpl
			{
				if (program[currentLine][4] == 'a') { regA *= 3; }
				else { regB *= 3; }
				++currentLine;
			}
			else if (program[currentLine][2] == 'c') // inc
			{
				if (program[currentLine][4] == 'a') { regA += 1; }
				else { regB += 1; }
				++currentLine;
			}
			else if (program[currentLine][2] == 'p') // jmp
			{
				const auto offset = program[currentLine].substr(4);
				currentLine += std::stoull(offset);
			}
			else if (program[currentLine][2] == 'e') // jie
			{
				if ((program[currentLine][4] == 'a' && regA % 2 == 0) || (program[currentLine][4] == 'b' && regB % 2 == 0))
				{
					const auto offset = program[currentLine].substr(7);
					currentLine += std::stoull(offset);
				}
				else ++currentLine;
			}
			else if (program[currentLine][2] == 'o') // jio
			{
				if ((program[currentLine][4] == 'a' && regA == 1) || (program[currentLine][4] == 'b' && regB == 1))
				{
					const auto offset = program[currentLine].substr(7);
					currentLine += std::stoull(offset);
				}
				else ++currentLine;
			}
		}
	}

	int64_t part1()
	{
		int64_t regA = 0;
		int64_t regB = 0;

		simulate(regA, regB);

		return regB;
	}

	int64_t part2()
	{
		int64_t regA = 1;
		int64_t regB = 0;

		simulate(regA, regB);

		return regB;
	}
} // namespace day23