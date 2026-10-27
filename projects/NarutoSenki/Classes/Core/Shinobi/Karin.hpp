#pragma once
#include "Hero.hpp"

class Karin : public Hero
{
	void perform() override
	{
		_mainTarget = nullptr;
		findHeroHalf();

		tryUseGear6();
		tryBuyGear(GearType::Gear06, GearType::Gear01, GearType::Gear07);

		if (needBackToTowerToRestoreHP() ||
			needBackToDefendTower())
			return;

		if (_mainTarget && _mainTarget->isNotFlog())
		{
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTarget();

			if (isFreeState())
			{
				if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && _mainTarget->getDEF() < 5000 && !_mainTarget->_isArmored && _mainTarget->getState() != State::KNOCKDOWN && !_mainTarget->_isSticking)
				{
					if (abs(sp.x) > 96 || abs(sp.y) > 16)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					changeSide(sp);
					attack(OUGIS2);
					return;
				}
				else if (getHpPercent() < 0.9 && _isCanOugis1 && !_isControlled && !_buffStartTime && !_isHealing)
				{
					changeSide(sp);
					attack(OUGIS1);
					return;
				}
				else if (_isCanSkill3 && _mainTarget->getDEF() < 5000)
				{
					if ((abs(sp.x) > 128 || abs(sp.y) > 16))
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}

					changeSide(sp);
					attack(SKILL3);
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
					if (abs(sp.x) > 96 || abs(sp.y) > 32)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					if (_isCanSkill2)
					{
						changeSide(sp);
						attack(SKILL2);
					}
					else if (_isCanSkill1)
					{
						changeSide(sp);
						attack(SKILL1);
					}
					else
					{
						if (abs(sp.x) > 32 || abs(sp.y) > 32)
						{
							moveDirection = sp.getNormalized();
							walk(moveDirection);
							return;
						}
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
				if (_isCanSkill1 && _mainTarget->isFlog())
				{
					changeSide(sp);
					attack(SKILL1);
				}
				else if (_isCanSkill2 && _mainTarget->isFlog() && isBaseDanger)
				{
					changeSide(sp);
					attack(SKILL2);
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

	/**
	 * Callbacks
	 */

	void onSetTrap(const string &trapType) override
	{
		if (trapType == "Kusuri")
		{
			for (int i = 0; i < 3; i++)
			{
				auto trap = Bullet::create();
				trap->setAnchorPoint(Vec2(0.5f, 0));
				trap->setMaster(this);
				trap->setID(trapType, Role::Mon, getGroup());

				if (i == 0)
					trap->setPosition(Vec2(getPositionX() + (_isFlipped ? -24 : 24), getPositionY() - 24));
				else if (i == 1)
					trap->setPosition(Vec2(getPositionX() + (_isFlipped ? 24 : -24), getPositionY() - 24));
				else if (i == 2)
					trap->setPosition(Vec2(getPositionX(), getPositionY() + 24));

				trap->attack(NAttack);
				getGameLayer()->addChild(trap, -trap->getPositionY());
			}
		}
	}
};
