#include "JoyStick.h"
#include "HudLayer.h"

bool JoyStick::init()
{
	RETURN_FALSE_IF(!Sprite::init());

	initWithSpriteFrameName("JoyStickBg.png");
	setAnchorPoint(Vec2(0, 0));

	_joyStickControl = Sprite::createWithSpriteFrameName("JoyStick.png");
	_joyStickControl->setAnchorPoint(Vec2(0, 0));

	_defaultPotion = Vec2(getContentSize().width / 2 - _joyStickControl->getContentSize().width / 2,
						  getContentSize().height / 2 - _joyStickControl->getContentSize().height / 2);

	_joyStickControl->setPosition(_defaultPotion);
	addChild(_joyStickControl);

	return true;
}

void JoyStick::onEnter()
{
	Sprite::onEnter();
	Director::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void JoyStick::onExit()
{
	Sprite::onExit();
	Director::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool JoyStick::ccTouchBegan(Touch *touch, Event *event)
{
	Vec2 curPoint = touch->getLocation();
	if (curPoint.x > winSize.width / 2 || curPoint.y > winSize.height / 2)
	{
		return false;
	}

	return true;
}

void JoyStick::ccTouchMoved(Touch *touch, Event *event)
{
	if (!_delegate->_isAllButtonLocked)
	{
		updateDirectionForTouchLocation(touch);
	}
}

void JoyStick::ccTouchEnded(Touch *touch, Event *event)
{
	if (!_delegate->_isAllButtonLocked)
	{
		_joyStickControl->setPosition(_defaultPotion);
		_delegate->JoyStickRelease();
	}
}

void JoyStick::updateDirectionForTouchLocation(Touch *touch)
{
	Vec2 startPoint = Vec2(32 + getContentSize().width / 2,
						   32 + getContentSize().height / 2);
	Vec2 curPoint = touch->getLocation();
	Vec2 sp = curPoint - startPoint;
	float distance = sp.getLength();
	float radians = sp.getAngle();
	float degrees = -1 * CC_RADIANS_TO_DEGREES(radians);

	if (degrees <= 22.5 && degrees >= -22.5)
	{
		// right
		_direction = Vec2(1.0, 0.0);
	}
	else if (degrees > 22.5 && degrees < 67.5)
	{
		// bottom right
		_direction = Vec2(1.0, -1.0);
	}
	else if (degrees >= 67.5 && degrees <= 112.5)
	{
		// bottom
		_direction = Vec2(0.0, -1.0);
	}
	else if (degrees > 112.5 && degrees < 157.5)
	{
		// bottom left
		_direction = Vec2(-1.0, -1.0);
	}
	else if (degrees >= 157.5 || degrees <= -157.5)
	{
		// left
		_direction = Vec2(-1.0, 0.0);
	}
	else if (degrees < -22.5 && degrees > -67.5)
	{
		// top right
		_direction = Vec2(1.0, 1.0);
	}
	else if (degrees <= -67.5 && degrees >= -112.5)
	{
		// top
		_direction = Vec2(0.0, 1.0);
	}
	else if (degrees < -112.5 && degrees > -157.5)
	{
		// top left
		_direction = Vec2(-1.0, 1.0);
	};

	updateJoyStick(distance, _direction);
	_delegate->JoyStickUpdate(_direction);
}

void JoyStick::updateJoyStick(float distance, Vec2 direction)
{
	if (distance < 27.5)
	{
		_joyStickControl->setPosition(_defaultPotion + (direction * distance));
	} /*else if (distance > 96) {
		_joyStickControl->setPosition(_defaultPotion + (direction * 53));
	} */
	else
	{
		_joyStickControl->setPosition(_defaultPotion + (direction * 26.5f));
	}
}
