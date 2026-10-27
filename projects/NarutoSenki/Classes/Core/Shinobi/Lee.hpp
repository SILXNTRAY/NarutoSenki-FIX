#pragma once
#include "Hero.hpp"

class Lee : public Hero
{
	static const uint8_t kMax_Lee_HachimonTonkouLevel = 5;

	// Hachimon tonkou level
	uint8_t htLv = 0;

	void setID(const string &name, Role role, Group group) override
	{
		Hero::setID(name, role, group);

		match_char_exp(HeroEnum::Lee, setAIHandler(Lee::perform),
					   HeroEnum::RockLee, setAIHandler(Lee::perform_RockLee));

		// NOTE: Because Lee can transform to RockLee
		if (getGameLayer()->isHUDInit())
			tryLockSkillButton();
		else
			getGameLayer()->onHUDInitialized(BIND(Lee::tryLockSkillButton));
	}

	void dead() override
	{
		CharacterBase::dead();

		if (htLv > 0)
		{
			if (htLv == 5)
			{
				setWalkSpeed(224);
				_originSpeed = 224;
				setWalkAction(createAnimation(walkArray, 10, true, false));
				setNAttackValue(getNAttackValue() - 60);
				setSAttackValue2(getSAttackValue2() - 100);
				setSAttackValue3(getSAttackValue3() - 100);
			}
			else if (htLv == 4)
			{
				setSAttackValue2(getSAttackValue2() - 100);
				setSAttackValue3(getSAttackValue3() - 100);
			}
			else if (htLv == 3)
			{
				setTransform();

				if (isPlayer())
				{
					getGameLayer()->getHudLayer()->skill3Button->setLock();
				}

				if (_skillBuffEffect)
				{
					_skillBuffEffect->removeFromParent();
					_skillBuffEffect = nullptr;
				}
			}
			else if (htLv == 2)
			{
				setSAttackValue2(getSAttackValue2() - 100);
			}
			else if (htLv == 1)
			{
				lockSkill4Button();
				setNAttackValue(getNAttackValue() - 30);
			}
			htLv--;

			if (htLv == 0)
			{
				_heartEffect->removeFromParent();
				_heartEffect = nullptr;
			}
			else
			{
				auto frame = getSpriteFrame("Bamen_Effect_{:02d}", htLv - 1);
				_heartEffect->setDisplayFrame(frame);
			}
		}
	}

	void changeHPbar() override
	{
		Hero::changeHPbar();

		if (isNotPlayer())
			return;

		if (getName() == HeroEnum::Lee)
		{
			// NOTE: See `Kakuzu::changeHPbar()`
			if (_exp >= 500 && _level == 1 + 1)
			{
				if (htLv < 1)
					getGameLayer()->getHudLayer()->skill4Button->setLock();
			}
			else if (_exp >= 1500 && _level == 3 + 1)
			{
				if (htLv < 3)
					getGameLayer()->getHudLayer()->skill5Button->setLock();
			}
		}
	}

	void changeAction() override
	{
		if (htLv == 0 && !_heartEffect)
		{
			_heartEffect = Sprite::createWithSpriteFrameName("Bamen_Effect_00");
			_heartEffect->setPosition(Vec2(getContentSize().width + 40, 60));
			addChild(_heartEffect);
		}

		if (htLv < kMax_Lee_HachimonTonkouLevel)
		{
			htLv++;
			auto frame = getSpriteFrame("Bamen_Effect_{:02d}", htLv - 1);
			_heartEffect->setDisplayFrame(frame);
		}
		else
		{
			return;
		}

		if (htLv == 1)
		{
			setNAttackValue(getNAttackValue() + 30);

			unlockSkill4Button();
		}
		else if (htLv == 2)
		{
			setSAttackValue2(getSAttackValue2() + 100);
		}
		else if (htLv == 3)
		{
			if (!_skillBuffEffect)
			{
				setBuffEffect("bmBuff");
			}
			setTransform();

			if (isPlayer())
			{
				getGameLayer()->getHudLayer()->skill3Button->unLock();
				getGameLayer()->getHudLayer()->skill5Button->unLock();
			}
		}
		else if (htLv == 4)
		{
			setSAttackValue2(getSAttackValue2() + 100);
			setSAttackValue3(getSAttackValue3() + 100);
		}
		else if (htLv == 5)
		{
			setWalkAction(createAnimation(skillSPC1Array, 10, true, false));
			setWalkSpeed(320);
			_originSpeed = 320;
			setNAttackValue(getNAttackValue() + 60);
			setSAttackValue2(getSAttackValue2() + 100);
			setSAttackValue3(getSAttackValue3() + 100);
		}
	}

