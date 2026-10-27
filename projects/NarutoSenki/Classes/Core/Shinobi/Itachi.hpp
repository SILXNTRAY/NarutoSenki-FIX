#pragma once
#include "Hero.hpp"

class Itachi : public Hero
{
	void perform() override
	{
		_mainTarget = nullptr;
		findHeroHalf();

		tryUseGear6();
		tryBuyGear(GearType::Gear06, GearType::Gear02, GearType::Gear05);

		if (needBackToTowerToRestoreHP() ||
			needBackToDefendTower())
			return;

		if (_mainTarget && _mainTarget->isNotFlog())
		{
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTarget();

			if (isFreeState())
			{
				if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && !_isArmored)
				{
					if (abs(sp.x) > 48 || abs(sp.y) > 32)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}

					changeSide(sp);
					attack(OUGIS2);

					return;
				}
				else if (_isCanOugis1 && !_isControlled && _mainTarget->getDEF() < 5000 && !_mainTarget->_isArmored && _mainTarget->getState() != State::KNOCKDOWN && !_mainTarget->_isSticking && !_isArmored)
				{
					changeSide(sp);
					attack(OUGIS1);

					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealing && !_isArmored && !_isControlled)
				{
					if (abs(sp.x) < 160)
						stepBack2();
					else
						idle();
					return;
				}
				else if (abs(sp.x) < 128 || _isArmored)
				{
					if (abs(sp.x) > 196 || abs(sp.y) > 64)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					else if ((abs(sp.x) > 56 || abs(sp.y) > 32) && !_isArmored)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}

					if (_isCanSkill3 && !_isArmored && _mainTarget->getDEF() < 5000)
					{
						changeSide(sp);
						attack(SKILL3);
					}
					else if (_isCanSkill2 && !_isArmored && _mainTarget->getDEF() < 5000)
					{
						changeSide(sp);
						attack(SKILL2);
					}
					else if (_isCanSkill1 && !_isArmored && _mainTarget->getDEF() < 5000)
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
				if (_isCanSkill3 && !_isArmored && _mainTarget->isFlog() && isBaseDanger)
				{
					changeSide(sp);
					attack(SKILL3);
				}
				else if (_isCanSkill2 && !_isArmored && _mainTarget->isFlog() && isBaseDanger)
				{
					changeSide(sp);
					attack(SKILL2);
				}
				else if (_isCanSkill1 && !_isArmored && _mainTarget->isFlog())
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
		setIdleAction(createAnimation(skillSPC1Array, 5, true, false));
		setWalkAction(createAnimation(skillSPC2Array, 10, true, false));
		setNAttackAction(createAnimation(skillSPC3Array, 10, false, true));
		setKnockDownAction(createAnimation(skillSPC4Array, 10, false, true));
		setWalkSpeed(112);
		_originSpeed = 112;

		_isOnlySkillLocked = true;

		setTempAttackValue1(getNAttackValue());
		setNAttackValue(560);

		_nAttackRangeX = 128;
		_nAttackRangeY = 64;

		_defense += 5000;
		_isArmored = true;

		lockOugisButtons();
	}

	void resumeAction(float dt) override
	{
		setIdleAction(createAnimation(idleArray, 5, true, false));
		setWalkAction(createAnimation(walkArray, 10, true, false));
		setNAttackAction(createAnimation(nattackArray, 10, false, true));

		_isOnlySkillLocked = false;

		unlockOugisButtons();

		setWalkSpeed(224);
		_originSpeed = 224;
		if (hasTempAttackValue1())
		{
			setNAttackValue(getTempAttackValue1());
			setTempAttackValue1(0);
		}
		_nAttackRangeX = 16;
		_nAttackRangeY = 48;
		resetDefenseValue(5000);
		_isArmored = false;

		if (_state != State::DEAD)
		{
			_state = State::WALK;
			knockDown();
		}

		setKnockDownAction(createAnimation(knockDownArray, 10, false, true));

		if (hasMonsterArrayAny())
		{
			for (auto mo : _monsterArray)
			{
				CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(mo);
				mo->removeFromParent();
			}
			_monsterArray.clear();
		}
		CharacterBase::resumeAction(dt);
	}

	void setActionResume() override
	{
		if (_skillChangeBuffValue == 17)
		{
			unschedule(schedule_selector(Itachi::resumeAction));

			setIdleAction(createAnimation(idleArray, 5, true, false));
			setWalkAction(createAnimation(walkArray, 10, true, false));
			setNAttackAction(createAnimation(nattackArray, 10, false, true));
			setKnockDownAction(createAnimation(knockDownArray, 10, false, true));

			_isOnlySkillLocked = false;
			unlockOugisButtons();

			setWalkSpeed(224);
			_originSpeed = 224;
			if (hasTempAttackValue1())
			{
				setNAttackValue(getTempAttackValue1());
				setTempAttackValue1(0);
			}
			_nAttackRangeX = 16;
			_nAttackRangeY = 48;
			resetDefenseValue(5000);
			_isArmored = false;

			_skillChangeBuffValue = 0;
		}
	}
};
