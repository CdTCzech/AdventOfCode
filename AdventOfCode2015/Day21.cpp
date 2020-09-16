#include "Day21.h"

namespace day21
{
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

	int64_t part1()
	{
		Result result{ 99999, 0, 0, 0, 0 };

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
							const auto price = Weapons[w].cost + Armors[a].cost + Rings[r1].cost + (r1 != r2 ? Rings[r2].cost : 0);
							if (price < result.price) result = { price, w, a, r1, r2 };
						}
					}
				}
			}
		}

		return result.price;
	}

	int64_t part2()
	{
		Result result{ 0, 0, 0, 0, 0 };

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
							const auto price = Weapons[w].cost + Armors[a].cost + Rings[r1].cost + (r1 != r2 ? Rings[r2].cost : 0);
							if (price > result.price) result = { price, w, a, r1, r2 };
						}
					}
				}
			}
		}

		return result.price;
	}
} // namespace day21