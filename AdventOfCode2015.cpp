#include "Days/Day1.h"
#include "Days/Day2.h"
#include "Days/Day3.h"
#include "Days/Day4.h"
#include "Days/Day5.h"
#include "Days/Day6.h"
#include "Days/Day7.h"
#include "Days/Day8.h"
#include "Days/Day9.h"
#include "Days/Day10.h"
#include "Days/Day11.h"
#include "Days/Day12.h"
#include "Days/Day13.h"
#include "Days/Day14.h"
#include "Days/Day15.h"
#include "Days/Day16.h"
#include "Days/Day17.h"
#include "Days/Day18.h"
#include "Days/Day19.h"
#include "Days/Day20.h"
#include "Days/Day21.h"
#include "Days/Day22.h"
#include "Days/Day23.h"
#include "Days/Day24.h"
#include "Days/Day25.h"

#include "Test.h"

#include <cstdint>
#include <string>

int main(int /*argc*/, char** /*argv*/)
{
	try
	{
		test::test<int64_t>(1, 1,             232, day1::part1);
		test::test<int64_t>(1, 2,           1'783, day1::part2);
		test::test<int64_t>(2, 1,       1'598'415, day2::part1);
		test::test<int64_t>(2, 2,       3'812'909, day2::part2);
		test::test<int64_t>(3, 1,           2'081, day3::part1);
		test::test<int64_t>(3, 2,           2'341, day3::part2);
		test::test<int64_t>(4, 1,         282'749, day4::part1);
		test::test<int64_t>(4, 2,       9'962'624, day4::part2);
		test::test<int64_t>(5, 1,             255, day5::part1);
		test::test<int64_t>(5, 2,              55, day5::part2);
		test::test<int64_t>(6, 1,         377'891, day6::part1);
		test::test<int64_t>(6, 2,      14'110'788, day6::part2);
		test::test<int64_t>(7, 1,          16'076, day7::part1);
		test::test<int64_t>(7, 2,           2'797, day7::part2);
		test::test<int64_t>(8, 1,           1'333, day8::part1);
		test::test<int64_t>(8, 2,           2'046, day8::part2);
		test::test<int64_t>(9, 1,             251, day9::part1);
		test::test<int64_t>(9, 2,             898, day9::part2);
		test::test<int64_t>(10, 1,         360154, day10::part1);
		test::test<int64_t>(10, 2,        5103798, day10::part2);
		test::test<std::string>(11, 1, "hepxxyzz", day11::part1);
		test::test<std::string>(11, 2, "heqaabcc", day11::part2);
		test::test<int64_t>(12, 1,        111'754, day12::part1);
		test::test<int64_t>(12, 2,         65'402, day12::part2);
		test::test<int64_t>(13, 1,            733, day13::part1);
		test::test<int64_t>(13, 2,            725, day13::part2);
		test::test<int64_t>(14, 1,          2'696, day14::part1);
		test::test<int64_t>(14, 2,          1'084, day14::part2);
		test::test<int64_t>(15, 1,        222'870, day15::part1);
		test::test<int64_t>(15, 2,        117'936, day15::part2);
		test::test<int64_t>(16, 1,             40, day16::part1);
		test::test<int64_t>(16, 2,            241, day16::part2);
		test::test<int64_t>(17, 1,          4'372, day17::part1);
		test::test<int64_t>(17, 2,              4, day17::part2);
		test::test<int64_t>(18, 1,            821, day18::part1);
		test::test<int64_t>(18, 2,            886, day18::part2);
		test::test<int64_t>(19, 1,            576, day19::part1);
		test::test<int64_t>(19, 2,            207, day19::part2);
		test::test<int64_t>(20, 1,        831'600, day20::part1);
		test::test<int64_t>(20, 2,        884'520, day20::part2);
		test::test<int64_t>(21, 1,             78, day21::part1);
		test::test<int64_t>(21, 2,            148, day21::part2);
		test::test<int64_t>(22, 1,          1'824, day22::part1);
		test::test<int64_t>(22, 2,          1'937, day22::part2);
		test::test<int64_t>(23, 1,            184, day23::part1);
		test::test<int64_t>(23, 2,            231, day23::part2);
		test::test<int64_t>(24, 1, 10'723'906'903, day24::part1);
		test::test<int64_t>(24, 2,     74'850'409, day24::part2);
		test::test<int64_t>(25, 1,      2'650'453, day25::part1);
	}
	catch (std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
	}

	system("pause");
	return 0;
}
