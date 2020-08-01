#include "AppDelegate.h"
#include "scene/MainMenuScene.h"

#define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(1136, 768);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AppDelegate::AppDelegate()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AppDelegate::initGLContextAttrs()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
    GLContextAttrs glContextAttrs = {0, 0, 0, 0, 0, 8, 0};

    GLView::setGLContextAttrs(glContextAttrs);
#else
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };

	GLView::setGLContextAttrs(glContextAttrs);
#endif
}

static int register_all_packages()
{
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool AppDelegate::applicationDidFinishLaunching() 
{
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("TienLenOffline", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height),true);
#else
        glview = GLViewImpl::create("TienLenOffline");
#endif
        director->setOpenGLView(glview);
    }

	director->setDisplayStats(true);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // set FPS. the default value is 1.0/60 if you don't call this
    //director->setAnimationInterval(1.0f / 60);
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Set the design resolution
	//
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
  
    register_all_packages();
	
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("data.plist");
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UserDefault::getInstance()->setIntegerForKey("aitype", 0);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    auto scene = MainMenuScene::createScene();
    director->runWithScene(scene);

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.

void AppDelegate::applicationDidEnterBackground() 
{
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// this function will be called when the app is active again

void AppDelegate::applicationWillEnterForeground() 
{
    Director::getInstance()->startAnimation();
#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
