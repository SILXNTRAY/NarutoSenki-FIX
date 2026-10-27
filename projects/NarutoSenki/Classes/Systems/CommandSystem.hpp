#pragma once
#include "Core/Hero.hpp"
#include "Enums/Enums.hpp"

#include <unordered_map>

namespace Command
{
	mk_const(addHP);
	mk_const(setInvincible);
	mk_const(setGainCKR);
	mk_const(reInvincible);
	mk_const(setInvisible);
	mk_const(reInvisible);
	mk_const(setTransport2);
	mk_const(setTransport);
	mk_const(reTransport);
	mk_const(setDead);
	mk_const(findTarget);
	mk_const(setRevive);
	mk_const(setTrade);
	mk_const(addExtern);
	mk_const(pauseJump);
	mk_const(setCounter);
} // namespace Command

using CommandHandler = std::function<void(CharacterBase *)>;

class CommandSystem
{
private:
	static inline std::unordered_map<string, CommandHandler> cmdMap;

public:
	static inline void on(const string &cmd, CommandHandler handler)
	{
		cmdMap.insert(std::make_pair(cmd, handler));
	}

	static inline void invoke(const string &cmd, CharacterBase *thiz)
	{
		auto it_find = cmdMap.find(cmd);
		if (it_find != cmdMap.end())
		{
			auto handler = it_find->second;
			handler(thiz);
		}
		else
		{
			CCLOGERROR("Not found command handler `%s`", cmd.c_str());
		}
	}

	static inline void remove(const string &cmd)
	{
		cmdMap.erase(cmd);
	}

	static inline void replaceOrInsert(const string &cmd, CommandHandler handler)
	{
		cmdMap[cmd] = handler;
	}

