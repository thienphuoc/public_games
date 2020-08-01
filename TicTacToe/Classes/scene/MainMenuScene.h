#pragma once

#include "BaseScene.h"

class MainMenuScene : public BaseScene
{
public:

	static cocos2d::Scene* createScene();

    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(MainMenuScene);
};

