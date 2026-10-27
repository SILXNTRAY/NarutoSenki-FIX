#pragma once
#include "GameMode/IGameModeHandler.hpp"

class ModeRegular : public IGameModeHandler
{
private:
	uint8_t konohaHeroCount;
	uint8_t akatsukiHeroCount;

public:
	const uint8_t kMaxHeroNum = 4;
	const uint8_t kDefaultHeroNum = 3;

	ModeRegular(uint8_t konohaHeroCount, uint8_t akatsukiHeroCount)
	{
		this->konohaHeroCount = konohaHeroCount <= kMaxHeroNum ? konohaHeroCount : kMaxHeroNum;
		this->akatsukiHeroCount = akatsukiHeroCount <= kMaxHeroNum ? akatsukiHeroCount : kMaxHeroNum;
	}

	void init()
	{
	}

	void onInitHeros()
	{
		initHeros(konohaHeroCount, akatsukiHeroCount);
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
