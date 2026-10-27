#pragma once
#include "Hero.hpp"
#include "Kuchiyose/Slug.hpp"

class Tsunade : public Hero
{
	void perform() override
	{
		_mainTarget = nullptr;
		findHeroHalf();

		tryBuyGear(GearType::Gear03, GearType::Gear02, GearType::Gear04);

		if (needBackToTowerToRestoreHP() ||
			needBackToDefendTower())
			return;

		if (_mainTarget && _mainTarget->isNotFlog())
		{
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTarget();

			if (isFreeState())
			{
				if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && _mainTarget->getDEF() < 5000 && !_isArmored)
				{
					if (abs(sp.x) > 64 || abs(sp.y) > 16)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					else
					{
						changeSide(sp);
						attack(OUGIS2);
					}
					return;
				}
				else if (_isCanSkill3 && _mainTarget->getDEF() < 5000 && !_isArmored)
				{
					changeSide(sp);
					attack(SKILL3);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealing && !_isControlled && !_isArmored)
				{
					if (abs(sp.x) < 160)
						stepBack2();
					else
						idle();
					return;
				}
				else if (abs(sp.x) < 128)
				{
					if (abs(sp.x) > 64 || abs(sp.y) > 32)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					else if ((abs(sp.x) > 32) || (abs(sp.y) > 32 && !_isCanSkill2 && !_isArmored && !_isCanOugis1))
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					if (_isCanGear03)
					{
						useGear(GearType::Gear03);
					}
					if (_isCanOugis1 && !_isControlled && _mainTarget->getDEF() < 5000 && !_isArmored)
					{
						changeSide(sp);
						attack(OUGIS1);
					}
					else if (_isCanSkill2 && !_isArmored)
					{
						changeSide(sp);
						attack(SKILL2);
						return;
					}
					else if (_isCanSkill1 && !_isArmored)
					{
						changeSide(sp);
						attack(SKILL1);
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
				if (_isCanGear03)
				{
					useGear(GearType::Gear03);
				}
				if (_mainTarget->isFlog() && _isCanSkill1 && !_isArmored && isBaseDanger)
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

		checkHealingState();
	}

	void changeAction() override
	{
		setNAttackValue(getNAttackValue() + 250);
		_isOnlySkillLocked = true;
		_nAttackRangeX = 32;
		_nAttackRangeY = 48;
		_originNAttackType = _nAttackType;
		_nAttackType = _spcAttackType3;

		_isArmored = true;
		_healBuffValue = 3000;
		schedule(schedule_selector(CharacterBase::healBuff), 1);

		setIdleAction(createAnimation(skillSPC1Array, 5, true, false));
		setWalkAction(createAnimation(skillSPC2Array, 10, true, false));
		setNAttackAction(createAnimation(skillSPC3Array, 10, false, true));

		lockOugisButtons();
	}

	void resumeAction(float dt) override
	{
		setNAttackValue(getNAttackValue() - 250);
		_nAttackRangeX = 16;
		_nAttackRangeY = 48;
		_nAttackType = _originNAttackType;

		_isOnlySkillLocked = false;

		unlockOugisButtons();
		_isArmored = false;

		setNAttackAction(createAnimation(nattackArray, 10, false, true));
		setIdleAction(createAnimation(idleArray, 5, true, false));
		setWalkAction(createAnimation(walkArray, 10, true, false));

		if (_state != State::DEAD)
		{
			_state = State::WALK;
			idle();
		}
		CharacterBase::resumeAction(dt);
	}

	Hero *createClone(int cloneTime) override
	{
		auto clone = createSummonHero<Slug>(SummonEnum::Slug);
		clone->_isArmored = true;
		return clone;
	}

private:
	string _originNAttackType;
};
