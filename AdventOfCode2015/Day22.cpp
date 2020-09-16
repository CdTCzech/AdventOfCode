#include "Day22.h"

#include <algorithm>

namespace day22
{
	int64_t simulate(const bool playerTurn, Player player, Boss boss, int s, int p, int r, const bool hardMode = false)
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
			int64_t results[]{ 99999, 99999, 99999, 99999, 99999 };
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

		return simulate(true, { player.HP - boss.DMG + (s ? 7 : 0) , player.MAN }, { boss.HP, boss.DMG }, (s ? s - 1 : s), p, r, hardMode);
	}

	int64_t part1()
	{
		return simulate(true, { 50, 500 }, { 71, 10 }, 0, 0, 0);
	}

	int64_t part2()
	{
		return simulate(true, { 50, 500 }, { 71, 10 }, 0, 0, 0, true);
	}
} // namespace day22