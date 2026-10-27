#pragma once
#include "Hero.hpp"

class Choji : public Hero
{
	void perform() override
	{
		_mainTarget = nullptr;
		findHeroHalf();

		tryUseGear6();
		tryBuyGear(GearType::Gear06, GearType::Gear01, GearType::Gear04);

		if (needBackToTowerToRestoreHP() ||
			needBackToDefendTower())
			return;

		if (_mainTarget && _mainTarget->isNotFlog())
		{
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTarget();

			if (isFreeState())
			{
				if (_isCanSkill1 && !_isArmored)
				{
					changeSide(sp);
					attack(SKILL1);
					return;
				}
				else if (_isCanSkill3 && _mainTarget->getDEF() < 5000 && !_isArmored)
				{
					if (abs(sp.x) > 96 || abs(sp.y) > 16)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
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
					if (abs(sp.x) > 32 || abs(sp.y) > 32)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}

					if (_isCanOugis1 && !_isControlled && _mainTarget->getDEF() < 5000 && !_isArmored)
					{
						changeSide(sp);
						attack(OUGIS1);
					}
					else if (_isCanSkill2 && _mainTarget->getDEF() < 5000 && !_isArmored && _skillUPBuffValue)
					{
						changeSide(sp);
						attack(SKILL2);
					}
					else if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && _mainTarget->getDEF() < 5000 && !_isArmored)
					{
						changeSide(sp);
						attack(OUGIS2);
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

		if (battleCondiction >= 0)
		{
			_mainTarget = nullptr;
			if (notFindFlogHalf())
			{
				findTowerHalf();
			}
		}
		else
		{
			_mainTarget = nullptr;
			findTowerHalf();
		}

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
				if (_isCanSkill2 && !_isArmored && _mainTarget->isFlog())
				{
					changeSide(sp);
					attack(SKILL2);
				}
				else if (_isCanOugis1 && !_isControlled && isBaseDanger && !_isArmored && _mainTarget->isFlog())
				{
					changeSide(sp);
					attack(OUGIS1);
				}
				else if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && _mainTarget->isTower() && !_isArmored)
				{
					changeSide(sp);
					attack(OUGIS2);
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
		_isArmored = true;
		setNAttackAction(createAnimation(skillSPC3Array, 10, false, true));
		setIdleAction(createAnimation(skillSPC4Array, 5, true, false));
		setWalkAction(createAnimation(skillSPC2Array, 5, true, false));

		_originNAttackType = _nAttackType;
		_nAttackType = _spcAttackType3;

		setNAttackValue(getNAttackValue() + 460);
		_nAttackRangeX = 32;
		_nAttackRangeY = 48;
		_isOnlySkillLocked = true;

		lockOugisButtons();
		_defense += 5000;

		if (_hpBar)
		{
			_hpBar->setPositionY(108);
		}
	}

	void resumeAction(float dt) override
	{
		setNAttackValue(getNAttackValue() - 460);
		_nAttackRangeX = 16;
		_nAttackRangeY = 48;
		_nAttackType = _originNAttackType;

		_isOnlySkillLocked = false;
		_isArmored = false;
		resetDefenseValue(5000);

		setWalkAction(createAnimation(walkArray, 10, true, false));
		setIdleAction(createAnimation(idleArray, 5, true, false));
		setNAttackAction(createAnimation(nattackArray, 10, false, true));

		if (_state != State::DEAD)
		{
			_state = State::WALK;
			idle();
		}

		unlockOugisButtons();

		if (_hpBar)
		{
			_hpBar->setPositionY(getHeight());
		}
		CharacterBase::resumeAction(dt);
	}

	void setActionResume() override
	{
		unschedule(schedule_selector(Choji::resumeAction));

		setNAttackValue(getNAttackValue() - 460);
		_nAttackRangeX = 16;
		_nAttackRangeY = 48;

		_isOnlySkillLocked = false;
		_isArmored = false;
		resetDefenseValue(5000);

		setWalkAction(createAnimation(walkArray, 10, true, false));
		setIdleAction(createAnimation(idleArray, 5, true, false));
		setNAttackAction(createAnimation(nattackArray, 10, false, true));

		unlockOugisButtons();

		if (_hpBar)
		{
			_hpBar->setPositionY(getHeight());
		}

		_skillChangeBuffValue = 0;
	}

	void dealloc() override
	{
		Hero::dealloc();

		// TODO: Only remove the blood loss buff caused by this hero's attack
		for (auto hero : getGameLayer()->_CharacterArray)
		{
			if (hero->_isSticking)
			{
				if (hero->getState() != State::DEAD)
				{
					hero->removeLostBlood(0.1f);
					hero->idle();
				}
			}
		}
	}

private:
	string _originNAttackType;
};
