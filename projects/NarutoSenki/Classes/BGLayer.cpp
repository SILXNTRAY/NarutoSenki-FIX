#include "BGLayer.h"

void BGLayer::initBg(int mapId)
{
	bgMap = Sprite::create(GetMapBgPath(mapId));
	bgMap->setAnchorPoint(Vec2(0, 0));
	bgMap->setPosition(Vec2(0, 192));
	addChild(bgMap);
}
