#include "StartMenu.h"
#include "MyUtils/KTools.h"

class GameScene : public Scene
{
public:
	bool init();

	static const char *getPlatform()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
		return "desktop";
#else
		return "mobile";
#endif
	}

	CREATE_FUNC(GameScene);
};
