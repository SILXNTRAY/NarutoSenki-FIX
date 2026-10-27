#pragma once
#include "Core/Provider.hpp"
#include "Core/Utils/UnitEx.hpp"
#include "GameMode/IGameModeHandler.hpp"

class ModeRandomDeathmatch : public IGameModeHandler
{
public:
	const uint8_t kRebornCount = 40;
	const uint8_t kHeroAmount = 3;

private:
	uint8_t konohaRebornCount;
	uint8_t akatsukiRebornCount;
	uint8_t konohaLiveCount;
	uint8_t akatsukiLiveCount;

public:
	void init()
	{
		CCLOG("Enter Random Deathmatch mode.");

		konohaRebornCount = kRebornCount;
		akatsukiRebornCount = kRebornCount;

		konohaLiveCount = kHeroAmount;
		akatsukiLiveCount = kHeroAmount;

		gd.isHardCore = true;
	}

	void onInitHeros()
	{
		initHeros(kHeroAmount, kHeroAmount);
	}

	void onGameStart()
	{
	}

	void onGameOver()
	{
	}

	void onCharacterInit(CharacterBase *c)
	{
	}

	void onCharacterDead(CharacterBase *c)
	{
		// CCLOG("[Character Dead] Name: %s, Role: %s, Group: %s", c->getName().c_str(), c->getRole(), c->getGroup());

		if (c->isPlayerOrCom())
		{
			uint8_t &count = c->isKonohaGroup() ? konohaRebornCount : akatsukiRebornCount;
			uint8_t &liveCount = c->isKonohaGroup() ? konohaLiveCount : akatsukiLiveCount;
			if (count == 0)
			{
				c->enableReborn = false;
				if (liveCount == 0)
					getGameLayer()->onGameOver(c->getGroup() != playerGroup);
			}
			else
			{
				count--;
				liveCount--;
				setRandomHero(c);
				c->unschedule(schedule_selector(CharacterBase::resumeAction));
			}
		}
	}

	void onCharacterReborn(CharacterBase *c)
	{
		// CCLOG("[Character Reborn] Name: %s, Role: %s, Group: %s", c->getName().c_str(), c->getRole(), c->getGroup());

		if (c->isPlayerOrCom())
		{
			uint8_t liveCount = c->isKonohaGroup() ? konohaLiveCount++ : akatsukiLiveCount++;
		}

		if (c->changeCharId > -1)
		{
			auto gameLayer = getGameLayer();
			// initial a new random character
			auto newCharName = heroVector.at(c->changeCharId);
			// CCLOG("[Change Character] %s from %s to %s", c->getRole(), c->getName().c_str(), newCharName.c_str());

			if (c->getName() == newCharName)
			{
				c->changeCharId = -1;
				return;
			}
			else
			{
				// If the character has changed, then cleanup
				CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(c);
				c->stopAllActions();
				for (auto mo : c->getMonsterArray())
				{
					if (auto heroMo = dynamic_cast<Hero *>(mo))
					{
						heroMo->dealloc();
					}
					else
					{
						CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(mo);
						mo->stopAllActions();
						mo->unscheduleAllSelectors();
						mo->removeFromParent();
					}
				}
				// TODO: Remove all Clone

				c->removeAllClones();
				std::erase(getGameLayer()->_CharacterArray, c);
				getGameLayer()->clearAllFlogsMainTarget(c);

				if (c->_shadow)
					c->_shadow->removeFromParent();
				if (c->getMaster())
					c->getMaster()->removeMon(c);
				c->removeFromParent();

				// load new char assets
				LoadLayer::perloadCharIMG(newCharName);
				// Unload old character assets if not used by the other player or AI
				auto oldCharName = c->getName();
				if (std::find(heroVector.begin(), heroVector.end(), oldCharName) == heroVector.end())
				{
					LoadLayer::unloadCharIMG(c);
				}
			}
			auto hudLayer = gameLayer->getHudLayer();
			auto newChar = gameLayer->addHero(newCharName, c->getRole(), c->getGroup(), c->getSpawnPoint(), c->getCharId());
			bool isPlayer = newChar->isPlayer();
			newChar->setCoin(c->getCoin());
			newChar->setCKR(c->getCKR());
			newChar->setCKR2(c->getCKR2());
			newChar->setEXP(c->getEXP());
			newChar->setLV(c->getLV());
			newChar->setKillNum(c->getKillNum());
			newChar->setWalkSpeed(224);
			newChar->setGearArray(c->getGearArray());
			newChar->changeHPbar();
			newChar->updateDataByLVOnly();
			for (auto gear : c->getGearArray())
			{
				if (gear == GearType::Gear00)
				{
					newChar->_isCanGear00 = true;
				}
				else if (gear == GearType::Gear01)
				{
					newChar->gearCKRValue = 25;
				}
				else if (gear == GearType::Gear02)
				{
					newChar->isAttackGainCKR = true;
				}
				else if (gear == GearType::Gear03)
				{
					newChar->_isCanGear03 = true;
				}
				else if (gear == GearType::Gear04)
				{
					if (newChar->getTempAttackValue1())
						newChar->setTempAttackValue1(newChar->getTempAttackValue1() + 160);
					newChar->setNAttackValue(newChar->getNAttackValue() + 160);
					newChar->hasArmorBroken = true;
				}
				else if (gear == GearType::Gear05)
				{
					newChar->isGearCD = true;
					newChar->_sAttackCD1 -= 5;
					newChar->_sAttackCD2 -= 5;
					newChar->_sAttackCD3 -= 5;
				}
				else if (gear == GearType::Gear06)
				{
					newChar->_isCanGear06 = true;
				}
				else if (gear == GearType::Gear07)
				{
					newChar->gearRecoverValue = 3000;
					if (isPlayer)
					{
						hudLayer->item1Button->setCD(3000);
						hudLayer->item1Button->_isColdChanged = true;
					}
				}
				else if (gear == GearType::Gear08)
				{
					newChar->setMaxHPValue(newChar->getMaxHP() + 6000);
					newChar->hasArmor = true;
				}
			}
			newChar->_deadNum = c->_deadNum;
			newChar->_flogNum = c->_flogNum;
			newChar->isBaseDanger = c->isBaseDanger;

			if (isPlayer)
			{
				gameLayer->currentPlayer = newChar;
				// reset hud layer
				hudLayer->updateSkillButtons();
				hudLayer->resetSkillButtons();

				hudLayer->status_hpbar->setOpacity(255);
				hudLayer->status_expbar->setOpacity(255);
				hudLayer->setHPLose(newChar->getHpPercent());
			}
			else if (newChar->isCom())
			{
				newChar->doAI();
			}
		}
	}

private:
	void setRandomHero(CharacterBase *c)
	{
		auto index = getIndexByHero(c);
		if (index == -1)
		{
			CCLOGERROR("Not found hero %s from hero vector", c->getName().c_str());
			return;
		}
		c->changeCharId = index;

		auto newChar = getRandomHeroExceptAll(heroVector);
		heroVector.at(index) = newChar;
	}

	inline int getIndexByHero(CharacterBase *c)
	{
		return (int)heroVector.size() < c->getCharId() ? -1 : c->getCharId() - 1;
	}
};
