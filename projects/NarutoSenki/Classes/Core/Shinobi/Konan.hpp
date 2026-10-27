#pragma once
#include "Hero.hpp"

class Konan : public Hero
{
	void perform() override
	{
		_mainTarget = nullptr;
		findHeroHalf();

		tryBuyGear(GearType::Gear03, GearType::Gear05, GearType::Gear02);

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
				else if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && _mainTarget->getDEF() < 5000 && !_mainTarget->_isArmored && _mainTarget->getState() != State::KNOCKDOWN && !_mainTarget->_isSticking && !_isArmored)
				{
					if ((abs(sp.x) > 48 || abs(sp.y) > 16))
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}

					changeSide(sp);
					attack(OUGIS2);
					return;
				}
				else if (_mainTarget->getDEF() < 5000 && !_isVisable && !_isArmored && (_isCanSkill3 || _isCanSkill2) &&
						 _mainTarget->getState() != State::KNOCKDOWN)
				{
					if ((abs(sp.x) > 128 || abs(sp.y) > 16))
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					else if (abs(sp.x) < 96)
					{
						stepBack();
						return;
					}

					if (_isCanSkill3)
					{
						changeSide(sp);
						attack(SKILL3);
					}
					else if (_isCanSkill2)
					{
						changeSide(sp);
						attack(SKILL2);
					}

					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealing && !_isControlled)
				{
					if (abs(sp.x) < 160)
						stepBack2();
					else
						idle();
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
					else if ((abs(sp.x) > 48 || abs(sp.y) > 32))
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					else if (abs(sp.x) < 32 && !_isArmored)
					{
						stepBack();
						return;
					}

					if (_isCanOugis1 && !_isControlled && _mainTarget->getDEF() < 5000 && !_isArmored)
					{
						changeSide(sp);
						attack(OUGIS1);
					}
					else if (_isCanSkill2 && !_isArmored && _mainTarget->getDEF() < 5000)
					{
						changeSide(sp);
						attack(SKILL2);
					}
					else
					{
						if (_isCanGear03)
						{
							useGear(GearType::Gear03);
						}
						if (!_isArmored)
						{
							changeSide(sp);
							attack(NAttack);
						}
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

			if ((abs(sp.x) > 8 || abs(sp.y) > 8) && _isArmored)
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
				if (_isCanGear03)
				{
					useGear(GearType::Gear03);
				}
				if (_isCanOugis1 && !_isControlled && !_isArmored && _mainTarget->isFlog() && isBaseDanger)
				{
					changeSide(sp);
					attack(OUGIS1);
				}
				else if (_isCanSkill2 && !_isArmored && _mainTarget->isFlog() && isBaseDanger)
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
		_isAllAttackLocked = true;
		_isArmored = true;

		_attackType = _spcAttackType2;
		_attackValue = getSpcAttackValue2();
		_attackRangeX = _spcAttackRangeX2;
		_attackRangeY = _spcAttackRangeY2;

		setWalkSpeed(320);
		_originSpeed = 320;

		setIdleAction(createAnimation(skillSPC1Array, 5, true, false));
		setWalkAction(createAnimation(skillSPC2Array, 10, true, false));
		if (_hpBar)
		{
			_hpBar->setPositionY(90);
		}
		lockOugisButtons();
	}

	void resumeAction(float dt) override
	{
		_isAllAttackLocked = false;
		_isArmored = false;
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
		CharacterBase::resumeAction(dt);
	}
};
