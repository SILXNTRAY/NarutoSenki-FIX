#pragma once
#include "CharacterBase.h"
#include "HPBar.h"

// TODO: Rename to 'Projectile'
class Bullet : public CharacterBase
{
public:
	CREATE_FUNC(Bullet);

	bool init()
	{
		RETURN_FALSE_IF(!Sprite::init());

		scheduleUpdate();

		return true;
	}

	void setID(const string &name, Role role, Group group)
	{
		clearActionData();
		setName(name);
		setRole(role);
		setGroup(group);

		CCArray *animationArray = CCArray::create();
		auto filePath = format("Unit/Projectile/{}.xml", name);
		KTools::readXMLToArray(filePath, animationArray);

		CCArray *tmpAction = (CCArray *)(animationArray->objectAtIndex(0));
		CCArray *tmpData = (CCArray *)(tmpAction->objectAtIndex(0));
		idleArray = (CCArray *)(tmpAction->objectAtIndex(1));

		// init nAttack data & Frame Array
		tmpAction = (CCArray *)(animationArray->objectAtIndex(7));
		tmpData = (CCArray *)(tmpAction->objectAtIndex(0));

		uint32_t tmpValue;
		uint32_t tmpCD;
		int tmpCombatPoint;

		readData(tmpData, _nAttackType, tmpValue, _nAttackRangeX, _nAttackRangeY, tmpCD, tmpCombatPoint);
		setNAttackValue(tmpValue);
		nattackArray = (CCArray *)(tmpAction->objectAtIndex(1));

		if (getName() == ProjectileEnum::Amaterasu)
		{
			// init DeadFrame
			tmpAction = (CCArray *)(animationArray->objectAtIndex(6));
			deadArray = (CCArray *)(tmpAction->objectAtIndex(1));
		}

		initAction();
	}

	void initAction()
	{
		setIdleAction(createAnimation(idleArray, 5, true, false));

		if (deadArray)
			setDeadAction(createAnimation(deadArray, 10, false, false));

		setNAttackAction(createAnimation(nattackArray, 10, true, false));
	}

	void setMove(int length, float delay, bool isReverse)
	{
		Vec2 direction = Vec2(_isFlipped ? getPosition().x - length : getPosition().x + length, getPositionY());
		Vec2 direction2 = getPosition();
		auto mv = MoveTo::create(delay, direction);
		auto call = CallFunc::create(std::bind(&Bullet::dealloc, this));
		Action *moveAction;

		if (!isReverse)
		{
			moveAction = newSequence(mv, call);
		}
		else
		{
			auto mv2 = MoveTo::create(delay, direction2);
			moveAction = newSequence(mv, mv2, call);
		}

		runAction(moveAction);
	}

	void setEaseIn(int length, float delay)
	{
		Vec2 direction = Vec2(_isFlipped ? getPosition().x - length : getPosition().x + length, getPositionY());
		auto mv = MoveTo::create(1.0f, direction);
		auto eo = EaseIn::create(mv, delay);
		auto call = CallFunc::create(std::bind(&Bullet::dealloc, this));
		auto moveAction = newSequence(eo, call);
		runAction(moveAction);
	}

	void setAttack(float dt)
	{
		attack(NAttack);
	}

protected:
	void dealloc()
	{
		stopAllActions();

		if (getName() == ProjectileEnum::Amaterasu)
		{
			auto call = CallFunc::create(std::bind(&Bullet::removeFromParent, this));
			auto seq = newSequence(getDeadAction(), call);
			runAction(seq);
		}
		else
		{
			if (getName() == ProjectileEnum::HiraishinKunai)
			{
				if (_master->getState() == State::SATTACK)
				{
					_master->setState(State::NATTACK);
					_master->_markPoint = Vec2(getPositionX(), _originY);
					_master->changeAction2();
					_master->_isCanSkill2 = true;
					_master->sAttack(SKILL2);
				}
			}

			if (_master)
				_master->removeMon(this);
			removeFromParent();
		}
	}
};
