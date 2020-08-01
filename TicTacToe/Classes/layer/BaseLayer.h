#pragma once

#include "cocos2d.h"

#include "ui/CocosGUI.h"

class BaseLayer : public cocos2d::LayerColor
{
public:

	virtual bool initWithColor(cocos2d::Color4B i_color);

	virtual void setEnableLockTouch(bool i_value);
	
	virtual void setLockTouchArea(cocos2d::Rect i_area);
	
	virtual void resetLockTouchArea();

protected:

	cocos2d::Size		m_visibleSize;

	cocos2d::Vec2		m_origin;

	cocos2d::ui::Button *m_lockButton;

};

