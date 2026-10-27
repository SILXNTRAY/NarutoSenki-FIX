#pragma once
#include "GameMode/GameModeImpl.h"

class ModeMenuButton;

class GameModeLayer : public Layer
{
public:
	static const int kMenuCount = 5;

	bool init();
	void backToMenu(Ref *sender);

	void initModeData();
	bool pushMode(const GameModeData &data);
	void removeMode(const GameModeData &data);
	void selectMode(GameMode mode);

	CREATE_FUNC(GameModeLayer);

private:
	inline bool setSelect(GameMode mode);

	CCLabelTTF *menuLabel = nullptr;

	vector<ModeMenuButton *> menuButtons = vector<ModeMenuButton *>(static_cast<size_t>(GameMode::__Internal_Max_Length));
	vector<GameModeData> modes = vector<GameModeData>(static_cast<size_t>(GameMode::__Internal_Max_Length));
};
