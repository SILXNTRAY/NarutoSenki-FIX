#pragma once
#include "Defines.h"

class CCStrokeLabel : public Node
{
public:
	bool init();

	float getStrokeSize();
	void setStrokeSize(float strokeSize);

	static CCStrokeLabel *create(CCLabelTTF *labelTTF, Color3B fullColor, Color3B StrokeColor, float strokeSize);

private:
	Sprite *m_sprite = nullptr;
	CCLabelTTF *m_label = nullptr;
	Color3B m_fullColor;
	Color3B m_StrokeColor;
	float m_strokeSize;
};
