#pragma once
#include "Hero.hpp"

class Saso : public Hero
{
	void perform() override
	{
		if (notFindHero(kAttackRange - 32, true))
		{
			if (notFindFlog(kAttackRange - 32, true))
				_mainTarget = nullptr;
		}

		Vec2 moveDirection;
		if (abs((_master->getPosition() - getPosition()).x) > 64)
		{
			if (isFreeState())
			{
				moveDirection = getDirByMoveTo(_master);
				walk(moveDirection);
				return;
			}
		}

		if (_mainTarget)
		{
			Vec2 sp = Vec2(_mainTarget->getPositionX(), _mainTarget->_originY ? _mainTarget->_originY : _mainTarget->getPositionY()) -
					  Vec2(getPositionX(), _originY ? _originY : getPositionY());

			if (_mainTarget->isFlog())
			{
				if (abs(sp.x) > 48 || abs(sp.y) > 16)
				{
					if (_master->getState() == State::IDLE ||
						_master->getState() == State::WALK ||
						_master->getState() == State::NATTACK ||
						_master->getState() == State::SATTACK ||
						_master->getState() == State::OATTACK ||
						_master->getState() == State::O2ATTACK)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
					}
				}
				else
				{
					if (isFreeState())
					{
						changeSide(sp);
						attack(NAttack);
					}
				}
				return;
			}
			else
			{
				if ((abs(sp.x) > 48 || abs(sp.y) > 16))
				{
					if (_master->getState() == State::IDLE ||
						_master->getState() == State::WALK ||
						_master->getState() == State::NATTACK ||
						_master->getState() == State::SATTACK ||
						_master->getState() == State::OATTACK ||
						_master->getState() == State::O2ATTACK)
					{
						moveDirection = sp.getNormalized();
						walk(moveDirection);
						return;
					}
				}
				else if (isFreeState())
				{
					if (_isCanSkill1 && _mainTarget->getDEF() < 5000)
					{
						changeSide(sp);
						attack(SKILL1);
						scheduleOnce(schedule_selector(CharacterBase::enableSkill1), _sAttackCD1);
					}
					else
					{
						changeSide(sp);
						attack(NAttack);
					}
				}
				return;
			}
		}

		if (abs((_master->getPosition() - getPosition()).x) > kAttackRange - 64)
		{
			Vec2 moveDirection = getDirByMoveTo(_master);
			walk(moveDirection);
			return;
		}
		else
		{
			if (_state == State::WALK ||
				_state == State::NATTACK)
				idle();
		}
	}

	void dealloc() override
	{
		_master->unlockSkill4Button();

		Hero::dealloc();
	}
};
