#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <locale>
#include <map>
#include <set>
#include <sstream>
#include <vector>

#include "Libraries/md5.h"
#include "FileReader.h"


namespace day1
{
	void part1()
	{
		const auto& line = getLine("day1.txt");
		int result = 0;

		for (auto character : line)
		{
			if (character == '(') ++result;
			else --result;
		}

		std::cout << result << std::endl;
	}

	void part2()
	{
		const auto& line = getLine("day1.txt");
		int floor = 0, result = 0;

		for (size_t i = 0; i < line.size(); ++i)
		{
			if (line[i] == '(') ++floor;
			else --floor;

			if (floor == -1)
			{
				result = i;
				break;
			}
		}

		std::cout << result + 1 << std::endl;
	}
}

namespace day2
{
	struct Dimensions
	{
		int l;
		int w;
		int h;
	};

	void part1()
	{
		auto result = 0;

		for (const auto& line : getLineByLine<Dimensions>("day2.txt", [&result](std::string& var)
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

		std::cout << result << std::endl;
	}

	void part2()
	{
		auto result = 0;

		for (const auto& line : getLineByLine<Dimensions>("day2.txt", [&result](std::string& var)
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

		std::cout << result << std::endl;
	}
}

namespace day3
{
	struct Point
	{
		int x;
		int y;

		bool operator< (const Point& other) const
		{
			if (x < other.x) return true;
			if (x == other.x && y < other.y) return true;
			return false;
		}
	};

	void part1()
	{
		Point currentPosition{ 0, 0 };
		std::set<Point> points;

		const auto& line = getLine("day3.txt");
		for (auto character : line)
		{
			points.insert(currentPosition);

			if (character == '^') ++currentPosition.y;
			else if (character == 'v') --currentPosition.y;
			else if (character == '<') --currentPosition.x;
			else if (character == '>') ++currentPosition.x;
		}

		std::cout << points.size() << std::endl;
	}

	void part2()
	{
		Point currentPositionSanta{ 0, 0 };
		Point currentPositionRobo{ 0, 0 };
		Point* current;
		std::set<Point> points;

		const auto& line = getLine("day3.txt");
		bool isSantaTurn = true;
		for (auto character : line)
		{
			if (isSantaTurn) current = &currentPositionSanta;
			else current = &currentPositionRobo;

			isSantaTurn = !isSantaTurn;

			points.insert(*current);

			if (character == '^') ++current->y;
			else if (character == 'v') --current->y;
			else if (character == '<') --current->x;
			else if (character == '>') ++current->x;
		}

		std::cout << points.size() << std::endl;
	}
}

namespace day4
{
	void part1()
	{
		const auto& line = getLine("day4.txt");
		for (unsigned int number = 0; number < 1000000; ++number)
		{
			auto hash = md5(line + std::to_string(number));
			if (hash.substr(0, 5) == "00000")
			{
				std::cout << std::to_string(number) << std::endl;
				break;
			}
		}
	}

	void part2()
	{
		const auto& line = getLine("day4.txt");
		for (unsigned int number = 282749; number < 10000000; ++number)
		{
			auto hash = md5(line + std::to_string(number));
			if (hash.substr(0, 6) == "000000")
			{
				std::cout << std::to_string(number) << std::endl;
				break;
			}
		}
	}
}

namespace day5
{
	void part1()
	{
		int result = 0;

		for (const auto& line : getLineByLine<std::string>("day5.txt", [&result](std::string& var) { return var; }))
		{
			int vowels = 0;
			bool twice = false;
			bool banned = false;
			char previous = '\0';

			for (const auto& character : line)
			{
				if (character == 'a' || character == 'e' || character == 'i'
					|| character == 'o' || character == 'u')
					++vowels;

				if (previous == character) twice = true;

				if ((previous == 'a' && character == 'b') ||
					(previous == 'c' && character == 'd') ||
					(previous == 'p' && character == 'q') ||
					(previous == 'x' && character == 'y'))
					banned = true;

				previous = character;
			}

			if (vowels >= 3 && twice && !banned) ++result;
		}

		std::cout << result << std::endl;
	}

	void part2()
	{
		int result = 0;

		for (const auto& line : getLineByLine<std::string>("day5.txt", [&result](std::string& var) { return var; }))
		{
			bool pair = false;
			bool between = false;

			for (unsigned int i = 0; i < line.size() - 2; ++i)
			{
				if (line[i] == line[i + 2])
				{
					between = true;
					break;
				}
			}

			for (unsigned int i = 0; i < line.size() - 3; ++i)
			{
				bool end = false;

				for (auto j = i + 2; j < line.size() - 1; ++j)
				{
					if (line[i] == line[j] && line[i + 1] == line[j + 1])
					{
						pair = true;
						end = true;
						break;
					}
				}

				if (end == true) break;
			}

			if (pair && between) ++result;
		}

		std::cout << result << std::endl;
	}
}

namespace day6
{
	enum class Type
	{
		on,
		off,
		toggle
	};

	struct Command
	{
		day3::Point start;
		day3::Point end;
		Type type;
	};

	void part1()
	{
		std::vector<std::vector<bool>> grid(1000, std::vector<bool>(1000, false));
		unsigned int result = 0;

		for (const auto& line : getLineByLine<Command>("day6.txt", [&grid](std::string& var)
		{
			std::replace(var.begin(), var.end(), ',', ' ');
			std::istringstream iss(var);
			std::string buffer;
			Command command;
			if (var[1] == 'o')
			{
				command.type = Type::toggle;
				iss >> buffer >> command.start.x >> command.start.y >> buffer >> command.end.x >> command.end.y;
			}
			else
			{
				command.type = (var[6] == 'f') ? Type::off : Type::on;
				iss >> buffer >> buffer >> command.start.x >> command.start.y >> buffer >> command.end.x >> command.end.y;
			}
			return command;
		}))
		{
			for (auto y = line.start.y; y <= line.end.y; ++y)
			{
				for (auto x = line.start.x; x <= line.end.x; ++x)
				{
					if (line.type == Type::toggle) grid[y][x] = !grid[y][x];
					else if (line.type == Type::off) grid[y][x] = false;
					else grid[y][x] = true;
				}
			}
		}

		for (const auto& y : grid)
		{
			for (const auto x : y)
			{
				if (x == true) ++result;
			}
		}

		std::cout << result << std::endl;
	}

	void part2()
	{
		std::vector<std::vector<int>> grid(1000, std::vector<int>(1000, 0));
		unsigned int result = 0;

		for (const auto& line : getLineByLine<Command>("day6.txt", [&grid](std::string& var)
		{
			std::replace(var.begin(), var.end(), ',', ' ');
			std::istringstream iss(var);
			std::string buffer;
			Command command;
			if (var[1] == 'o')
			{
				command.type = Type::toggle;
				iss >> buffer >> command.start.x >> command.start.y >> buffer >> command.end.x >> command.end.y;
			}
			else
			{
				command.type = (var[6] == 'f') ? Type::off : Type::on;
				iss >> buffer >> buffer >> command.start.x >> command.start.y >> buffer >> command.end.x >> command.end.y;
			}
			return command;
		}))
		{
			for (auto y = line.start.y; y <= line.end.y; ++y)
			{
				for (auto x = line.start.x; x <= line.end.x; ++x)
				{
					if (line.type == Type::toggle) grid[y][x] += 2;
					else if (line.type == Type::on) grid[y][x] += 1;
					else
					{
						if (grid[y][x] > 0) grid[y][x] -= 1;
					}
				}
			}
		}

		for (const auto& y : grid)
		{
			for (const auto x : y)
			{
				result += x;
			}
		}

		std::cout << result << std::endl;
	}
}

namespace day7
{
	std::map<std::string, std::vector<std::string>> instructions;
	std::map<std::string, unsigned short> results;

	inline bool isNumber(const std::string& toCheck)
	{
		return std::find_if(toCheck.begin(), toCheck.end(), [](char c) { return !std::isdigit(c, std::locale()); }) == toCheck.end();
	}

	unsigned short getResult(const std::string& key)
	{
		if (results.find(key) != results.end()) return results.at(key);

		if (isNumber(key)) return std::stoi(key);

		const auto& tokens = instructions.at(key);

		if (tokens.size() == 1)
		{
			results.insert({ key, getResult(tokens[0]) });
			return results.at(key);
		}
		if (tokens.size() == 2)
		{
			results.insert({ key, ~getResult(tokens[1]) });
			return results.at(key);
		}
		
		if (tokens[1][0] == 'A') results.insert({ key, getResult(tokens[0]) & getResult(tokens[2]) });
		else if (tokens[1][0] == 'O') results.insert({ key, getResult(tokens[0]) | getResult(tokens[2]) });
		else if (tokens[1][0] == 'L') results.insert({ key, getResult(tokens[0]) << getResult(tokens[2]) });
		else if (tokens[1][0] == 'R') results.insert({ key, getResult(tokens[0]) >> getResult(tokens[2]) });
		return results.at(key);
	}

	void part1()
	{
		for (const auto& line : getLineByLine<std::vector<std::string>>("day7.txt", [] (std::string& var)
		{
			std::istringstream iss(var);
			return std::vector<std::string>(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
		}))
		{
			instructions.insert({ line.back(),{ line.begin(), line.end() - 2 } });
		}

		std::cout << getResult("a") << std::endl;

		instructions.clear();
		results.clear();
	}

	void part2()
	{
		for (const auto& line : getLineByLine<std::vector<std::string>>("day7.txt", [](std::string& var)
		{
			std::istringstream iss(var);
			return std::vector<std::string>(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
		}))
		{
			instructions.insert({ line.back(),{ line.begin(), line.end() - 2 } });
		}

		auto part1Result = getResult("a");
		results.clear();

		instructions.at("b").clear();
		instructions.at("b").push_back(std::to_string(part1Result));
		std::cout << getResult("a") << std::endl;

		instructions.clear();
		results.clear();
	}
}

namespace day8
{
	void part1()
	{
		unsigned int result = 0;

		for (const auto& line : getLineByLine<std::string>("day8.txt", [&result](std::string& var) { return var; }))
		{
			result += line.size();

			for (size_t index = 0; index < line.size(); ++index)
			{
				if (line[index] == '\\')
				{
					if (line[index + 1] == 'x') index += 3;
					else index += 1;
				}
				else if (line[index] == '\"') result += 1;

				result -= 1;
			}
		}

		std::cout << result << std::endl;
	}

	void part2()
	{
		unsigned int result = 0;

		for (const auto& line : getLineByLine<std::string>("day8.txt", [&result](std::string& var) { return var; }))
		{
			result += 2;

			for (const auto character : line)
			{
				if (character == '\\' || character == '\"') result += 1;
			}
		}

		std::cout << result << std::endl;
	}
}

namespace day9
{
	struct City
	{
		std::string name;
		std::map<std::string, unsigned int> neighbours;
	};

	void part1()
	{
		std::map<std::string, City> cities;
		unsigned int result = 4294967295;

		for (const auto& line : getLineByLine<std::vector<std::string>>("day9.txt", [&cities](std::string& var)
		{
			std::istringstream iss(var);
			return std::vector<std::string>(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
		}))
		{
			if (cities.find(line[0]) == cities.end()) cities.insert({ line[0], City{ line[0], {} } });
			if (cities.find(line[2]) == cities.end()) cities.insert({ line[2], City{ line[2], {} } });

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

		std::cout << result << std::endl;
	}

	void part2()
	{
		std::map<std::string, City> cities;
		unsigned int result = 0;

		for (const auto& line : getLineByLine<std::vector<std::string>>("day9.txt", [&cities](std::string& var)
		{
			std::istringstream iss(var);
			return std::vector<std::string>(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
		}))
		{
			if (cities.find(line[0]) == cities.end()) cities.insert({ line[0], City{ line[0], {} } });
			if (cities.find(line[2]) == cities.end()) cities.insert({ line[2], City{ line[2], {} } });

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

		std::cout << result << std::endl;
	}
}

namespace day10
{
	void part1()
	{
		const auto& line = getLine("day10.txt");
		std::string temp = line;
		std::string result;

		for (unsigned int iteration = 0; iteration < 40; ++iteration)
		{
			unsigned int count = 1;
			char last = temp[0];
			result.clear();

			for (size_t index = 1; index < temp.size(); ++index)
			{
				if (temp[index] != last)
				{
					result += std::to_string(count);
					result += last;
					count = 1;
					last = temp[index];
				}
				else ++count;
			}

			result += std::to_string(count);
			result += last;
			temp = result;
		}

		std::cout << result.size() << std::endl;
	}

	void part2()
	{
		const auto& line = getLine("day10.txt");
		std::string temp = line;
		std::string result;

		for (unsigned int iteration = 0; iteration < 50; ++iteration)
		{
			unsigned int count = 1;
			char last = temp[0];
			result.clear();

			for (size_t index = 1; index < temp.size(); ++index)
			{
				if (temp[index] != last)
				{
					result += std::to_string(count);
					result += last;
					count = 1;
					last = temp[index];
				}
				else ++count;
			}

			result += std::to_string(count);
			result += last;
			temp = result;
		}

		std::cout << result.size() << std::endl;
	}
}

namespace day11
{
	void increaseString(std::string& line, size_t index)
	{
		if (line[index] != 'z')
		{
			++line[index];
		}
		else
		{
			line[index] = 'a';
			increaseString(line, index - 1);
		}
	}

	void part1()
	{
		auto& line = getLine("day11.txt");

		bool increasing = false;
		bool banned = false;
		bool pairs = false;

		while (!increasing || !banned || !pairs)
		{
			increasing = false;
			banned = false;
			pairs = false;

			increaseString(line, line.size() - 1);

			for (size_t index = 0; index < line.size() - 2; ++index)
			{
				if (line[index] + 1 == line[index + 1] &&
					line[index] + 2 == line[index + 2])
				{
					increasing = true;
					break;
				}
			}

			if (line.find_first_of("iol") == std::string::npos) banned = true;

			bool first = true;
			char temp = ' ';

			for (size_t index = 0; index < line.size() - 1; ++index)
			{
				if (line[index] == line[index + 1])
				{
					if (first)
					{
						first = false;
						temp = line[index];
						++index;
					}
					else if (line[index] != temp)
					{
						pairs = true;
						break;
					}
				}
			}
		}

		std::cout << line << std::endl;
	}

	void part2()
	{
		std::string line = "hepxxyzz";

		bool increasing = false;
		bool banned = false;
		bool pairs = false;

		while (!increasing || !banned || !pairs)
		{
			increasing = false;
			banned = false;
			pairs = false;

			increaseString(line, line.size() - 1);

			for (size_t index = 0; index < line.size() - 2; ++index)
			{
				if (line[index] + 1 == line[index + 1] &&
					line[index] + 2 == line[index + 2])
				{
					increasing = true;
					break;
				}
			}

			if (line.find_first_of("iol") == std::string::npos) banned = true;

			bool first = true;
			char temp = ' ';

			for (size_t index = 0; index < line.size() - 1; ++index)
			{
				if (line[index] == line[index + 1])
				{
					if (first)
					{
						first = false;
						temp = line[index];
						++index;
					}
					else if (line[index] != temp)
					{
						pairs = true;
						break;
					}
				}
			}
		}

		std::cout << line << std::endl;
	}
}

namespace day12
{
	void part1()
	{
		const auto& line = getLine("day12.txt");

		int result = 0;
		std::string buffer;

		for (const auto character : line)
		{
			if (character == '-' && buffer.empty()) buffer += character;
			else if (character >= '0' && character <= '9') buffer += character;
			else if (!buffer.empty())
			{
				result += std::stoi(buffer);
				buffer.clear();
			}
			else buffer.clear();
		}

		std::cout << result << std::endl;
	}

	void part2()
	{
		const auto& line = getLine("day12.txt");
		std::map<size_t, size_t> toSkip;
		int result = 0;
		std::string buffer;

		for (size_t index = 0; index < line.size(); ++index)
		{
			if (line[index + 0] == ':' && line[index + 1] == '\"' && line[index + 2] == 'r' &&
				line[index + 3] == 'e' && line[index + 4] == 'd' && line[index + 5] == '\"')
			{
				size_t start = index;
				int counter = 0;

				while (counter != -1)
				{
					--start;
					if (start == -1) return;
					if (line[start] == '{') --counter;
					else if (line[start] == '}') ++counter;
				}

				counter = 0;

				while (counter != -1)
				{
					++index;
					if (index == line.size()) return;
					if (line[index] == '{') ++counter;
					else if (line[index] == '}') --counter;
				}

				toSkip.insert({ start, index });
			}
		}

		for (size_t index = 0; index < line.size(); ++index)
		{
			if (toSkip.find(index) != toSkip.end())
			{
				if (!buffer.empty())
				{
					result += std::stoi(buffer);
					buffer.clear();
				}

				index = toSkip.at(index);
				continue;
			}

			if (line[index] == '-' && buffer.empty()) buffer += line[index];
			else if (line[index] >= '0' && line[index] <= '9') buffer += line[index];
			else if (!buffer.empty())
			{
				result += std::stoi(buffer);
				buffer.clear();
			}
			else buffer.clear();
		}

		std::cout << result << std::endl;
	}
}

namespace day13
{
	struct Person
	{
		std::string name;
		std::map<std::string, int> neighbours;
	};

	void part1()
	{
		std::map<std::string, Person> persons;
		int result = 0;

		for (const auto& line : getLineByLine<std::vector<std::string>>("day13.txt", [&persons](std::string& var)
		{
			var[var.size() - 1] = ' ';
			std::istringstream iss(var);
			return std::vector<std::string>(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
		}))
		{
			if (persons.find(line[0]) == persons.end()) persons.insert({ line[0], Person{ line[0],{} } });

			int multiplier = 1;
			if (line[2][0] == 'l') multiplier = -1;

			persons.at(line[0]).neighbours.insert({ line[10], std::stoi(line[3]) * multiplier });
		}

		std::vector<std::string> unique;
		for (auto& person : persons) unique.push_back(person.first);
		std::sort(unique.begin(), unique.end());

		do {
			int sum = 0;
			for (size_t i = 0; i < unique.size() - 1; ++i)
			{
				sum += persons[unique[i]].neighbours[unique[i + 1]];
				sum += persons[unique[i + 1]].neighbours[unique[i]];
			}
			sum += persons[unique[0]].neighbours[unique[unique.size() - 1]];
			sum += persons[unique[unique.size() - 1]].neighbours[unique[0]];


			if (sum > result) result = sum;
		} while (std::next_permutation(unique.begin(), unique.end()));

		std::cout << result << std::endl;
	}

	void part2()
	{
		std::map<std::string, Person> persons;
		int result = 0;

		for (const auto& line : getLineByLine<std::vector<std::string>>("day13.txt", [&persons](std::string& var)
		{
			var[var.size() - 1] = ' ';
			std::istringstream iss(var);
			return std::vector<std::string>(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
		}))
		{
			if (persons.find(line[0]) == persons.end()) persons.insert({ line[0], Person{ line[0],{} } });

			int multiplier = 1;
			if (line[2][0] == 'l') multiplier = -1;

			persons.at(line[0]).neighbours.insert({ line[10], std::stoi(line[3]) * multiplier });
		}

		std::vector<std::string> unique;
		for (auto& person : persons) unique.push_back(person.first);

		persons.insert({ "me", Person{ "me",{} } });
		for (auto& person : unique)
		{
			persons.at("me").neighbours.insert({ person, 0 });
			persons.at(person).neighbours.insert({ "me", 0 });
		}
		unique.push_back("me");

		std::sort(unique.begin(), unique.end());

		do {
			int sum = 0;
			for (size_t i = 0; i < unique.size() - 1; ++i)
			{
				sum += persons[unique[i]].neighbours[unique[i + 1]];
				sum += persons[unique[i + 1]].neighbours[unique[i]];
			}
			sum += persons[unique[0]].neighbours[unique[unique.size() - 1]];
			sum += persons[unique[unique.size() - 1]].neighbours[unique[0]];


			if (sum > result) result = sum;
		} while (std::next_permutation(unique.begin(), unique.end()));

		std::cout << result << std::endl;
	}
}

namespace day14
{
	struct ReindeerStats
	{
		int speed;
		int flyTime;
		int restTime;
		bool phase;
		int secondsRemaining;
		int distance;
		int points;
	};

	void part1()
	{
		int time = 2503;
		int maximal = 0;

		for (const auto& line : getLineByLine<ReindeerStats>("day14.txt", [&time, &maximal](std::string& var)
		{
			std::istringstream iss(var);
			std::vector<std::string> splitted(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
			return ReindeerStats{std::stoi(splitted[3]), std::stoi(splitted[6]), std::stoi(splitted[13])};
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

		std::cout << maximal << std::endl;
	}

	void part2()
	{
		std::vector<ReindeerStats> reindeers;

		for (const auto& line : getLineByLine<ReindeerStats>("day14.txt", [&reindeers](std::string& var)
		{
			std::istringstream iss(var);
			std::vector<std::string> splitted(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
			return ReindeerStats{ std::stoi(splitted[3]), std::stoi(splitted[6]), std::stoi(splitted[13]), true, std::stoi(splitted[6]), 0, 0 };
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
					if (reindeer.phase) reindeer.secondsRemaining = reindeer.restTime;
					else reindeer.secondsRemaining = reindeer.flyTime;
					reindeer.phase = !reindeer.phase;
				}
			}

			int maximum = 0;
			for (auto& reindeer : reindeers) if (reindeer.distance > maximum) maximum = reindeer.distance;
			for (auto& reindeer : reindeers) if (reindeer.distance == maximum) ++reindeer.points;
		}

		int maximum = 0;
		for (auto& reindeer : reindeers) if (reindeer.points > maximum) maximum = reindeer.points;

		std::cout << maximum << std::endl;
	}
}

namespace day15
{
	struct Cookie
	{
		int capacity;
		int durability;
		int flavor;
		int texture;
		int calories;
	};

	void part1()
	{
		std::vector<Cookie> cookies;
		unsigned long long int result = 0;

		for (const auto& line : getLineByLine<Cookie>("day15.txt", [&cookies](std::string& var)
		{
			std::replace(var.begin(), var.end(), ',', ' ');
			std::istringstream iss(var);
			std::vector<std::string> splitted(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
			return Cookie{ std::stoi(splitted[2]), std::stoi(splitted[4]), std::stoi(splitted[6]), std::stoi(splitted[8]), std::stoi(splitted[10]) };
		}))
		{
			cookies.push_back(line);
		}

		for (int i = 1; i <= 100; ++i)
		{
			for (int j = 1; j <= 100 - i; ++j)
			{
				for (int k = 1; k <= 100 - i - j; ++k)
				{
					int l = 100 - i - j - k;

					long long int capacity =	i * cookies[0].capacity   +	j * cookies[1].capacity   +	k * cookies[2].capacity   +	l * cookies[3].capacity;
					long long int durability =	i * cookies[0].durability + j * cookies[1].durability + k * cookies[2].durability + l * cookies[3].durability;
					long long int flavor =		i * cookies[0].flavor     +	j * cookies[1].flavor     +	k * cookies[2].flavor     +	l * cookies[3].flavor;
					long long int texture =		i * cookies[0].texture    +	j * cookies[1].texture    +	k * cookies[2].texture    +	l * cookies[3].texture;

					if (capacity <= 0 || durability <= 0 || flavor <= 0 || texture <= 0) continue;

					unsigned long long int score = capacity * durability * flavor * texture;

					if (score > result) result = score;
				}
			}
		}

		std::cout << result << std::endl;
	}

	void part2()
	{
		std::vector<Cookie> cookies;
		unsigned long long int result = 0;

		for (const auto& line : getLineByLine<Cookie>("day15.txt", [&cookies](std::string& var)
		{
			std::replace(var.begin(), var.end(), ',', ' ');
			std::istringstream iss(var);
			std::vector<std::string> splitted(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
			return Cookie{ std::stoi(splitted[2]), std::stoi(splitted[4]), std::stoi(splitted[6]), std::stoi(splitted[8]), std::stoi(splitted[10]) };
		}))
		{
			cookies.push_back(line);
		}

		for (int i = 1; i <= 100; ++i)
		{
			for (int j = 1; j <= 100 - i; ++j)
			{
				for (int k = 1; k <= 100 - i - j; ++k)
				{
					int l = 100 - i - j - k;

					long long int capacity =	i * cookies[0].capacity   +	j * cookies[1].capacity   +	k * cookies[2].capacity   +	l * cookies[3].capacity;
					long long int durability =	i * cookies[0].durability + j * cookies[1].durability +	k * cookies[2].durability + l * cookies[3].durability;
					long long int flavor =		i * cookies[0].flavor     +	j * cookies[1].flavor	  +	k * cookies[2].flavor     +	l * cookies[3].flavor;
					long long int texture =		i * cookies[0].texture	  +	j * cookies[1].texture	  +	k * cookies[2].texture    +	l * cookies[3].texture;
					long long int calories =	i * cookies[0].calories	  + j * cookies[1].calories	  + k * cookies[2].calories	  + l * cookies[3].calories;

					if (calories != 500 || capacity <= 0 || durability <= 0 || flavor <= 0 || texture <= 0) continue;

					unsigned long long int score = capacity * durability * flavor * texture;

					if (score > result) result = score;
				}
			}
		}

		std::cout << result << std::endl;
	}
}

namespace day16
{
	void part1()
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

		for (const auto& line : getLineByLine<std::vector<std::string>>("day16.txt", [&myAunt](std::string& var)
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
				std::cout << line[1] << std::endl;
				break;
			}
		}
	}

	void part2()
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

		for (const auto& line : getLineByLine<std::vector<std::string>>("day16.txt", [&myAunt](std::string& var)
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
				std::cout << line[1] << std::endl;
				break;
			}
		}
	}
}

namespace day17
{
	void combinations(std::vector<std::vector<int>>& result, std::vector<int>& numbers, int startPosition, std::vector<int> current, int count)
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

	void part1()
	{
		std::vector<int> numbers;
		std::vector<std::vector<int>> result;

		for (const auto& line : getLineByLine<int>("day17.txt", [&numbers](std::string& var)
		{
			return std::stoi(var);
		}))
		{
			numbers.push_back(line);
		}

		std::sort(numbers.begin(), numbers.end(), std::greater<int>());

		for (size_t i = 0; i < numbers.size(); ++i)
		{
			combinations(result, numbers, i, {}, 0);
		}

		std::cout << result.size() << std::endl;
	}

	void part2()
	{
		std::vector<int> numbers;
		std::vector<std::vector<int>> results;

		for (const auto& line : getLineByLine<int>("day17.txt", [&numbers](std::string& var)
		{
			return std::stoi(var);
		}))
		{
			numbers.push_back(line);
		}

		std::sort(numbers.begin(), numbers.end(), std::greater<int>());

		for (size_t i = 0; i < numbers.size(); ++i)
		{
			combinations(results, numbers, i, {}, 0);
		}

		unsigned int minimum = numbers.size();
		for (const auto& var : results) if (var.size() < minimum) minimum = var.size();

		int result = 0;
		for (const auto& var : results) if (var.size() == minimum) ++result;

		std::cout << result << std::endl;
	}
}

namespace day18
{
	void part1()
	{
		std::array<std::array<char, 102>, 102> one;
		std::array<std::array<char, 102>, 102> two;

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

		for (const auto& line : getLineByLine("day18.txt"))
		{
			for (size_t i = 0; i < line.size(); ++i) one[lineNumber][i + 1] = line[i];
			++lineNumber;
		}

		auto* read = &one;
		auto* write = &two;

		for (int i = 0; i < 100; ++i)
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

					if (((*read)[y][x] == '#') && (neighboursOn == 2 || neighboursOn == 3)) (*write)[y][x] = '#';
					else if (((*read)[y][x] == '.') && (neighboursOn == 3)) (*write)[y][x] = '#';
					else (*write)[y][x] = '.';
				}
			}
		}

		unsigned int result = 0;
		for (const auto& line : one)
		{
			for (const auto& element : line) if (element == '#') ++result;
		}

		std::cout << result << std::endl;
	}

	void part2()
	{
		std::array<std::array<char, 102>, 102> one;
		std::array<std::array<char, 102>, 102> two;

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

		for (const auto& line : getLineByLine("day18.txt"))
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

		for (int i = 0; i < 100; ++i)
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

					if (((*read)[y][x] == '#') && (neighboursOn == 2 || neighboursOn == 3)) (*write)[y][x] = '#';
					else if (((*read)[y][x] == '.') && (neighboursOn == 3)) (*write)[y][x] = '#';
					else (*write)[y][x] = '.';
				}
			}

			(*write)[1][1] = '#';
			(*write)[1][100] = '#';
			(*write)[100][1] = '#';
			(*write)[100][100] = '#';
		}

		unsigned int result = 0;
		for (const auto& line : one)
		{
			for (const auto& element : line) if (element == '#') ++result;
		}

		std::cout << result << std::endl;
	}
}

namespace day19
{
	void part1()
	{
		std::map<std::string, std::vector<std::string>> replacements;
		std::set<std::string> result;

		for (const auto& line : getLineByLine<std::vector<std::string>>("day19_1.txt", [&replacements](std::string& var)
		{
			std::istringstream iss(var);
			std::vector<std::string> splitted(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
			return splitted;
		}))
		{
			if (replacements.find(line[0]) == replacements.end()) replacements.insert({ line[0], { line[2] } });
			else replacements.at(line[0]).push_back(line[2]);
		}

		auto line = getLine("day19_2.txt");

		for (size_t i = 0; i < line.size() - 1; ++i)
		{
			std::string key{ line[i] };
			if (replacements.find(key) != replacements.end())
			{
				for (const auto& replacement : replacements.at(key))
				{
					auto temp = line;
					temp.replace(i, 1, replacement);
					result.insert(temp);
				}
			}

			key += line[i + 1];
			if (replacements.find(key) != replacements.end())
			{
				for (const auto& replacement : replacements.at(key))
				{
					auto temp = line;
					temp.replace(i, 2, replacement);
					result.insert(temp);
				}
			}
		}

		std::string key{ line[line.size() - 1] };
		if (replacements.find(key) != replacements.end())
		{
			for (const auto& replacement : replacements.at(key))
			{
				auto temp = line;
				temp.replace(line.size() - 1, 1, replacement);
				result.insert(temp);
			}
		}

		std::cout << result.size() << std::endl;
	}

	void part2()
	{
		auto line = getLine("day19_2.txt");

		int total = 0;
		for (auto& element : line) if (element >= 'A' && element <= 'Z') ++total;

		int ar = 0;
		int rn = 0;
		int y = 0;
		for (size_t i = 0; i < line.size() - 1; ++i)
		{
			if (line[i] == 'A' && line[i + 1] == 'r') ++ar;
			if (line[i] == 'R' && line[i + 1] == 'n') ++rn;
			if (line[i] == 'Y') ++y;
		}

		std::cout << (total - ar - rn - 2 * y - 1) << std::endl;
	}
}

namespace day20
{
	void part1()
	{
		auto line = getLine<int>("day20.txt", [](std::string& var) { return std::stoi(var); });
		auto size = line / 10;

		std::vector<int> houses(size, 0);

		for (auto i = 1; i <= size; ++i)
		{
			auto value = i * 10;
			for (auto j = 1; j <= (size / i); ++j)
			{
				houses[i * j - 1] += value;
			}

			if (houses[i - 1] >= line)
			{
				std::cout << i << std::endl;
				break;
			}
		}
	}

	void part2()
	{
		auto line = getLine<int>("day20.txt", [](std::string& var) { return std::stoi(var); });
		auto size = line / 11;

		std::vector<int> houses(size, 0);

		for (auto i = 1; i <= size; ++i)
		{
			auto value = i * 11;
			for (auto j = 1; j <= std::min((size / i), 50); ++j)
			{
				houses[i * j - 1] += value;
			}

			if (houses[i - 1] >= line)
			{
				std::cout << i << std::endl;
				break;
			}
		}
	}
}

namespace day21
{
	struct Entity
	{
		int HP;
		int DMG;
		int ARM;
	};

	struct Item
	{
		int cost;
		int damage;
		int armor;
	};

	struct Result
	{
		int price;
		size_t w;
		size_t a;
		size_t r1;
		size_t r2;
	};

	std::vector<Item> Weapons
	{
		{  8, 4, 0 },
		{ 10, 5, 0 },
		{ 25, 6, 0 },
		{ 40, 7, 0 },
		{ 74, 8, 0 }
	};

	std::vector<Item> Armors
	{
		{   0, 0, 0 },
		{  13, 0, 1 },
		{  31, 0, 2 },
		{  53, 0, 3 },
		{  75, 0, 4 },
		{ 102, 0, 5 }
	};

	std::vector<Item> Rings
	{
		{   0, 0, 0 },
		{  25, 1, 0 },
		{  50, 2, 0 },
		{ 100, 3, 0 },
		{  20, 0, 1 },
		{  40, 0, 2 },
		{  80, 0, 3 }
	};

	bool simulate(Entity& player, Entity& boss)
	{
		while (true)
		{
			boss.HP = boss.HP + boss.ARM - player.DMG;
			if (boss.HP <= 0) return true;
			player.HP = player.HP + player.ARM - boss.DMG;
			if (player.HP <= 0) return false;
		}
	}

	void part1()
	{
		Result result{ 99999, 0, 0, 0 };

		for (size_t w = 0; w < Weapons.size(); ++w)
		{
			for (size_t a = 0; a < Armors.size(); ++a)
			{
				for (size_t r1 = 0; r1 < Armors.size(); ++r1)
				{
					for (size_t r2 = 0; r2 < Armors.size(); ++r2)
					{
						Entity player
						{ 
							100,
							Weapons[w].damage + Armors[a].damage + Rings[r1].damage + (r1 != r2 ? Rings[r2].damage : 0),
							Weapons[w].armor + Armors[a].armor + Rings[r1].armor + (r1 != r2 ? Rings[r2].armor : 0)
						};
						Entity boss{ 104, 8, 1 };

						if (simulate(player, boss))
						{
							auto price = Weapons[w].cost + Armors[a].cost + Rings[r1].cost + (r1 != r2 ? Rings[r2].cost : 0);
							if (price < result.price) result = { price, w, a, r1, r2};
						}
					}
				}
			}
		}

		std::cout << result.price << " (" << result.w << ", " << result.a << ", " << result.r1 << ", " << result.r2 << ")" <<std::endl;
	}

	void part2()
	{
		Result result{ 0, 0, 0, 0 };

		for (size_t w = 0; w < Weapons.size(); ++w)
		{
			for (size_t a = 0; a < Armors.size(); ++a)
			{
				for (size_t r1 = 0; r1 < Armors.size(); ++r1)
				{
					for (size_t r2 = 0; r2 < Armors.size(); ++r2)
					{
						Entity player
						{
							100,
							Weapons[w].damage + Armors[a].damage + Rings[r1].damage + (r1 != r2 ? Rings[r2].damage : 0),
							Weapons[w].armor + Armors[a].armor + Rings[r1].armor + (r1 != r2 ? Rings[r2].armor : 0)
						};
						Entity boss{ 104, 8, 1 };

						if (!simulate(player, boss))
						{
							auto price = Weapons[w].cost + Armors[a].cost + Rings[r1].cost + (r1 != r2 ? Rings[r2].cost : 0);
							if (price > result.price) result = { price, w, a, r1, r2 };
						}
					}
				}
			}
		}

		std::cout << result.price << " (" << result.w << ", " << result.a << ", " << result.r1 << ", " << result.r2 << ")" << std::endl;
	}
}

namespace day22
{
	struct Player
	{
		int HP;
		int MAN;
	};

	struct Boss
	{
		int HP;
		int DMG;
	};

	int simulate(bool playerTurn, Player player, Boss boss, int s, int p, int r, bool hardMode = false)
	{
		if (playerTurn && hardMode)
		{
			player.HP -= 1;
		}

		if (p)
		{
			boss.HP -= 3;
			--p;
		}

		if (player.HP <= 0) return 99999;
		if (boss.HP <= 0) return 0;

		if (r)
		{
			player.MAN += 101;
			--r;
		}

		if (playerTurn)
		{
			int results[]{ 99999, 99999, 99999, 99999, 99999 };
			if (s) --s;

			// MAGIC MISSILE
			if (player.MAN >= 53)
			{
				results[0] = 53 + simulate(false, { player.HP, player.MAN - 53 }, { boss.HP - 4, boss.DMG }, s, p, r, hardMode);
			}
			// DRAIN
			if (player.MAN >= 73)
			{
				results[1] = 73 + simulate(false, { player.HP + 2, player.MAN - 73 }, { boss.HP - 2, boss.DMG }, s, p, r, hardMode);
			}
			// SHIELD
			if (player.MAN >= 113 && !s)
			{
				results[2] = 113 + simulate(false, { player.HP, player.MAN - 113 }, { boss.HP, boss.DMG }, 6, p, r, hardMode);
			}
			// POISON
			if (player.MAN >= 173 && !p)
			{
				results[3] = 173 + simulate(false, { player.HP, player.MAN - 173 }, { boss.HP, boss.DMG }, s, 6, r, hardMode);
			}
			// RECHARGE
			if (player.MAN >= 229 && !r)
			{
				results[4] = 229 + simulate(false, { player.HP, player.MAN - 229 }, { boss.HP, boss.DMG }, s, p, 5, hardMode);
			}

			return *std::min_element(results, results + 5);
		}
		else
		{
			return simulate(true, { player.HP - boss.DMG + (s ? 7 : 0) , player.MAN }, { boss.HP, boss.DMG }, (s ? s - 1 : s), p, r, hardMode);
		}
	}

	void part1()
	{
		std::cout << simulate(true, { 50, 500 }, { 71, 10 }, 0, 0, 0) << std::endl;
	}

	void part2()
	{
		std::cout << simulate(true, { 50, 500 }, { 71, 10 }, 0, 0, 0, true) << std::endl;
	}
}

int main()
{
	std::cout << "Day 1 Part 1: "; day1::part1();
	std::cout << "Day 1 Part 2: "; day1::part2();
	std::cout << "Day 2 Part 1: "; day2::part1();
	std::cout << "Day 2 Part 2: "; day2::part2();
	std::cout << "Day 3 Part 1: "; day3::part1();
	std::cout << "Day 3 Part 2: "; day3::part2();
	std::cout << "Day 4 Part 1: "; day4::part1();
	std::cout << "Day 4 Part 2: "; day4::part2();
	std::cout << "Day 5 Part 1: "; day5::part1();
	std::cout << "Day 5 Part 2: "; day5::part2();
	std::cout << "Day 6 Part 1: "; day6::part1();
	std::cout << "Day 6 Part 2: "; day6::part2();
	std::cout << "Day 7 Part 1: "; day7::part1();
	std::cout << "Day 7 Part 2: "; day7::part2();
	std::cout << "Day 8 Part 1: "; day8::part1();
	std::cout << "Day 8 Part 2: "; day8::part2();
	std::cout << "Day 9 Part 1: "; day9::part1();
	std::cout << "Day 9 Part 2: "; day9::part2();
	std::cout << "Day 10 Part 1: "; day10::part1();
	std::cout << "Day 10 Part 2: "; day10::part2();
	std::cout << "Day 11 Part 1: "; day11::part1();
	std::cout << "Day 11 Part 2: "; day11::part2();
	std::cout << "Day 12 Part 1: "; day12::part1();
	std::cout << "Day 12 Part 2: "; day12::part2();
	std::cout << "Day 13 Part 1: "; day13::part1();
	std::cout << "Day 13 Part 2: "; day13::part2();
	std::cout << "Day 14 Part 1: "; day14::part1();
	std::cout << "Day 14 Part 2: "; day14::part2();
	std::cout << "Day 15 Part 1: "; day15::part1();
	std::cout << "Day 15 Part 2: "; day15::part2();
	std::cout << "Day 16 Part 1: "; day16::part1();
	std::cout << "Day 16 Part 2: "; day16::part2();
	std::cout << "Day 17 Part 1: "; day17::part1();
	std::cout << "Day 17 Part 2: "; day17::part2();
	std::cout << "Day 18 Part 1: "; day18::part1();
	std::cout << "Day 18 Part 2: "; day18::part2();
	std::cout << "Day 19 Part 1: "; day19::part1();
	std::cout << "Day 19 Part 2: "; day19::part2();
	std::cout << "Day 20 Part 1: "; day20::part1();
	std::cout << "Day 20 Part 2: "; day20::part2();
	std::cout << "Day 21 Part 1: "; day21::part1();
	std::cout << "Day 21 Part 2: "; day21::part2();
	std::cout << "Day 22 Part 1: "; day22::part1();
	std::cout << "Day 22 Part 2: "; day22::part2();
	system("pause");
	return 0;
}
 