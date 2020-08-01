#include "BaseLayer.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace ui;

bool BaseLayer::initWithColor(cocos2d::Color4B i_color)
{
	if (!LayerColor::initWithColor(i_color))
	{
		return false;
	}
	
	m_visibleSize = Director::getInstance()->getVisibleSize();

	m_origin = Director::getInstance()->getVisibleOrigin();

	//lock button.

	m_lockButton = Button::create();
	
	m_lockButton->setAnchorPoint(Point::ZERO);
	
	m_lockButton->setScale9Enabled(true);
	
	m_lockButton->setContentSize(m_visibleSize);

	m_lockButton->setPosition(m_origin);

	this->addChild(m_lockButton,-1);
	
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BaseLayer::setEnableLockTouch(bool i_isVisible)
{
	m_lockButton->setVisible(i_isVisible);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BaseLayer::setLockTouchArea(cocos2d::Rect i_area)
{
	m_lockButton->setPosition(i_area.origin);
	m_lockButton->setContentSize(i_area.size);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BaseLayer::resetLockTouchArea()
{
	m_lockButton->setPosition(m_origin);
	m_lockButton->setContentSize(m_visibleSize);
}