	static inline void reset()
	{
		cmdMap.clear();
		init();

		if (cmdMap.size() > 0)
			CCLOG("[ Command System ] Count: %lu ", cmdMap.size());
		else
			CCLOG("[ Command System ] Initial error, not found any command");
	}

private:
	static void init()
	{
		on(Command::addExtern, [](CharacterBase *thiz)
		   {
			   Vector<SpriteFrame *> spriteFrames;

			   if (thiz->getName() == HeroEnum::Tenten)
			   {
				   int i = 1;
				   while (i < 11)
				   {
					   auto frame = getSpriteFrame("Tenten_Extern_0{}", i);
					   spriteFrames.pushBack(frame);
					   i += 1;
				   }
			   }

			   auto tempAnimation = Animation::createWithSpriteFrames(spriteFrames, 0.1f);
			   auto tempAction = Animate::create(tempAnimation);

			   auto tempChar = Sprite::createWithSpriteFrameName(format("{}_Extern_01", thiz->getName()).c_str());
			   tempChar->setAnchorPoint(Vec2(0.5f, 0));
			   tempChar->setPosition(thiz->getPosition());
			   getGameLayer()->addChild(tempChar, -thiz->_originY);

			   auto call = CallFunc::create(std::bind(&CharacterBase::disableShadow, thiz, tempChar));
			   auto seq = newSequence(tempAction, call);
			   tempChar->runAction(seq);
		   });
		on(Command::addHP, [](CharacterBase *thiz)
		   {
			   if (thiz->_hpBar)
			   {
				   thiz->setHPValue(thiz->getMaxHP());
				   thiz->_hpBar->setPositionY(thiz->getHeight());
			   }
		   });
		on(Command::findTarget, [](CharacterBase *thiz)
		   {
			   if (thiz->notFindHero(0))
			   {
				   if (thiz->notFindFlog(0) ||
					   thiz->getName() == HeroEnum::RikudoNaruto || thiz->getName() == HeroEnum::SageNaruto)
					   thiz->_mainTarget = nullptr;
			   }

			   if (thiz->_mainTarget)
			   {
				   if (thiz->getName() == SkillEnum::Dogs ||
					   thiz->getName() == SkillEnum::Yominuma ||
					   thiz->getName() == SkillEnum::SandBall ||
					   thiz->getName() == SkillEnum::Sabaku ||
					   thiz->getName() == SkillEnum::Yataikuzu ||
					   thiz->getName() == HeroEnum::Lee ||
					   thiz->getName() == HeroEnum::RockLee)
				   {
					   thiz->_markPoint = Vec2(thiz->_mainTarget->getPositionX(), thiz->_mainTarget->_originY ? thiz->_mainTarget->_originY : thiz->_mainTarget->getPositionY());
				   }
				   else if (thiz->getName() == SkillEnum::Tsukuyomi)
				   {
					   thiz->_markPoint = Vec2(thiz->_mainTarget->getPositionX(), thiz->_mainTarget->_originY ? thiz->_mainTarget->_originY : thiz->_mainTarget->getPositionY() + 2);
				   }
				   else if (thiz->getName() == SkillEnum::KageFeng)
				   {
					   thiz->_markPoint = Vec2(thiz->_mainTarget->getPositionX(), thiz->_mainTarget->_originY ? thiz->_mainTarget->_originY - 6 : thiz->_mainTarget->getPositionY() - 6);
				   }
				   else
				   {
					   thiz->_markPoint = Vec2(thiz->_mainTarget->_isFlipped ? thiz->_mainTarget->getPositionX() + 32 : thiz->_mainTarget->getPositionX() - 32,
											   thiz->_mainTarget->_originY ? thiz->_mainTarget->_originY : thiz->_mainTarget->getPositionY());
				   }
			   }
		   });
		on(Command::pauseJump, [](CharacterBase *thiz)
		   {
			   // pause jump
			   thiz->getActionManager()->addAction(thiz->_jumpUPAction, thiz, false);
		   });
		on(Command::setDead, [](CharacterBase *thiz)
		   {
			   thiz->_isSuicide = true;
			   thiz->dead();
		   });
		on(Command::setGainCKR, [](CharacterBase *thiz)
		   {
			   uint32_t boundValue = 1500;
			   thiz->increaseAllCkrs(boundValue, true, !thiz->_isControlled);
		   });
		on(Command::setInvincible, [](CharacterBase *thiz)
		   {
			   // set character invincible
			   thiz->_isInvincible = true;
		   });
		on(Command::reInvincible, [](CharacterBase *thiz)
		   {
			   // unset character invincible
			   thiz->_isInvincible = false;
		   });
		on(Command::setInvisible, [](CharacterBase *thiz)
		   {
			   thiz->setVisible(false);
			   thiz->_isVisable = false;
		   });
		on(Command::reInvisible, [](CharacterBase *thiz)
		   {
			   thiz->setVisible(true);
			   thiz->_isVisable = true;
		   });
		on(Command::setTransport, [](CharacterBase *thiz)
		   {
			   int tsPosX = thiz->getPositionX();
			   int tsPosY = thiz->getPositionY();

			   if (thiz->_mainTarget)
			   {
				   if (thiz->_mainTarget->_isFlipped)
				   {
					   thiz->setFlipX(true);
					   thiz->_isFlipped = true;
				   }
				   else
				   {
					   thiz->setFlipX(false);
					   thiz->_isFlipped = false;
				   }
			   }

			   if (thiz->getName() == HeroEnum::Sakura)
			   {
				   float posY = thiz->getPositionY();
				   if (!thiz->_originY)
				   {
					   if (posY == 0)
						   posY = 0.1f;
					   thiz->_originY = posY;
				   }
				   thiz->setPosition(Vec2(thiz->getPositionX(), thiz->getPositionY() + 64));
				   return;
			   }
			   else
			   {
				   if (thiz->_markPoint.x != 0)
				   {
					   thiz->_startPoint = Vec2(tsPosX, tsPosY);
					   tsPosX = thiz->_markPoint.x;
					   tsPosY = thiz->_markPoint.y;
					   thiz->_markPoint = Vec2(0, 0);
				   }
				   else if (thiz->_startPoint.x != 0)
				   {
					   tsPosX = thiz->_startPoint.x;
					   tsPosY = thiz->_startPoint.y;
					   thiz->_startPoint = Vec2(0, 0);
				   }
			   }

			   thiz->setPosition(Vec2(tsPosX, tsPosY));
			   CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMap", thiz);

			   if (thiz->getName() != SkillEnum::Yominuma)
			   {
				   getGameLayer()->reorderChild(thiz, -tsPosY);
			   }
		   });
		on(Command::reTransport, [](CharacterBase *thiz)
		   {
			   thiz->setPosition(Vec2(thiz->getPositionX(), thiz->_originY));
			   thiz->_originY = 0;
		   });
		// For special characters
		on(Command::setCounter, [](CharacterBase *thiz)
		   {
			   bool _isCounter = false;
			   if (thiz->hasMonsterArrayAny())
			   {
				   for (auto mo : thiz->getMonsterArray())
				   {
					   float distanceX = (mo->getPosition() - thiz->getPosition()).x;
					   float distanceY = (mo->getPosition() - thiz->getPosition()).y;
					   if (abs(distanceX) < 40 && abs(distanceY) < 15)
					   {
						   _isCounter = true;
					   }
				   }
			   }

			   if (_isCounter)
			   {
				   for (auto hero : getGameLayer()->_CharacterArray)
				   {
					   if (thiz->getGroup() != hero->getGroup() &&
						   hero->isPlayerOrCom() &&
						   hero->_state != State::DEAD)
					   {
						   if (hero->_hpBar)
						   {
							   if (hero->getHP() <= 2000)
								   hero->setDamage(thiz, "c_hit", hero->getHP(), false);
							   else
								   hero->setDamage(thiz, "c_hit", 2000, false);

							   if (hero->isPlayer())
								   getGameLayer()->setHPLose(hero->getHpPercent());
						   }
					   }
				   }
			   }
			   else
			   {
				   if (thiz->_hpBar)
				   {
					   if (thiz->getHP() <= 2000)
						   thiz->setDamage(thiz, "c_hit", thiz->getHP(), false);
					   else
						   thiz->setDamage(thiz, "c_hit", 2000, false);

					   if (thiz->isPlayer())
						   getGameLayer()->setHPLose(thiz->getHpPercent());
				   }
			   }

			   thiz->setActionResume();
		   });
		on(Command::setRevive, [](CharacterBase *thiz)
		   {
			   for (auto hero : getGameLayer()->_CharacterArray)
			   {
				   if (thiz->getGroup() == hero->getGroup() &&
					   hero->isPlayerOrCom() &&
					   hero->_state == State::DEAD &&
					   hero->rebornSprite)
				   {
					   hero->unschedule(schedule_selector(Hero::reborn));
					   hero->reborn(0.1f);
				   }
			   }
		   });
		on(Command::setTrade, [](CharacterBase *thiz)
		   {
			   for (auto hero : getGameLayer()->_CharacterArray)
			   {
				   if (hero->hearts > 0 &&
					   hero->_state == State::DEAD &&
					   hero->rebornSprite &&
					   hero->isPlayerOrCom() &&
					   hero->getName() != HeroEnum::Kakuzu)
				   {
					   Vec2 sp = hero->getPosition() - thiz->getPosition();
					   if (abs(sp.x) <= 48 && abs(sp.y) <= 48)
					   {
						   hero->hearts -= 1;
						   if (thiz->getGroup() != hero->getGroup())
						   {
							   thiz->setMaxHPValue(thiz->getMaxHP() + 100);
							   thiz->setNAttackValue(thiz->getNAttackValue() + 5);
						   }

						   if (thiz->isPlayer())
						   {
							   if (getGameLayer()->_isHardCoreGame)
							   {
								   getGameLayer()->setCoin(to_cstr(50 + (hero->getLV() - 1) * 10));
								   thiz->setCoinDisplay(50 + (hero->getLV() - 1) * 10);
								   thiz->addCoin(50 + (hero->getLV() - 1) * 10);
							   }
							   else
							   {
								   getGameLayer()->setCoin("50");
								   thiz->setCoinDisplay(50);
								   thiz->addCoin(50);
							   }
						   }
					   }
				   }
			   }
		   });
		on(Command::setTransport2, [](CharacterBase *thiz)
		   {
			   int tsPosX = thiz->getPositionX();
			   int tsPosY = thiz->getPositionY();

			   if (thiz->_state != State::NATTACK && thiz->hasMonsterArrayAny())
			   {
				   for (auto mo : thiz->getMonsterArray())
				   {
					   if (mo->getName() == SkillEnum::HiraishinMark)
					   {
						   tsPosX = mo->getPositionX();
						   tsPosY = mo->getPositionY();
						   mo->attack(NAttack);
					   }
				   }
			   }

			   thiz->setPosition(Vec2(tsPosX, tsPosY));
			   CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMap", thiz);

			   getGameLayer()->reorderChild(thiz, -tsPosY);
		   });
	}
};
