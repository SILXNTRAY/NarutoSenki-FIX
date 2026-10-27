#pragma once
#include "GameLayer.h"

// TODO: Create a states panel in battle
class StatsLayer : public Layer
{
public:
	void update()
	{
	}

	CREATE_FUNC(StatsLayer);

private:
	bool init()
	{
		RETURN_FALSE_IF(!Layer::init());

		return true;
	}

	Sprite *bg;
};
