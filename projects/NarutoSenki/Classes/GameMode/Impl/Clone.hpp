#pragma once
#include "GameMode/IGameModeHandler.hpp"

class ModeClone : public IGameModeHandler
{
private:
	const int kGenerateCount = 3;

	bool isOneForAllGroups;

public:
	ModeClone(bool isOneForAllGroups)
	{
		this->isOneForAllGroups = isOneForAllGroups;
	}

	void init()
	{
		CCLOG("Enter Clone mode.");

		if (Cheats >= kMaxCheats)
			gd.use4v4SpawnLayout = true;
		gd.isHardCore = true;
	}

	void onInitHeros()
	{
		Group playerGroup;
		Group enemyGroup;
		getRandomGroups(playerGroup, enemyGroup);
		setPlayerTeamByGroup(playerGroup);

		auto playerHero = getSelectedOrRandomHero();
		auto enemyHero = getRandomHeroExcept(playerHero);

		addHero(playerHero, Role::Player, playerGroup);
		if (Cheats >= kMaxCheats)
		{
			addHeros(3, playerHero, Role::Com, playerGroup);
			addHeros(4, enemyHero, Role::Com, enemyGroup);
		}
		else
		{
			addHeros(kGenerateCount - 1, playerHero, Role::Com, playerGroup);
			addHeros(kGenerateCount, enemyHero, Role::Com, enemyGroup);
		}
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
	}

	void onCharacterReborn(CharacterBase *c)
	{
	}
};
