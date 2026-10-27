#pragma once
#include "Hero.hpp"

class Gaara : public Hero
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
				if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && !_isArmored && _mainTarget->getDEF() < 5000)
				{
					changeSide(sp);
					attack(OUGIS2);
					return;
				}
				else if (_isCanOugis1 && !_isControlled && _mainTarget->getDEF() < 5000 && !_isArmored)
				{
					changeSide(sp);
					attack(OUGIS1);
					return;
				}
				else if (_isCanSkill3 && _mainTarget->getDEF() < 5000 && !_isArmored)
				{
					changeSide(sp);
					attack(SKILL3);
					return;
				}
				else if (_isCanSkill2 && _mainTarget->getDEF() < 5000 && !_isArmored)
				{
					changeSide(sp);
					attack(SKILL2);
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

					if (_isCanSkill1 && !_isArmored)
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
				if (_mainTarget->isFlog() && _isCanSkill1 && !_isArmored)
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

		_isOnlySkillLocked = true;

		_defense += 5000;
		_isArmored = true;

		lockOugisButtons();

		if (_hpBar)
		{
			_hpBar->setPositionY(134);
		}
	}

	void resumeAction(float dt) override
	{
		setIdleAction(createAnimation(idleArray, 5, true, false));
		setWalkAction(createAnimation(walkArray, 10, true, false));
		setNAttackAction(createAnimation(nattackArray, 10, false, true));

		_isOnlySkillLocked = false;

		unlockOugisButtons();
		resetDefenseValue(5000);
		_isArmored = false;

		if (_state != State::DEAD)
		{
			_state = State::WALK;
			idle();
		}

		if (_hpBar)
		{
			_hpBar->setPositionY(getHeight());
		}
		CharacterBase::resumeAction(dt);
	}

	void setActionResume() override
	{
		if (_skillChangeBuffValue == 0)
			return;

		unschedule(schedule_selector(Gaara::resumeAction));
		setIdleAction(createAnimation(idleArray, 5, true, false));
		setWalkAction(createAnimation(walkArray, 10, true, false));
		setNAttackAction(createAnimation(nattackArray, 10, false, true));

		_isOnlySkillLocked = false;

		unlockOugisButtons();
		resetDefenseValue(5000);
		_isArmored = false;
		_skillChangeBuffValue = 0;

		if (_hpBar)
		{
			_hpBar->setPositionY(getHeight());
		}
	}
};
