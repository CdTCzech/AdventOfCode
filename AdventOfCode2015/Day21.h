#pragma once

#include <cstdint>

#include <vector>

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
		int64_t price;
		size_t w;
		size_t a;
		size_t r1;
		size_t r2;
	};

	inline std::vector<Item> Weapons
	{
		{ 8, 4, 0 },
		{ 10, 5, 0 },
		{ 25, 6, 0 },
		{ 40, 7, 0 },
		{ 74, 8, 0 }
	};

	inline std::vector<Item> Armors
	{
		{ 0, 0, 0 },
		{ 13, 0, 1 },
		{ 31, 0, 2 },
		{ 53, 0, 3 },
		{ 75, 0, 4 },
		{ 102, 0, 5 }
	};

	inline std::vector<Item> Rings
	{
		{ 0, 0, 0 },
		{ 25, 1, 0 },
		{ 50, 2, 0 },
		{ 100, 3, 0 },
		{ 20, 0, 1 },
		{ 40, 0, 2 },
		{ 80, 0, 3 }
	};

	int64_t part1();
	int64_t part2();
}  // namespace day21