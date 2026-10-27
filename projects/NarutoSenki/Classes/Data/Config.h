#pragma once
#include "Data/Fonts.h"

#define FONT_NAME "Microsoft YaHei"

// Game

#define RES_X 570
#define RES_y 320

#define kSpeedBase 480 / 1280

extern int Cheats;
#define kMaxCheats 7

#define kFlogCount 6
#define kComCount 5
#define MapPosCount 3

// UI

// Layer order
#define kBgOrder 0
#define kGameLayerOrder 1
#define kHudLayerOrder 2

// Game layer children order
#define kMapOrder -5000
#define kShadowOrder -4000
#define kCutOrder 1000
#define kcharacterOrder 2
#define kBulletOrder 3
#define kDamageEffectOrder 100
#define kNumberOrder 200
#define kSkillEffectOrder 300
#define kFontOrder 400

#define DETAIL_NS_BEGIN \
	namespace detail    \
	{
#define DETAIL_NS_END }

#define ACTION_CONSTANT_NS_BEGIN \
	namespace ActionConstant     \
	{
#define ACTION_CONSTANT_NS_END }
