#pragma once
#include "Hero.hpp"

class Ino : public Hero
{
	void dead() override
	{
		CharacterBase::dead();

		// Ino died while her jutsu was active: possession ends immediately
		// and control reverts to Ino's own (now dead) body - the human
		// should see their own death/respawn, not keep piloting whatever
		// they were possessing. Previously this handed currentPlayer to the
		// possessed body instead, effectively letting the player keep
		// playing as if Ino hadn't died at all.
		unschedule(schedule_selector(Ino::resumeAction));

		for (auto hero : getGameLayer()->_CharacterArray)
		{
			if (hero->_isControlled && hero->getController() == this)
			{
				hero->_isControlled = false;
				hero->changeGroup();
				hero->setController(nullptr);

				if (hero->isPlayer())
				{
					hero->unschedule(schedule_selector(CharacterBase::setAI));
					hero->_isAI = false;
					getGameLayer()->getHudLayer()->_isAllButtonLocked = false;
				}
				else
				{
					hero->_isAI = true;
					hero->doAI();
				}
			}
		}

		if (isPlayer())
		{
			// Hand control back to Ino's own body - she is dead, so this
			// puts the human back on their real character's death/respawn
			// flow instead of leaving them stuck on the possessed body.
			getGameLayer()->currentPlayer = this;
			getGameLayer()->controlChar = nullptr;
			getGameLayer()->getHudLayer()->updateSkillButtons();
		}

		_isArmored = false;
	}

	void perform() override
	{
		_mainTarget = nullptr;
		findHeroHalf();

		if (_skillChangeBuffValue)
		{
			return;
		}

		tryUseGear6();
		tryBuyGear(GearType::Gear06, GearType::Gear05, GearType::Gear01);

		if (needBackToTowerToRestoreHP() ||
			needBackToDefendTower())
			return;

		if (getMaxHP() - getHP() >= 3000 &&
			getCoin() >= 50 && !_isHealing && _isCanItem1 && _isArmored)
		{
			setItem(Item1);
		}

		if (_mainTarget && _mainTarget->isNotFlog())
		{
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTarget();

			if (isFreeState())
			{
				if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game)
				{
					if (abs(sp.x) > 96 || abs(sp.y) > 16)
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
				else if (_mainTarget->getDEF() < 5000 && (_isCanSkill3 || _isCanSkill2))
				{
					if (abs(sp.x) > 96 || abs(sp.y) > 16)
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
					else if (_isCanSkill3)
					{
						changeSide(sp);
						attack(SKILL3);
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
					if (abs(sp.x) > 32 || abs(sp.y) > 32)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}

					if (_isCanOugis1 && !_isControlled && _mainTarget->getDEF() < 5000)
					{
						changeSide(sp);
						attack(OUGIS1);
					}
					else if (_isCanSkill1)
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
				if (_mainTarget->isFlog() && _isCanSkill1)
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

	void resumeAction(float dt) override
	{
		if (!_isArmored)
			return;

		for (auto hero : getGameLayer()->_CharacterArray)
		{
			if (hero->_isControlled && hero->getController() == this)
			{
				hero->_isControlled = false;

				if (hero->isPlayer())
				{
					// The possessed body was the human's own player
					// character (AI Ino possessed the player) - give
					// control back to the human instead of leaving them
					// AI-driven and locked out, which was the previous bug.
					hero->_isAI = false;
					hero->unschedule(schedule_selector(CharacterBase::setAI));
					getGameLayer()->getHudLayer()->_isAllButtonLocked = false;
				}
				else
				{
					// Otherwise the possessed body reverts to being an
					// ordinary AI-driven unit again - it was never actually
					// switched back to AI before, which is why it kept
					// fighting under manual control (and on the wrong team)
					// forever.
					hero->_isAI = true;
					hero->doAI();
				}

				if (isPlayer())
				{
					// Restore control to Ino herself: this was previously
					// left commented out, so a player possessing something
					// with Ino would keep piloting the possessed body
					// forever after the timer ran out, with no way back.
					// She must go back to being player-driven (not AI), or
					// perform() keeps ticking alongside human input and the
					// two fight over her.
					_isAI = false;
					unschedule(schedule_selector(CharacterBase::setAI));

					getGameLayer()->currentPlayer = this;
					getGameLayer()->controlChar = nullptr;
					getGameLayer()->getHudLayer()->_isAllButtonLocked = false;
					getGameLayer()->getHudLayer()->updateSkillButtons();
				}

				if (hero->getState() != State::DEAD)
				{
					hero->idle();
				}
				hero->changeGroup();
				hero->setController(nullptr);
			}
		}

		if (_state != State::DEAD)
		{
			idle();
		}

		_isArmored = false;
		CharacterBase::resumeAction(dt);
	}

	void setActionResume() override
	{
		unschedule(schedule_selector(Ino::resumeAction));

		for (auto hero : getGameLayer()->_CharacterArray)
		{
			if (hero->_isControlled && hero->getController() == this)
			{
				hero->_isControlled = false;
				hero->changeGroup();

				if (hero->isPlayer())
				{
					hero->unschedule(schedule_selector(CharacterBase::setAI));
					hero->_isAI = false;
					getGameLayer()->getHudLayer()->_isAllButtonLocked = false;
				}
				else
				{
					hero->_isAI = true;
					hero->doAI();
				}

				if (isPlayer())
				{
					_isAI = false;
					unschedule(schedule_selector(CharacterBase::setAI));

					getGameLayer()->currentPlayer = this;
					getGameLayer()->controlChar = nullptr;
					getGameLayer()->getHudLayer()->_isAllButtonLocked = false;
					getGameLayer()->getHudLayer()->updateSkillButtons();
				}

				hero->setController(nullptr);
			}
		}

		_isArmored = false;
	}
};