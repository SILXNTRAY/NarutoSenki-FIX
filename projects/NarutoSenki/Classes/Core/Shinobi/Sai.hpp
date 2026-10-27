#pragma once
#include "Hero.hpp"

class Sai : public Hero
{
	void perform() override
	{
		_mainTarget = nullptr;
		findHeroHalf();

		tryUseGear6();
		tryBuyGear(GearType::Gear06, GearType::Gear05, GearType::Gear01);

		if (needBackToTowerToRestoreHP() ||
			needBackToDefendTower())
			return;

		if (_mainTarget && _mainTarget->isNotFlog())
		{
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTarget();

			if (isFreeState())
			{
				if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && !_isArmored && _mainTarget->getDEF() < 5000 && !_mainTarget->_isArmored && _mainTarget->getState() != State::KNOCKDOWN && !_mainTarget->_isSticking)
				{
					if (abs(sp.x) > 48 || abs(sp.y) > 16)
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
					if (abs(sp.x) > 64 || abs(sp.y) > 16)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					else
					{
						changeSide(sp);
						attack(SKILL3);
					}
					return;
				}
				else if (_isCanSkill2 && _mainTarget->getDEF() < 5000 && !_isArmored)
				{
					changeSide(sp);
					attack(SKILL2);
					return;
				}
				else if (_isCanOugis1 && !_isControlled && _mainTarget->getDEF() < 5000 && !_isArmored)
				{
					changeSide(sp);
					attack(OUGIS1);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealing && !_isControlled)
				{
					if (abs(sp.x) < 160)
					{
						stepBack2();
						return;
					}
					else
					{
						if (_skillChangeBuffValue)
						{
							if (!_isArmored)
							{
								changeSide(sp);
								attack(NAttack);
							}
						}
						idle();
						return;
					}
				}
				else if (_isCanSkill1 && !_isArmored)
				{
					changeSide(sp);
					attack(SKILL1);
					return;
				}
				else if (abs(sp.x) < 128)
				{
					if ((abs(sp.x) > 8 || abs(sp.y) > 8) && _isArmored)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					else if ((abs(sp.x) > 32 || abs(sp.y) > 32) && !_isCanSkill1 && !_skillChangeBuffValue)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}

					if (!_isArmored)
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
				else if (_isCanSkill2 && _mainTarget->getDEF() < 5000 && !_isArmored && _mainTarget->isFlog() && isBaseDanger)
				{
					changeSide(sp);
					attack(SKILL2);
				}
				else if (!_isArmored)
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
		if (_skillChangeBuffValue == 17)
		{
			setNAttackAction(createAnimation(skillSPC1Array, 10, false, true));
		}
		else if (_skillChangeBuffValue == 18)
		{
			_isAllAttackLocked = true;
			_isArmored = true;

			setWalkSpeed(320);
			_originSpeed = 320;

			lockOugisButtons();

			setIdleAction(createAnimation(skillSPC2Array, 5, true, false));
			setWalkAction(createAnimation(skillSPC3Array, 5, true, false));

			if (_hpBar)
			{
				_hpBar->setPositionY(120);
			}
			schedule(schedule_selector(Sai::setMonPer), 0.5f);
		}
	}

	void resumeAction(float dt) override
	{
		if (_skillChangeBuffValue == 17)
		{
			setNAttackAction(createAnimation(nattackArray, 10, false, true));
		}
		else if (_skillChangeBuffValue == 18)
		{
			_isArmored = false;
			_isAllAttackLocked = false;
			setWalkSpeed(224);
			_originSpeed = 224;

			unlockOugisButtons();

			setIdleAction(createAnimation(idleArray, 5, true, false));
			setWalkAction(createAnimation(walkArray, 10, true, false));

			if (_state != State::DEAD)
			{
				_state = State::WALK;
				idle();
			}
			if (_hpBar)
			{
				_hpBar->setPositionY(getHeight());
			}

			unschedule(schedule_selector(Sai::setMonPer));
		}
		CharacterBase::resumeAction(dt);
	}

	void setActionResume() override
	{
		if (_skillChangeBuffValue == 0)
			return;

		unschedule(schedule_selector(Sai::resumeAction));

		if (_skillChangeBuffValue == 17)
		{
			setNAttackAction(createAnimation(nattackArray, 10, false, true));
		}
		else if (_skillChangeBuffValue == 18)
		{
			_isArmored = false;
			_isAllAttackLocked = false;
			setWalkSpeed(224);
			_originSpeed = 224;

			unlockOugisButtons();

			setIdleAction(createAnimation(idleArray, 5, true, false));
			setWalkAction(createAnimation(walkArray, 10, true, false));

			if (_hpBar)
			{
				_hpBar->setPositionY(getHeight());
			}
			unschedule(schedule_selector(Sai::setMonPer));
		}

		_skillChangeBuffValue = 0;
	}
};
