#pragma once
#include "Hero.hpp"

class Slug : public Hero
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
					if (isFreeState())
					{
						if (_isCanSkill1)
						{
							attack(SKILL1);
							scheduleOnce(schedule_selector(CharacterBase::enableSkill1), _sAttackCD1);
						}
						else if (_isCanSkill2)
						{
							attack(SKILL2);
							scheduleOnce(schedule_selector(CharacterBase::enableSkill2), _sAttackCD2);
						}
						else
						{
							changeSide(sp);
							attack(NAttack);
						}
					}
				}

				return;
			}
		}

		stepOn();
	}
};
