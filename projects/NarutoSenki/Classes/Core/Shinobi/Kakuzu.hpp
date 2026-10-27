#pragma once
#include "Hero.hpp"
#include "Kuchiyose/Mask.hpp"

class Kakuzu : public Hero
{
	void dead() override
	{
		CharacterBase::dead();

		if (_heartEffect)
		{
			auto frame = getSpriteFrame("Heart_Effect_{:02d}", hearts);
			_heartEffect->setDisplayFrame(frame);
		}

		if (getLV() >= 2)
		{
			unlockSkill4Button();
		}
	}

	void changeHPbar() override
	{
		Hero::changeHPbar();

		if (isNotPlayer())
			return;

		// NOTE: The level was increased on base
		// We should do the same here
		if (_exp >= 500 && _level == 1 + 1)
		{
			if (hearts < 1)
			{
				getGameLayer()->getHudLayer()->skill4Button->setLock();
			}
		}
		else if (_exp >= 1500 && _level == 3 + 1)
		{
			getGameLayer()->getHudLayer()->skill5Button->setLock();
		}
	}

	void perform() override
	{
		_mainTarget = nullptr;

		if (isFreeState())
		{
			if (getHpPercent() > 0.3f && !_isControlled && _isCanSkill1)
			{
				float distance;
				float curDistance = 0;
				Vec2 sp;

				for (auto target : getGameLayer()->_CharacterArray)
				{
					if (target->isPlayerOrCom() &&
						target->getState() == State::DEAD)
					{
						sp = target->getPosition() - getPosition();
						distance = sp.getLength();

						if (abs(sp.x) < (kAttackRange))
						{
							if (target->_isTaunt)
							{
								_mainTarget = target;
							}
							if (curDistance && abs(curDistance) > abs(distance))
							{
								_mainTarget = target;
								curDistance = distance;
							}
							else if (!curDistance)
							{
								curDistance = distance;
								_mainTarget = target;
							}
						}
					}
				}

				if (_mainTarget)
				{
					Vec2 moveDirection;
					if (_mainTarget->_originY)
					{
						sp = Vec2(_mainTarget->getPositionX(), _mainTarget->_originY) - getPosition();
					}
					else
					{
						sp = _mainTarget->getPosition() - getPosition();
					}

					if (abs(sp.x) > 32 || abs(sp.y) > 32)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					else
					{
						changeSide(sp);
						attack(SKILL1);
					}

					return;
				}
			}
		}

		findHeroHalf();

		tryBuyGear(GearType::Gear03, GearType::Gear08, GearType::Gear04);

		if (needBackToTowerToRestoreHP() ||
			needBackToDefendTower())
			return;

		bool isSummonAble = false;

		if (_monsterArray.size() < 3 && hearts > 0)
		{
			isSummonAble = true;
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
				else if (_isCanOugis1 && !_isControlled && isSummonAble)
				{
					attack(OUGIS1);
					return;
				}
				else if (_isCanSkill2)
				{
					if (abs(sp.x) > 96 || abs(sp.y) > 32)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}

					if (_isCanGear03)
					{
						useGear(GearType::Gear03);
					}

					changeSide(sp);
					attack(SKILL2);
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
				if (_isCanOugis1 && !_isControlled && !isSummonAble)
				{
					changeSide(sp);
					attack(OUGIS1);
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
		setBuffEffect("jdBuff");
	}

	void resumeAction(float dt) override
	{
		removeBuffEffect("sBuff");

		CharacterBase::resumeAction(dt);
	}

	void setActionResume() override
	{
		unschedule(schedule_selector(Kakuzu::resumeAction));

		resumeAction(0);
	}

	Hero *createClone(int cloneTime) override
	{
		bool isRaiton = false;
		bool isFuton = false;
		bool isKaton = false;
		int countMon = 0;

		for (auto mo : _monsterArray)
		{
			if (mo->getName() == KugutsuEnum::MaskRaiton)
			{
				countMon++;
				isRaiton = true;
			}
			if (mo->getName() == KugutsuEnum::MaskFuton)
			{
				countMon++;
				isFuton = true;
			}
			if (mo->getName() == KugutsuEnum::MaskKaton)
			{
				countMon++;
				isKaton = true;
			}
		}

		Hero *clone = nullptr;
		if (hearts > 0 && (!isRaiton || !isKaton || !isFuton))
		{
			if (!isRaiton)
			{
				clone = createKugutsuHero<Mask>(KugutsuEnum::MaskRaiton);
			}
			else if (!isFuton)
			{
				clone = createKugutsuHero<Mask>(KugutsuEnum::MaskFuton);
			}
			else if (!isKaton)
			{
				clone = createKugutsuHero<Mask>(KugutsuEnum::MaskKaton);
			}
			clone->_isArmored = true;
			_monsterArray.push_back(clone);

			hearts -= 1;
			if (_heartEffect)
			{
				auto frame = getSpriteFrame("Heart_Effect_{:02d}", hearts);
				_heartEffect->setDisplayFrame(frame);
			}

			if (hearts < 1 || countMon >= 2)
			{
				lockSkill4Button();
			}
		}

		return clone;
	}

	/**
	 * Callbacks
	 */

	bool isEnableSkill04() override { return hearts > 1; }

	bool onHit(CharacterBase *attacker) override
	{
		if (_skillChangeBuffValue >= 0)
		{
			if (!attacker->getMaster())
			{
				if (attacker->getState() != State::DEAD)
				{
					attacker->setDamage(this, attacker->getEffectType(), attacker->_attackValue / 2, attacker->_isFlipped);
				}
			}
		}

		return true;
	}
};
