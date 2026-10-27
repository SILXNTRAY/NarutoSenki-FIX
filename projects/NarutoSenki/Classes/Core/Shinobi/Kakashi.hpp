#pragma once
#include "Hero.hpp"
#include "Kuchiyose/DogWall.hpp"

class Kakashi : public Hero
{
	void perform() override
	{
		_mainTarget = nullptr;
		findHeroHalf();

		tryUseGear6();
		tryBuyGear(GearType::Gear06, GearType::Gear05, GearType::Gear02);

		if (needBackToTowerToRestoreHP() ||
			needBackToDefendTower())
			return;

		if (_mainTarget && _mainTarget->isNotFlog())
		{
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTarget();

			if (isFreeState())
			{
				if (_isCanSkill3)
				{
					changeSide(sp);
					attack(SKILL3);
					return;
				}
				else if (_isCanSkill2 && _mainTarget->getDEF() < 5000)
				{
					changeSide(sp);
					attack(SKILL2);
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
					if ((abs(sp.x) > 64 || abs(sp.y) > 32))
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}

					if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && _mainTarget->getDEF() < 5000 && !_mainTarget->_isArmored && _mainTarget->getState() != State::KNOCKDOWN && !_mainTarget->_isSticking)
					{
						changeSide(sp);
						attack(OUGIS2);
					}
					else if (_isCanOugis1 && !_isControlled && _mainTarget->getDEF() < 5000)
					{
						changeSide(sp);
						attack(OUGIS1);
					}
					else if (_isCanSkill1 && _mainTarget->getDEF() < 5000)
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
				if (_isCanSkill3 && _mainTarget->isFlog())
				{
					changeSide(sp);
					attack(SKILL3);
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
		setSkill1Action(createAnimation(skillSPC1Array, 10, false, true));
		setSkill2Action(createAnimation(skillSPC2Array, 10, false, true));
		setIdleAction(createAnimation(skillSPC3Array, 5, true, false));
		setTempAttackValue1(getSAttackValue1());
		setSAttackValue1(getSpcAttackValue1());

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

		if (isPlayer())
		{
			auto frame = getSpriteFrame("Kakashi_skill1_1.png");
			getGameLayer()->getHudLayer()->skill1Button->setDisplayFrame(frame);
			frame = getSpriteFrame("Kakashi_skill2_1.png");
			getGameLayer()->getHudLayer()->skill2Button->setDisplayFrame(frame);
		}
	}

	void resumeAction(float dt) override
	{
		setIdleAction(createAnimation(idleArray, 5, true, false));
		setSkill1Action(createAnimation(skill1Array, 10, false, true));
		setSkill2Action(createAnimation(skill2Array, 10, false, true));

		setSAttackValue1(getTempAttackValue1());

		if (isPlayer())
		{
			auto frame = getSpriteFrame("Kakashi_skill1.png");
			getGameLayer()->getHudLayer()->skill1Button->setDisplayFrame(frame);
			frame = getSpriteFrame("Kakashi_skill2.png");
			getGameLayer()->getHudLayer()->skill2Button->setDisplayFrame(frame);
		}
		CharacterBase::resumeAction(dt);
	}

	Hero *createClone(int cloneTime) override
	{
		auto clone = createSummonHero<DogWall>(SummonEnum::DogWall);
		clone->setPosition(Vec2(getPositionX() + (_isFlipped ? -56 : 56), getPositionY()));
		clone->setAnchorPoint(Vec2(0.5f, 0.1f));
		clone->_isArmored = true;
		return clone;
	}
};
