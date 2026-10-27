#pragma once
#include "Defines.h"

class PauseLayer : public Layer
{
public:
	bool init(RenderTexture *snapshoot);

	Menu *pauseMenu = nullptr;
	Menu *soundMenu = nullptr;
	Menu *preMenu = nullptr;
	Layer *exitLayer = nullptr;
	MenuItem *bgm_btn = nullptr;
	MenuItem *voice_btn = nullptr;
	MenuItem *pre_btn = nullptr;

	static PauseLayer *create(RenderTexture *snapshoot);

private:
	void onResume(Ref *sender);
	void onBackToMenu(Ref *sender);
	void onLeft(Ref *sender);
	void onCancel(Ref *sender);
	void onBGM(Ref *sender);
	void onPreload(Ref *sender);
	void onVoice(Ref *sender);
};
