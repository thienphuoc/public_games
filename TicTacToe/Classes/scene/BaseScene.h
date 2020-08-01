#pragma once

#include "cocos2d.h"
#include "Definitions.h"

class BaseScene : public cocos2d::Scene
{
protected:
	
	cocos2d::Size m_visibleSize;

	cocos2d::Vec2 m_orgin;

public:

    virtual bool init();
    
	virtual void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(BaseScene);
};

