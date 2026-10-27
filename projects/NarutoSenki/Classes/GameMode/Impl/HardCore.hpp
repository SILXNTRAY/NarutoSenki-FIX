#pragma once
#include "GameMode/IGameModeHandler.hpp"

class ModeHardCore : public IGameModeHandler
{
public:
	void init()
	{
		CCLOG("Enter HardCore mode.");

		Cheats = 7; // Use 4 vs 4 map position
		gd.enableGear = false;
		gd.isHardCore = true;
		gd.use4v4SpawnLayout = true;
	}

	void onInitHeros()
	{
		initHeros(4, 4);
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
