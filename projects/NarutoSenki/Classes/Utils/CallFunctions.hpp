#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class CallFunc : public CCCallFunc
{
public:
	static CallFunc *create(const std::function<void()> &func)
	{
		CallFunc *pRet = new CallFunc();

		if (pRet && pRet->initWithTarget(func))
		{
			pRet->autorelease();
			return pRet;
		}

		CC_SAFE_DELETE(pRet);
		return nullptr;
	}

	bool initWithTarget(const std::function<void()> &func)
	{
		_func = func;
		return true;
	}

	CCObject *copyWithZone(CCZone *zone)
	{
		CCZone *pNewZone = nullptr;
		CallFunc *pRet = nullptr;

		if (zone && zone->m_pCopyObject)
		{
			// in case of being called at sub class
			pRet = (CallFunc *)(zone->m_pCopyObject);
		}
		else
		{
			pRet = new CallFunc();
			zone = pNewZone = new CCZone(pRet);
		}

		CCCallFunc::copyWithZone(zone);
		pRet->initWithTarget(_func);
		CC_SAFE_DELETE(pNewZone);
		return pRet;
	}

	void execute()
	{
		if (_func)
			_func();
	}

protected:
	std::function<void()> _func;
};
