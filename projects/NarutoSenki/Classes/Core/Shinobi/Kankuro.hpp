#pragma once
#include "Hero.hpp"
#include "Kuchiyose/Karasu.hpp"
#include "Kuchiyose/Sanshouuo.hpp"
#include "Kuchiyose/Saso.hpp"

class Kankuro : public Hero
{
	void setID(const string &name, Role role, Group group) override
	{
		Hero::setID(name, role, group);

		getGameLayer()->onHUDInitialized(BIND(Kankuro::tryLockSkillButton));
	}

	void perform() override
	{
		_mainTarget = nullptr;
		findHeroHalf();

		tryUseGear6();
		tryBuyGear(GearType::Gear06, GearType::Gear04, GearType::Gear08);

		if (needBackToTowerToRestoreHP() ||
			needBackToDefendTower())
			return;

		bool isFound1 = false;
		bool isFound2 = false;
		bool isFound3 = false;

		if (hasMonsterArrayAny())
		{
			for (auto mo : _monsterArray)
			{
				if (mo->getName() == KugutsuEnum::Saso)
				{
					isFound3 = true;
				}
				else if (mo->getName() == KugutsuEnum::Sanshouuo)
				{
					isFound2 = true;
				}
				else if (mo->getName() == KugutsuEnum::Karasu)
				{
					isFound1 = true;
				}
			}
		}

		if (_mainTarget && _mainTarget->isNotFlog())
		{
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTarget();

			if (isFreeState())
			{
				if (_isCanSkill3)
				{
					changeSide(sp);
					attack(SKILL3);
					return;
				}
				else if (_isCanSkill1 && !isFound1 && !_isControlled)
				{
					attack(SKILL1);
					return;
				}
				else if (_isCanOugis1 && !_isControlled && !isFound2)
				{
					changeSide(sp);
					attack(OUGIS1);
					return;
				}
				else if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && !isFound3)
				{
					changeSide(sp);
					attack(OUGIS2);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 5000 && !_isHealing && !_isControlled)
				{
					if (abs(sp.x) < 160)
						stepBack2();
					else
						idle();
					return;
				}
				else if (abs(sp.x) < 128)
				{
					if (abs(sp.x) > 32 || abs(sp.y) > 32)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					else
					{
						changeSide(sp);
						attack(NAttack);
					}

					return;
				}
			}
		}
		_mainTarget = nullptr;
		if (notFindFlogHalf())
			findTowerHalf();

		if (_mainTarget)
		{
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTarget();

			if (abs(sp.x) > 32 || abs(sp.y) > 32)
			{
				moveDirection = sp.getNormalized();
				walk(moveDirection);
				return;
			}

			if (isFreeState())
			{
				if (_isCanOugis1 && !_isControlled && !isFound2)
				{
					changeSide(sp);
					attack(OUGIS1);
				}
				else if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && !isFound3)
				{
					changeSide(sp);
					attack(OUGIS2);
				}
				else if (_isCanSkill1 && !isFound1)
				{
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

		checkHealingState();
	}

	void changeAction() override
	{
		if (isPlayer())
		{
			getGameLayer()->getHudLayer()->skill1Button->setLock();
			getGameLayer()->getHudLayer()->skill2Button->unLock();
		}
	}

	void setActionResume() override
	{
		if (isPlayer())
		{
			getGameLayer()->getHudLayer()->skill1Button->unLock();
			getGameLayer()->getHudLayer()->skill2Button->setLock();
		}
		_skillChangeBuffValue = 0;
	}

	void dealloc() override
	{
		Hero::dealloc();

		unlockOugisButtons();
	}

	Hero *createClone(int cloneTime) override
	{
		Hero *clone = nullptr;

		if (cloneTime == 0)
		{
			clone = createKugutsuHero<Karasu>(KugutsuEnum::Karasu);
		}
		else if (cloneTime == 1)
		{
			clone = createKugutsuHero<Sanshouuo>(KugutsuEnum::Sanshouuo);
			lockSkill4Button();
		}
		else if (cloneTime == 2)
		{
			clone = createKugutsuHero<Saso>(KugutsuEnum::Saso);
			lockSkill5Button();
		}

		clone->_isArmored = true;
		_monsterArray.push_back(clone);
		return clone;
	}

private:
	void tryLockSkillButton()
	{
		if (isPlayer())
		{
			getGameLayer()->getHudLayer()->skill2Button->setLock();
		}
	}
};