	void setRestore2(float dt) override
	{
		CharacterBase::setRestore2(dt);

		uint32_t hp = getHP();

		// TODO: Make Maito Gai
		// if (htLv >= 8)
		// {
		// 	setHPValue(hp > 1000 ? hp - 1000 : 100);
		// }
		if (htLv >= 5)
		{
			setHPValue(hp > 200 ? hp - 200 : 100);
		}
		else if (htLv >= 4)
		{
			setHPValue(hp > 150 ? hp - 150 : 100);
		}
		else if (htLv >= 3)
		{
			setHPValue(hp > 100 ? hp - 100 : 100);
		}
	}

	// Lee

	void perform() override
	{
		_mainTarget = nullptr;
		findHeroHalf();

		tryUseGear6();
		tryBuyGear(GearType::Gear06, GearType::Gear07, GearType::Gear02);

		if (needBackToTowerToRestoreHP() ||
			needBackToDefendTower())
			return;

		if (_mainTarget && _mainTarget->isNotFlog())
		{
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTarget();

			if ((isFreeState()) && abs(sp.x) < 128)
			{
				if (_isCanSkill1 && htLv < 5)
				{
					changeSide(sp);
					attack(SKILL1);
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
					if (abs(sp.x) > 48 || abs(sp.y) > 32)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					if (_isCanOugis1 && !_isControlled && _mainTarget->getDEF() < 5000 && !_mainTarget->_isArmored && _mainTarget->getState() != State::KNOCKDOWN && !_mainTarget->_isSticking && htLv >= 1)
					{
						changeSide(sp);
						attack(OUGIS1);
					}
					else if (_isCanSkill2)
					{
						changeSide(sp);
						attack(SKILL2);
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
				if (_isCanSkill2 && _mainTarget->isFlog())
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

	// RockLee

	void perform_RockLee()
	{
		_mainTarget = nullptr;
		findHeroHalf();

		tryUseGear6();
		tryBuyGear(GearType::Gear06, GearType::Gear07, GearType::Gear02);

		if (needBackToTowerToRestoreHP() ||
			needBackToDefendTower())
			return;

		if (_mainTarget && _mainTarget->isNotFlog())
		{
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTarget();

			if (isFreeState())
			{
				if (_isCanSkill1 && htLv < 5)
				{
					changeSide(sp);
					attack(SKILL1);
					return;
				}
				else if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && _mainTarget->getDEF() < 5000 && !_mainTarget->_isArmored && _mainTarget->getState() != State::KNOCKDOWN && !_mainTarget->_isSticking && htLv >= 3)
				{
					changeSide(sp);
					attack(OUGIS2);
				}
				else if (enemyCombatPoint > friendCombatPoint && abs(enemyCombatPoint - friendCombatPoint) > 3000 && !_isHealing && !_isControlled)
				{
					if (abs(sp.x) < 160)
						stepBack2();
					else
						idle();
					return;
				}
				else if (abs(sp.x) < 128 || htLv >= 5)
				{
					if (abs(sp.x) > 46 || abs(sp.y) > 32)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}

					if (_isCanOugis1 && !_isControlled && _mainTarget->getDEF() < 5000 && !_mainTarget->_isArmored && _mainTarget->getState() != State::KNOCKDOWN && !_mainTarget->_isSticking && htLv >= 1)
					{
						changeSide(sp);
						attack(OUGIS1);
					}
					else if (_isCanSkill2)
					{
						changeSide(sp);
						attack(SKILL2);
					}
					else if (_isCanSkill3 && htLv >= 3)
					{
						changeSide(sp);
						attack(SKILL3);
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
				if (_isCanSkill2 && _mainTarget->isFlog())
				{
					changeSide(sp);
					attack(SKILL2);
				}
				else if (_isCanSkill3 && htLv >= 3 && isBaseDanger && _mainTarget->isFlog())
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

	// Callbacks

	bool isEnableSkill05() override { return htLv >= 3; }

private:
	void tryLockSkillButton()
	{
		if (htLv < 3 && isPlayer())
		{
			getGameLayer()->getHudLayer()->skill3Button->setLock();
		}
	}
};
