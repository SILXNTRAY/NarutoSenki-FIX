#pragma once
#include "Hero.hpp"

class Hidan : public Hero
{
	void perform() override
	{
		_mainTarget = nullptr;
		bool _isFound = false;

		if (hasMonsterArrayAny())
		{
			for (auto mo : _monsterArray)
			{
				if (mo->getName() == "CircleMark")
				{
					_mainTarget = mo;
					_isFound = true;
					Vec2 moveDirection;
					Vec2 sp;

					if (_mainTarget->_originY)
					{
						sp = Vec2(_mainTarget->getPositionX(), _mainTarget->_originY) - getPosition();
					}
					else
					{
						sp = _mainTarget->getPosition() - getPosition();
					}
					if ((abs(sp.x) > 8 || abs(sp.y) > 8))
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					else
					{
						if (_isArmored)
						{
							for (auto hero : getGameLayer()->_CharacterArray)
							{
								if (hero->getGroup() != getGroup() && hero->getHP() < 2000 && hero->getState() != State::DEAD && hero->isPlayerOrCom())
								{
									attack(NAttack);
									return;
								}
							}

							idle();
							return;
						}
					}
				}
			}
		}

		if (!_isFound)
			findHeroHalf();

		tryUseGear6();
		tryBuyGear(GearType::Gear06, GearType::Gear01, GearType::Gear07);

		bool needBack = !_isArmored && !_isFound;
		if (needBackToTowerToRestoreHP(needBack) ||
			needBackToDefendTower(needBack))
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
					if (_isCanSkill1 && !_isArmored && !_isFound)
					{
						changeSide(sp);
						attack(SKILL1);
						return;
					}
					changeSide(sp);
					attack(OUGIS2);
					return;
				}
				else if (_isCanSkill2 && _mainTarget->getDEF() < 5000 && !_isArmored)
				{
					if (abs(sp.x) > 56 || abs(sp.y) > 32)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}

					changeSide(sp);
					attack(SKILL2);
					return;
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealing && !_isControlled && !_isArmored && !_isFound)
				{
					if (abs(sp.x) < 160)
						stepBack2();
					else
						idle();
					return;
				}
				else if (abs(sp.x) < 128)
				{
					if ((abs(sp.x) > 48 || abs(sp.y) > 32) && !_isArmored)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					if (_isCanOugis1 && !_isArmored && !_isControlled && _mainTarget->getDEF() < 5000)
					{
						changeSide(sp);
						attack(OUGIS1);
					}
					else if (_isCanSkill3 && !_isArmored)
					{
						changeSide(sp);
						attack(SKILL3);
					}
					else
					{
						if (!_isArmored)
						{
							changeSide(sp);
							attack(NAttack);
						}
						else
						{
							idle();
						}
					}

					return;
				}
			}
		}

		if (!_mainTarget && !_isFound && !_isArmored)
		{
			if (notFindFlogHalf())
			{
				findTowerHalf();
			}
		}

		if (_mainTarget && _mainTarget->isNotMon() && !_isArmored)
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
				if (_isCanSkill3 && _mainTarget->isFlog() && isBaseDanger && !_isArmored)
				{
					changeSide(sp);
					attack(SKILL3);
				}
				else if (_isCanSkill2 && _mainTarget->isFlog() && isBaseDanger && !_isArmored)
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

		if (!_isArmored)
			checkHealingState();
		else if (isFreeState())
			idle();
	}

	void changeAction() override
	{
		_isArmored = true;
		_isTaunt = true;
		_isOnlySkillLocked = true;
		setIdleAction(createAnimation(skillSPC1Array, 5, true, false));
		setWalkAction(createAnimation(skillSPC2Array, 10, true, false));
		setNAttackAction(createAnimation(skillSPC3Array, 10, false, true));

		lockOugisButtons();
	}

	void resumeAction(float dt) override
	{
		_isArmored = false;
		_isTaunt = false;
		_isOnlySkillLocked = false;
		unlockOugisButtons();

		setNAttackAction(createAnimation(nattackArray, 10, false, true));
		setIdleAction(createAnimation(idleArray, 5, true, false));
		setWalkAction(createAnimation(walkArray, 10, true, false));

		if (hasMonsterArrayAny())
		{
			for (auto mo : _monsterArray)
			{
				std::erase(getGameLayer()->_CharacterArray, mo);

				CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(mo);
				mo->setState(State::DEAD);
				mo->removeFromParent();
			}
			_monsterArray.clear();
		}

		if (isPlayer())
		{
			getGameLayer()->getHudLayer()->skill1Button->unLock();
		}

		if (_state != State::DEAD)
		{
			_state = State::WALK;
			idle();
		}
		CharacterBase::resumeAction(dt);
	}

	void setActionResume() override
	{
		unschedule(schedule_selector(Hidan::resumeAction));

		resumeAction(0);
	}

	void dealloc() override
	{
		Hero::dealloc();

		if (isPlayer())
			getGameLayer()->getHudLayer()->skill1Button->unLock();
	}

	/**
	 * Callbacks
	 */

	bool onHit(CharacterBase *attacker) override
	{
		if (_skillChangeBuffValue <= 0)
			return true;

		bool _isCounter = false;
		if (hasMonsterArrayAny())
		{
			for (auto mo : _monsterArray)
			{
				float distanceX = (mo->getPosition() - getPosition()).x;
				float distanceY = (mo->getPosition() - getPosition()).y;
				if (abs(distanceX) < 40 && abs(distanceY) < 15)
				{
					_isCounter = true;
				}
			}
		}

		if (_isCounter && attacker->isNotGuardian())
		{
			if (attacker->getMaster() && attacker->getMaster()->getState() != State::DEAD)
			{
				attacker->getMaster()->setDamage(this, attacker->getEffectType(), attacker->_attackValue, attacker->_isFlipped);
			}
			else if (!attacker->getMaster())
			{
				if (attacker->getState() != State::DEAD)
				{
					attacker->setDamage(this, attacker->getEffectType(), attacker->_attackValue, attacker->_isFlipped);
				}
			}

			for (auto hero : getGameLayer()->_CharacterArray)
			{
				if (getGroup() != hero->getGroup() && hero->isPlayerOrCom() && hero->getState() != State::DEAD)
				{
					hero->setDamage(this, attacker->getEffectType(), attacker->_attackValue / 2, attacker->_isFlipped);
				}
			}

			return false;
		}

		return true;
	}

	bool onBulletHit(CharacterBase *attacker) override
	{
		if (_skillChangeBuffValue <= 0)
			return true;

		bool _isCounter = false;
		if (hasMonsterArrayAny())
		{
			for (auto mo : _monsterArray)
			{
				float distanceX = (mo->getPosition() - getPosition()).x;
				float distanceY = (mo->getPosition() - getPosition()).y;
				if (abs(distanceX) < 40 && abs(distanceY) < 15)
				{
					_isCounter = true;
				}
			}
		}

		if (_isCounter)
		{
			if (attacker->getMaster() && attacker->getMaster()->getState() != State::DEAD)
			{
				attacker->getMaster()->setDamage(this, attacker->getEffectType(), attacker->_attackValue, attacker->_isFlipped);
			}

			for (auto hero : getGameLayer()->_CharacterArray)
			{
				if (getGroup() != hero->getGroup() && hero->isPlayerOrCom() && hero->getState() != State::DEAD)
				{
					hero->setDamage(this, attacker->getEffectType(), attacker->_attackValue / 2, attacker->_isFlipped);
				}
			}

			return false;
		}

		return true;
	}
};
