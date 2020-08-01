#include "BaseScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool BaseScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_orgin = Director::getInstance()->getVisibleOrigin();
   
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BaseScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

