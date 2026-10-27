#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "Data/Types.h"
#include "Data/UnitDefines.h"
#include "Data/Version.h"
#include "Enums/Audio.hpp"
#include "Enums/Character.h"
#include "Utils/Utils.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

#define winSize Director::sharedDirector()->getWinSize()
#define random(x) (rand() % x)
#define setRand() srand((uint32_t)time(0))

#define is_same(__Str1, __Str2) (strcmp(__Str1, __Str2) == 0)
#define to_cstr(var) (std::to_string(var).c_str())
