#pragma once
#include "GameMode/IGameModeHandler.hpp"

class ModeDeathmatch : public IGameModeHandler
{
public:
	void init()
	{
		CCLOG("Enter Deathmatch mode.");

		gd.isHardCore = true;
	}

	void onInitHeros()
	{
		initHeros(3, 3);
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
