#pragma once
#include "Hero.hpp"

class Sasuke : public Hero
{
	void setID(const string &name, Role role, Group group) override
	{
		Hero::setID(name, role, group);

		match_char_exp(HeroEnum::Sasuke, setAIHandler(Sasuke::perform),
					   HeroEnum::ImmortalSasuke, setAIHandler(Sasuke::perform_SasukeImmortal));
	}

	void changeAction() override
	{
		match_char_exp(HeroEnum::Sasuke, changeAction_Sasuke(),
					   HeroEnum::ImmortalSasuke, changeAction_SasukeImmortal());
	}

	void resumeAction(float dt) override
	{
		match_char_exp(HeroEnum::Sasuke, resumeAction_Sasuke(dt),
					   HeroEnum::ImmortalSasuke, resumeAction_SasukeImmortal(dt));
	}

	void setActionResume() override
	{
		match_char_exp(HeroEnum::Sasuke, setActionResume_Sasuke(),
					   HeroEnum::ImmortalSasuke, setActionResume_SasukeImmortal());
	}

	// Sasuke

	void perform() override
	{
		_mainTarget = nullptr;
		findHeroHalf();

		tryUseGear6();
		tryBuyGear(GearType::Gear06, GearType::Gear01, GearType::Gear02);

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
					changeSide(sp);
					attack(OUGIS2);
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
				else if (_isCanSkill3 && !_isTaunt && !_isArmored)
				{
					changeSide(sp);
					attack(SKILL3);
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
					else if ((abs(sp.x) > 32 || abs(sp.y) > 32) && !_isCanSkill1 && !_isCanSkill2)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}

					if (_isCanOugis1 && !_isControlled && _mainTarget->getDEF() < 5000 && !_isArmored)
					{
						if (abs(sp.x) > 32 || abs(sp.y) > 32)
						{
							moveDirection = sp.getNormalized();
							walk(moveDirection);
							return;
						}
						changeSide(sp);
						attack(OUGIS1);
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
				if (_isCanSkill1 && !_isArmored && _mainTarget->isFlog())
				{
					changeSide(sp);
					attack(SKILL1);
				}
				else if (_isCanSkill2 && isBaseDanger && !_isArmored && _mainTarget->isFlog())
				{
					changeSide(sp);
					attack(SKILL2);
				}
				else if (_isCanSkill3 && !_isArmored && _mainTarget->isFlog())
				{
					changeSide(sp);
					attack(SKILL3);
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

	inline void changeAction_Sasuke()
	{
		if (_skillChangeBuffValue == 17)
		{
			_isTaunt = true;
			setHurtAction(createAnimation(skillSPC5Array, 10, false, true));

			for (auto hero : getGameLayer()->_CharacterArray)
			{
				if (getGroup() != hero->getGroup() &&
					hero->isPlayerOrCom() &&
					hero->getState() != State::HURT &&
					hero->getState() != State::DEAD)
				{
					float distanceX = (hero->getPosition() - getPosition()).x;
					if (distanceX < kAttackRange)
					{
						if (!hero->_isVisable)
						{
							if (hero->getName() == HeroEnum::Konan ||
								hero->getName() == HeroEnum::Deidara)
							{
								hero->unschedule(schedule_selector(CharacterBase::disableBuff));
							}

							hero->setOpacity(255);
							hero->setVisible(true);

							if (hero->_hpBar)
								hero->_hpBar->setVisible(true);
							if (hero->_shadow)
								hero->_shadow->setVisible(true);

							hero->_isVisable = true;
						}
					}
				}
			}
		}
		else if (_skillChangeBuffValue == 18)
		{
			setIdleAction(createAnimation(skillSPC1Array, 5, true, false));
			setWalkAction(createAnimation(skillSPC2Array, 10, true, false));
			setNAttackAction(createAnimation(skillSPC3Array, 10, false, true));
			setKnockDownAction(createAnimation(skillSPC4Array, 10, false, true));

			setWalkSpeed(320);
			_originSpeed = 320;

			_isOnlySkillLocked = true;
			setTempAttackValue1(getNAttackValue());
			setNAttackValue(560);

			_nAttackRangeX = _spcAttackRangeX3;
			_nAttackRangeY = _spcAttackRangeY3;
			_originNAttackType = _nAttackType;
			_nAttackType = _spcAttackType3;

			_defense += 5000;
			_isArmored = true;

			lockOugisButtons();
		}
	}

	inline void resumeAction_Sasuke(float dt)
	{
		if (_isTaunt)
		{
			_isTaunt = false;
			setHurtAction(createAnimation(hurtArray, 10, false, true));
		}
		else if (_skillChangeBuffValue == 18)
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
			_nAttackType = _originNAttackType;
			resetDefenseValue(5000);
			_isArmored = false;

			if (_state != State::DEAD)
			{
				_state = State::WALK;
				knockDown();
			}

			setKnockDownAction(createAnimation(knockDownArray, 10, false, true));
		}
		CharacterBase::resumeAction(dt);
	}

	inline void setActionResume_Sasuke()
	{
		if (_isTaunt)
		{
			unschedule(schedule_selector(Sasuke::resumeAction_Sasuke));
			_isTaunt = false;
			setHurtAction(createAnimation(hurtArray, 10, false, true));
			_skillChangeBuffValue = 0;
		}
	}

	// Sasuke Immortal

	void perform_SasukeImmortal()
	{
		_mainTarget = nullptr;
		findHeroHalf();

		tryUseGear6();
		tryBuyGear(GearType::Gear06, GearType::Gear01, GearType::Gear02);

		if (needBackToTowerToRestoreHP() ||
			needBackToDefendTower())
			return;

		if (_mainTarget && _mainTarget->isNotFlog())
		{
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTarget();

			if (isFreeState())
			{
				if (_isCanOugis1 && !_isControlled && _mainTarget->getDEF() < 5000 && !_isArmored)
				{
					changeSide(sp);
					attack(OUGIS1);
					return;
				}
				else if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && !_isArmored)
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
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealing && !_isArmored && !_isControlled)
				{
					if (abs(sp.x) < 160)
						stepBack2();
					else
						idle();
					return;
				}
				else if (_isCanSkill3 && !_isArmored && !_isTaunt)
				{
					changeSide(sp);
					attack(SKILL3);
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
					else if ((abs(sp.x) > 96 || abs(sp.y) > 32) && !_isArmored)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					else if ((abs(sp.x) > 32 || abs(sp.y) > 32) && !_isCanSkill1 && !_isCanSkill2)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}

					if (_isCanSkill2 && !_isArmored && _mainTarget->getDEF() < 5000)
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
				if (_isCanSkill1 && !_isArmored && _mainTarget->isFlog())
				{
					changeSide(sp);
					attack(SKILL1);
				}
				else if (_isCanSkill2 && isBaseDanger && !_isArmored && _mainTarget->isFlog())
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

	inline void changeAction_SasukeImmortal()
	{
		if (_skillChangeBuffValue == 17)
		{
			_isTaunt = true;
			setHurtAction(createAnimation(skillSPC1Array, 10, false, true));

			for (auto hero : getGameLayer()->_CharacterArray)
			{
				if (getGroup() != hero->getGroup() &&
					hero->isPlayerOrCom() &&
					hero->getState() != State::HURT &&
					hero->getState() != State::DEAD)
				{
					float distanceX = (hero->getPosition() - getPosition()).x;
					if (distanceX < kAttackRange)
					{
						if (!hero->_isVisable)
						{
							if (hero->getName() == HeroEnum::Konan ||
								hero->getName() == HeroEnum::Deidara)
							{
								hero->unschedule(schedule_selector(CharacterBase::disableBuff));
							}

							hero->setOpacity(255);
							hero->setVisible(true);

							if (hero->_hpBar)
								hero->_hpBar->setVisible(true);
							if (hero->_shadow)
								hero->_shadow->setVisible(true);

							hero->_isVisable = true;
						}
					}
				}
			}
		}
		else if (_skillChangeBuffValue == 18)
		{
			setIdleAction(createAnimation(skillSPC4Array, 5, true, false));
			setWalkAction(createAnimation(skillSPC3Array, 10, true, false));
			setNAttackAction(createAnimation(skillSPC2Array, 10, false, true));
			setWalkSpeed(112);
			_originSpeed = 112;

			setTempAttackValue1(getNAttackValue());
			setNAttackValue(1160);

			_nAttackRangeX = 156;
			_nAttackRangeY = 64;

			_defense += 5000;
			_isArmored = true;
			_isOnlySkillLocked = true;

			lockOugisButtons();
		}
	}

	inline void resumeAction_SasukeImmortal(float dt)
	{
		if (_isTaunt)
		{
			_isTaunt = false;
			setHurtAction(createAnimation(hurtArray, 10, false, true));
		}
		else if (_skillChangeBuffValue == 18)
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
			resetDefenseValue(5000);
			_isArmored = false;

			_nAttackRangeX = 16;
			_nAttackRangeY = 48;

			if (hasMonsterArrayAny())
			{
				for (auto mo : _monsterArray)
				{
					CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(mo);
					mo->removeFromParent();
				}
				_monsterArray.clear();
			}

			if (_state != State::DEAD)
			{
				_state = State::WALK;
				idle();
			}
		}
		CharacterBase::resumeAction(dt);
	}

	inline void setActionResume_SasukeImmortal()
	{
		if (_isTaunt)
		{
			unschedule(schedule_selector(Sasuke::resumeAction_SasukeImmortal));
			_isTaunt = false;
			setHurtAction(createAnimation(hurtArray, 10, false, true));
			_skillChangeBuffValue = 0;
		}
		else if (_skillChangeBuffValue && _skillChangeBuffValue == 18)
		{
			unschedule(schedule_selector(Sasuke::resumeAction_SasukeImmortal));

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
			resetDefenseValue(5000);
			_isArmored = false;

			_nAttackRangeX = 16;
			_nAttackRangeY = 48;

			_skillChangeBuffValue = 0;
		}
	}

private:
	string _originNAttackType;
};
