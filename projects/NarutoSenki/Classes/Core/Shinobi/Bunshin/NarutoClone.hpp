#pragma once
#include "Hero.hpp"

class NarutoClone : public Hero
{
	void perform() override
	{
		if (notFindFlog(0))
		{
			if (notFindHero(0))
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

			if (abs(sp.x) > 32 || abs(sp.y) > 32)
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
