#pragma once
#include "Hero.hpp"

class Minato : public Hero
{
	void perform() override
	{
		_mainTarget = nullptr;
		findHeroHalf();

		tryUseGear6();
		tryBuyGear(GearType::Gear06, GearType::Gear05, GearType::Gear02);

		if (getHpPercent() < 0.3f)
		{
			if (_isCanSkill1)
			{
				bool isMark = false;
				if (hasMonsterArrayAny())
				{
					for (auto mo : _monsterArray)
					{
						if (mo->getName() == SkillEnum::HiraishinMark)
						{
							if (isKonohaGroup() && mo->getPositionX() < getPositionX())
							{
								isMark = true;
							}
							else if (isAkatsukiGroup() && mo->getPositionX() > getPositionX())
							{
								isMark = true;
							}
						}
					}
				}
				if (isFreeState())
				{
					if (isMark)
					{
						attack(SKILL1);
						return;
					}
				}
			}
		}

		if (needBackToTowerToRestoreHP() ||
			needBackToDefendTower())
			return;

		if (_mainTarget && _mainTarget->isNotFlog())
		{
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTarget();

			if (isFreeState())
			{
				bool isMark = false;
				if (hasMonsterArrayAny())
				{
					for (auto mo : _monsterArray)
					{
						if (mo->getName() == SkillEnum::HiraishinMark)
						{
							isMark = true;
						}
					}
				}

				if (_isCanSkill1 && !isMark)
				{
					changeSide(sp);
					attack(SKILL1);
				}
				else if (_isCanOugis2 && !_isControlled && getGameLayer()->_isOugis2Game && _mainTarget->getDEF() < 5000)
				{
					if (abs(sp.x) > 64 || abs(sp.y) > 16)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					changeSide(sp);
					attack(OUGIS2);

					return;
				}
				else if (_isCanOugis1 && !_isControlled && _mainTarget->getDEF() < 5000)
				{
					if (abs(sp.x) > 64 || abs(sp.y) > 16)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					changeSide(sp);
					attack(OUGIS1);
					return;
				}
				else if (_isCanSkill2 && _mainTarget->getDEF() < 5000)
				{
					if (abs(sp.y) > 16)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					changeSide(sp);
					attack(SKILL2);
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
				else if (_isCanSkill3)
				{
					changeSide(sp);
					attack(SKILL3);
					return;
				}
				else
				{
					if (abs(sp.x) > 352 || abs(sp.y) > 128)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
					else if ((abs(sp.x) > 32 || abs(sp.y) > 32) && getNAttackValue() < 260)
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
				if (_isCanSkill3 && _mainTarget->isFlog())
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

		if (_isHealing && getHpPercent() < 1)
		{
			if (isFreeState())
				idle();
		}
		else
		{
			if (_isCanSkill1)
			{
				bool isMark = false;
				if (hasMonsterArrayAny())
				{
					for (auto mo : _monsterArray)
					{
						if (mo->getName() == SkillEnum::HiraishinMark)
						{
							if (isKonohaGroup() && mo->getPositionX() > getPositionX())
							{
								isMark = true;
							}
							else if (isAkatsukiGroup() && mo->getPositionX() < getPositionX())
							{
								isMark = true;
							}
						}
					}
				}

				if (isFreeState())
				{
					if (isMark)
					{
						attack(SKILL1);
						return;
					}
				}
			}

			stepOn();
		}
	}

	void changeAction() override
	{
		if (_skillChangeBuffValue == 17)
		{
			setSkill1Action(createAnimation(skillSPC1Array, 10, false, true));

			if (isPlayer())
			{
				auto frame = getSpriteFrame("Minato_skill1_1.png");
				getGameLayer()->getHudLayer()->skill1Button->setDisplayFrame(frame);
				if (getGameLayer()->getHudLayer()->skill1Button->_clickNum < 2)
				{
					getGameLayer()->getHudLayer()->skill1Button->_clickNum++;
				}
			}
		}
		else if (_skillChangeBuffValue == 18)
		{
			setNAttackValue(getNAttackValue() + 200);

			_nAttackRangeX = 16;
			_nAttackRangeY = 48;

			setNAttackAction(createAnimation(skillSPC3Array, 10, false, true));
		}
	}

	void resumeAction(float dt) override
	{
		setNAttackValue(getNAttackValue() - 200);
		_nAttackRangeX = 16;
		_nAttackRangeY = 48;
		setNAttackAction(createAnimation(nattackArray, 10, false, true));

		_markPoint = Vec2(0, 0);
		_startPoint = Vec2(0, 0);
		CharacterBase::resumeAction(dt);
	}

	void setActionResume() override
	{
		setSkill1Action(createAnimation(skill1Array, 10, false, true));
		_skillChangeBuffValue = 0;
	}
};
