#pragma once
#include "Hero.hpp"

class Guardian : public Hero
{
	void perform() override
	{
		if (!findTargetEnemy(Role::Hero, true))
		{
			if (!findTargetEnemy(Role::Flog, true))
			{
				if (!findTargetEnemy(Role::Flog, false))
				{
					if (!findTargetEnemy(Role::Hero, false))
					{
						_mainTarget = nullptr;
					}
				}
			}
		}

		if (_mainTarget)
		{
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTargetAndIgnoreOriginY();

			if (abs(sp.x) > 128 || abs(sp.y) > 16)
			{
				moveDirection = sp.getNormalized();
				walk(moveDirection);
				return;
			}
			else if (abs(sp.x) > 32 || abs(sp.y) > 32)
			{
				moveDirection = sp.getNormalized();
				walk(moveDirection);
				return;
			}

			if (isFreeState())
			{
				bool isTurn = false;
				auto gardTower = getGameLayer()->getGuardianGroup();

				for (auto targetTower : getGameLayer()->_TowerArray)
				{
					if (targetTower->getName() == gardTower && targetTower->getHpPercent() < 0.5f)
					{
						isTurn = true;
					}
				}

				if (_isCanSkill1 && !_skillChangeBuffValue && (getHpPercent() < 0.5f || isTurn))
				{
					changeSide(sp);
					attack(SKILL1);
					scheduleOnce(schedule_selector(CharacterBase::enableSkill1), _sAttackCD1);
				}
				else if (_isCanSkill2 && _skillChangeBuffValue)
				{
					changeSide(sp);
					attack(SKILL2);
					scheduleOnce(schedule_selector(CharacterBase::enableSkill2), _sAttackCD2);
				}
				else
				{
					changeSide(sp);
					attack(NAttack);
				}
			}

			return;
		}
		else
		{
			Vec2 moveDirection;
			Vec2 sp = getSpawnPoint() - getPosition();

			if (abs(sp.x) > 32 || abs(sp.y) > 32)
			{
				moveDirection = sp.getNormalized();
				walk(moveDirection);
				return;
			}

			idle();
		}
	}

	void changeAction() override
	{
		setNAttackValue(getNAttackValue() + 700);
		_nAttackRangeX = 0;
		_nAttackRangeY = 48;
		_originNAttackType = _nAttackType;
		_nAttackType = _spcAttackType2;

		_isArmored = true;
		hasArmorBroken = true;
		if (_hpBar)
		{
			_hpBar->setPositionY(120);
		}
		setWalkAction(createAnimation(skillSPC1Array, 10, true, false));
		setNAttackAction(createAnimation(skillSPC2Array, 10, false, true));
		setIdleAction(createAnimation(skillSPC3Array, 5, true, false));
	}

private:
	string _originNAttackType;
};
