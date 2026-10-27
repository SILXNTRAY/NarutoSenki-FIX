#pragma once
#include "Hero.hpp"

class Karasu : public Hero
{
	void perform() override
	{
		if (notFindHero(kAttackRange - 32, true))
		{
			if (notFindFlog(kAttackRange - 32, true))
				_mainTarget = nullptr;
		}

		if (_mainTarget)
		{
			Vec2 moveDirection;
			if (abs((_master->getPosition() - getPosition()).x) > kAttackRange - 48)
			{
				if (isFreeState())
				{
					moveDirection = getDirByMoveTo(_master);
					walk(moveDirection);
					return;
				}
			}
			Vec2 sp = getDistanceToTarget();

			if (_mainTarget->isFlog())
			{
				if (abs(sp.x) > 32 || abs(sp.y) > 32)
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
				if (abs(sp.x) > 32 || abs(sp.y) > 16)
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
					if (_master->isFreeState())
					{
						if (_master->_isCanSkill2 && _mainTarget->getDEF() < 5000 && (_master->_isControlled || _master->_isAI == true))
						{
							changeSide(sp);

							if (_master->isNotPlayer())
							{
								_master->attack(SKILL2);
							}
							else if (_master->isPlayer())
							{
								_master->attack(SKILL2);
							}
						}
						else
						{
							changeSide(sp);
							attack(NAttack);
						}
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
			if (
				_master->getState() == State::WALK ||
				_master->getState() == State::NATTACK ||
				_master->getState() == State::SATTACK ||
				_master->getState() == State::OATTACK)
			{
				stepOn();
			}
			else
			{
				if (_state == State::WALK ||
					_state == State::NATTACK)
				{
					idle();
				}
			}
		}
	}

	void dealloc() override
	{
		_master->setActionResume();

		Hero::dealloc();
	}
};
