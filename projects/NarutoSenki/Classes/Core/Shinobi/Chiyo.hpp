#pragma once
#include "Hero.hpp"
#include "Kuchiyose/Parents.hpp"

class Chiyo : public Hero
{
	void setID(const string &name, Role role, Group group) override
	{
		Hero::setID(name, role, group);

		getGameLayer()->onHUDInitialized(BIND(Chiyo::tryLockSkillButton));
	}

	void perform() override
	{
		_mainTarget = nullptr;
		findHeroHalf();

		tryUseGear6();
		tryBuyGear(GearType::Gear06, GearType::Gear07, GearType::Gear04);

		if (needBackToTowerToRestoreHP() ||
			needBackToDefendTower())
			return;

		bool isFound1 = false;

		if (hasMonsterArrayAny())
		{
			for (auto mo : _monsterArray)
			{
				if (mo->getName() == KugutsuEnum::Parents)
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
				if (_isCanOugis1 && !_isControlled && !_buffStartTime)
				{
					int countNum = 0;
					for (auto hero : getGameLayer()->_CharacterArray)
					{
						if (getGroup() == hero->getGroup() &&
							hero->isPlayerOrCom() &&
							hero->getState() != State::DEAD &&
							hero->getName() != HeroEnum::Chiyo)
						{
							Vec2 sp = hero->getPosition() - getPosition();
							if (sp.x <= kAttackRange)
								countNum++;
						}
					}
					if (countNum >= 1)
					{
						attack(OUGIS1);
						return;
					}
				}
				if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && _mainTarget->getDEF() < 5000 && !_mainTarget->_isArmored && _mainTarget->getState() != State::KNOCKDOWN && !_mainTarget->_isSticking)
				{
					if (abs(sp.x) > 96 || abs(sp.y) > 32)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					else if (abs(sp.x) < 48)
					{
						stepBack();
						return;
					}
					changeSide(sp);
					attack(OUGIS2);
				}
				else if (_isCanSkill1 && !isFound1 && !_isControlled)
				{
					attack(SKILL1);
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
				if (_isCanSkill1 && !isFound1)
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
			getGameLayer()->getHudLayer()->skill3Button->unLock();
		}
	}

	void setActionResume() override
	{
		if (isPlayer())
		{
			getGameLayer()->getHudLayer()->skill1Button->unLock();
			getGameLayer()->getHudLayer()->skill2Button->setLock();
			getGameLayer()->getHudLayer()->skill3Button->setLock();
		}
		_skillChangeBuffValue = 0;
	}

	Hero *createClone(int cloneTime) override
	{
		auto clone = createKugutsuHero<Parents>(KugutsuEnum::Parents);
		clone->setPosition(Vec2(getPositionX(), getPositionY() - 3));
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
			getGameLayer()->getHudLayer()->skill3Button->setLock();
		}
	}
};
