#pragma once
#include "Hero.hpp"

class Mask : public Hero
{
	void perform() override
	{
		if (getName() == KugutsuEnum::MaskRaiton)
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
		}
		else
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
		}

		if (_mainTarget)
		{
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTarget();

			if (_mainTarget->isTower())
			{
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
			else
			{
				if (abs(sp.x) > 96 || abs(sp.y) > 16)
				{
					moveDirection = sp.getNormalized();
					walk(moveDirection);
					return;
				}
				else if ((abs(sp.x) > 48 || abs(sp.y) > 16) && !_isCanSkill1)
				{
					moveDirection = sp.getNormalized();
					walk(moveDirection);
					return;
				}
				else if (isFreeState())
				{
					if (_isCanSkill1 && _mainTarget->getDEF() < 5000)
					{
						changeSide(sp);
						attack(SKILL1);
					}
					else
					{
						changeSide(sp);
						attack(NAttack);
					}
				}
				return;
			}
		}

		stepOn();
	}

	void dealloc() override
	{
		if (_master->hearts > 0)
		{
			_master->unlockSkill4Button();
		}

		Hero::dealloc();
	}
};
