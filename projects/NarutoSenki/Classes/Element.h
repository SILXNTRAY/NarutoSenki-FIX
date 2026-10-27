#pragma once
#include "CharacterBase.h"
#include "GameLayer.h"
#include "HPBar.h"

class Monster : public CharacterBase
{
public:
	Monster();
	~Monster();

	bool init();
	void initAction();
	void setID(const string &name, Role role, Group group);
	void setHPbar();
	void changeHPbar();
	void setDirectMove(int length, float delay, bool isReverse);
	void setEaseIn(int length, float delay);
	void setDirectMoveBy(int length, float delay);

	CREATE_FUNC(Monster);

protected:
	void dealloc();
	void setAI(float dt);
	void setResume();
};

#include "Core/Tower/Tower.hpp"

#include "Core/Warrior/Flog.hpp"

#include "Core/Projectile/Bullet.hpp"
