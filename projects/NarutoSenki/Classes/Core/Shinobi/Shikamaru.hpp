#pragma once
#include "Hero.hpp"

class Shikamaru : public Hero
{
	void perform() override
	{
		_mainTarget = nullptr;
		findHeroHalf();

		tryBuyGear(GearType::Gear00, GearType::Gear07, GearType::Gear08);

		if (needBackToTowerToRestoreHP() ||
			needBackToDefendTower())
			return;

		if (_mainTarget && _mainTarget->isNotFlog())
		{
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTarget();

			if (isFreeState())
			{
				if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && _mainTarget->getDEF() < 5000 && !_mainTarget->_isArmored && !_mainTarget->_isSticking)
				{
					changeSide(sp);
					attack(OUGIS2);
					return;
				}
				else if (_isCanSkill2 && _mainTarget->getDEF() < 5000)
				{
					changeSide(sp);
					attack(SKILL2);
					return;
				}
				else if (_isCanOugis1 && !_isControlled && _mainTarget->getDEF() < 5000)
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
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealing && !_isControlled)
				{
					if (abs(sp.x) < 160)
						stepBack2();
					else
						idle();
					return;
				}
				else if (getLV() >= 2 && _isCanSkill1)
				{
					changeSide(sp);
					attack(SKILL1);
					return;
				}
				else if (_isCanSkill3 && _mainTarget->getDEF() < 5000 && !_mainTarget->_isArmored && !_mainTarget->_isSticking)
				{
					if (abs(sp.x) > 156 || abs(sp.y) > 32)
					{
						if (_isCanGear00)
							useGear(GearType::Gear00);

						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					else if (abs(sp.x) < 32)
					{
						stepBack();
						return;
					}

					changeSide(sp);
					attack(SKILL3);
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
				if (_isCanSkill2 && _mainTarget->isFlog() && isBaseDanger)
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

	/**
	 * Callbacks
	 */

	void onSetTrap(const string &trapType) override
	{
		if (trapType == "KageBom")
		{
			for (auto hero : getGameLayer()->_CharacterArray)
			{
				if (getGroup() != hero->getGroup() && hero->isPlayerOrCom() && hero->getState() != State::DEAD && hero->_isVisable && !hero->_isSticking)
				{
					float distanceX = (hero->getPosition() - getPosition()).x;
					float atkRangeX = kAttackRange;
					if (abs(distanceX) <= atkRangeX)
					{
						auto trap = Monster::create();
						trap->setMaster(this);
						trap->setID(trapType, Role::Mon, getGroup());
						trap->setPosition(Vec2(hero->getPositionX(), hero->getPositionY()));
						trap->idle();
						trap->attack(NAttack);
						getGameLayer()->addChild(trap, -trap->getPositionY());
					}
				}
			}
		}
	}
};
