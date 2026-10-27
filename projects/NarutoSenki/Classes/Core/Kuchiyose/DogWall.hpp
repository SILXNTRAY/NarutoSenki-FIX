#pragma once
#include "Hero.hpp"

class DogWall : public Hero
{
	void perform() override
	{
		attack(NAttack);
	}

	void setAI(float dt) override
	{
		attack(NAttack);
	}
};
