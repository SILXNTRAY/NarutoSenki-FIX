#pragma once
#include "Defines.h"

class AppDelegate : private Application
{
public:
	AppDelegate();
	~AppDelegate();

	bool applicationDidFinishLaunching();
	void applicationDidEnterBackground();
	void applicationWillEnterForeground();
};
