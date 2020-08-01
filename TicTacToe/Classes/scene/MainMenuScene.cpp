#include "MainMenuScene.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool MainMenuScene::init()
{
    if (!BaseScene::init() )
    {
        return false;
    }

	auto backgroundColor = LayerColor::create(Color4B::WHITE);
	this->addChild(backgroundColor);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto title = Sprite::createWithSpriteFrameName("tictactoe_title.png");
	title->setPosition(m_orgin + m_visibleSize/2 + Vec2(-title->getContentSize().width*0.25f,title->getContentSize().height));
	this->addChild(title);

	title->setOpacity(0);
	title->runAction(Spawn::createWithTwoActions(MoveBy::create(0.5f, Vec2(title->getContentSize().width / 4, 0)), FadeIn::create(0.6f)));

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto playButton = ui::Button::create("play_button.png", "play_button.png", "play_button.png", ui::Widget::TextureResType::PLIST);
	playButton->setPosition(title->getPosition() - Vec2(0,title->getContentSize().height+playButton->getContentSize().height/2));
	playButton->addClickEventListener([](cocos2d::Ref*) {
	
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GameScene::createScene()));

	});
	playButton->setPressedActionEnabled(true);
	this->addChild(playButton);

	playButton->setOpacity(0);
	playButton->runAction(Spawn::createWithTwoActions(MoveBy::create(0.5f+0.15f, Vec2(title->getContentSize().width / 4, 0)), FadeIn::create(0.6f + 0.15f)));

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainMenuScene::menuCloseCallback(Ref* pSender)
{

}
