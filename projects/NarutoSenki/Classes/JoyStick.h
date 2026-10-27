#pragma once
#include "Defines.h"

class HudLayer;

class JoyStick : public Sprite, public CCTouchDelegate
{
public:
	Vec2 _direction;
	Sprite *_joyStickControl;
	Vec2 _defaultPotion;

	bool init();
	void onEnter();
	void onExit();

	void keyUpdate(float direction);
	void keyEnded(float direction);

	PROP(HudLayer *, _delegate, Delegate);

	CREATE_FUNC(JoyStick);

protected:
	bool ccTouchBegan(Touch *touch, Event *event);
	void ccTouchMoved(Touch *touch, Event *event);
	void ccTouchEnded(Touch *touch, Event *event);

	void updateDirectionForTouchLocation(Touch *touch);
	void updateJoyStick(float distance, Vec2 direction);
};
