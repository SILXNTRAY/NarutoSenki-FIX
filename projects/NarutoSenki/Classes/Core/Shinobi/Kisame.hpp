#pragma once
#include "Hero.hpp"

class Kisame : public Hero
{
	void perform() override
	{
		_mainTarget = nullptr;
		findHeroHalf();

		tryBuyGear(GearType::Gear00, GearType::Gear01, GearType::Gear05);

		if (needBackToTowerToRestoreHP() ||
			needBackToDefendTower())
			return;

		if (_mainTarget && _mainTarget->isNotFlog())
		{
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTarget();

			if ((isFreeState()) && (abs(sp.x) < 128 || _isCanGear00))
			{
				if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && _mainTarget->getDEF() < 5000 && !_mainTarget->_isArmored && _mainTarget->getState() != State::KNOCKDOWN && !_mainTarget->_isSticking && !_skillChangeBuffValue)
				{
					if (abs(sp.x) > 48 || abs(sp.y) > 32)
					{
						if (_isCanGear00)
							useGear(GearType::Gear00);

						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}

					changeSide(sp);
					attack(OUGIS2);
					return;
				}
				else if (_isCanOugis1 && !_isControlled && _mainTarget->getDEF() < 5000 && !_skillChangeBuffValue)
				{
					if (abs(sp.x) > 48 || abs(sp.y) > 32)
					{
						if (_isCanGear00)
							useGear(GearType::Gear00);

						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}

					changeSide(sp);
					attack(OUGIS1);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealing && !_isControlled && !_skillChangeBuffValue)
				{
					if (abs(sp.x) < 160)
						stepBack2();
					else
						idle();
					return;
				}
				else if (_isCanSkill3 && !_skillChangeBuffValue)
				{
					if (abs(sp.x) > 96 || abs(sp.y) > 32)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					changeSide(sp);
					attack(SKILL3);
					return;
				}
				else if (_isCanSkill2 && _mainTarget->getDEF() < 5000 && !_skillChangeBuffValue)
				{
					if (abs(sp.x) > 96 || abs(sp.y) > 32)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}

					changeSide(sp);
					attack(SKILL2);
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

					if (_isCanSkill1 && _mainTarget->getDEF() < 5000 && !_skillChangeBuffValue)
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
				if (_isCanSkill2 && _mainTarget->isFlog() && isBaseDanger)
				{
					changeSide(sp);
					attack(SKILL2);
				}
				else if (_isCanSkill1 && _mainTarget->isFlog())
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
		setTempAttackValue1(getNAttackValue());
		setNAttackValue(660);

		_isOnlySkillLocked = true;

		_nAttackRangeX = 32;
		_nAttackRangeY = 48;

		setIdleAction(createAnimation(skillSPC1Array, 5, true, false));
		setWalkAction(createAnimation(skillSPC2Array, 10, true, false));
		setNAttackAction(createAnimation(skillSPC3Array, 10, false, true));

		setWalkSpeed(112);
		_originSpeed = 112;

		lockOugisButtons();
	}

	void setActionResume() override
	{
		if (_skillChangeBuffValue == 0)
			return;

		if (hasTempAttackValue1())
		{
			setNAttackValue(getTempAttackValue1());
			setTempAttackValue1(0);
		}
		_isOnlySkillLocked = false;
		unlockOugisButtons();

		_nAttackRangeX = 16;
		_nAttackRangeY = 48;

		setIdleAction(createAnimation(idleArray, 5, true, false));
		setWalkAction(createAnimation(walkArray, 10, true, false));
		setNAttackAction(createAnimation(nattackArray, 10, false, true));

		_skillChangeBuffValue = 0;

		setWalkSpeed(224);
		_originSpeed = 224;
	}
};
