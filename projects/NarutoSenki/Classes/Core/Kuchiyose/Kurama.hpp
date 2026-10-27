#pragma once
#include "Hero.hpp"

class Kurama : public Hero
{
	void perform() override
	{
		if (notFindHero(0))
		{
			if (notFindFlog(0))
			{
				if (notFindTower(0))
				{
					_mainTarget = nullptr;
				}
			}
		}

		if (_mainTarget)
		{
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTarget();

			if (abs(sp.x) > 156 || abs(sp.y) > 48)
			{
				moveDirection = sp.getNormalized();
				walk(moveDirection);
			}
			else
			{
				if (isFreeState())
				{
					changeSide(sp);
					attack(NAttack);
				}
			}

			return;
		}

		stepOn();
	}
};
