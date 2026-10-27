#pragma once
#include "GameLayer.h"

class BGLayer : public Layer
{
public:
	Sprite *bgMap;

	void initBg(int mapId);

	CREATE_FUNC(BGLayer);
};
