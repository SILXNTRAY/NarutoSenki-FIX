#pragma once
#include "Hero.hpp"

class Centipede : public Hero
{
	void perform() override
	{
		if (notFindFlog(0))
		{
			if (notFindTower(0))
				_mainTarget = nullptr;
		}

		if (_mainTarget)
		{
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTargetAndIgnoreOriginY();

			if (_mainTarget->isTower() ||
				_mainTarget->isFlog())
			{
				if (abs(sp.x) > 32 || abs(sp.y) > 32)
				{
					moveDirection = sp.getNormalized();
					walk(moveDirection);
				}
				else
				{
					changeSide(sp);
					attack(NAttack);
				}

				return;
			}
		}

		stepOn();
	}
};
