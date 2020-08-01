#include "ResultLayer.h"
#include "ui/CocosGUI.h"

#include "scene/GameScene.h"

USING_NS_CC;

ResultLayer * ResultLayer::createResultLayer(E_RESULT i_result)
{
	ResultLayer *ret = new (std::nothrow) ResultLayer();

	if (ret && ret->init(i_result))
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);

		return nullptr;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool ResultLayer::init(E_RESULT i_result)
{
    if (!BaseLayer::initWithColor(Color4B::WHITE))
    {
        return false;
    }
	
	BaseLayer::setEnableLockTouch(true);

	this->setOpacity(0.9f*255.0f);

	const std::string k_msg = (E_RESULT::DRAW == i_result ? "Draw!" : (E_RESULT::WIN == i_result ? "You Win!" : "You Loss!"));

	auto title = Label::createWithTTF(k_msg, "fonts/QUINHON.TTF", 90.0f);
	title->setTextColor(Color4B(10,11,107,255));
	title->setPosition(m_origin + m_visibleSize/2-Vec2(title->getContentSize().width*0.25f,0));
	this->addChild(title);

	auto retryButton = ui::Button::create("retry_button.png", "retry_button.png", "retry_button.png", ui::Widget::TextureResType::PLIST);
	retryButton->setPosition(title->getPosition() - Vec2(0, title->getContentSize().height + retryButton->getContentSize().height / 2));
	retryButton->setPressedActionEnabled(true);
	retryButton->addClickEventListener([](cocos2d::Ref*) {

		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GameScene::createScene()));

	});
	this->addChild(retryButton);


	title->setOpacity(0);
	retryButton->setOpacity(0);

	title->runAction(Spawn::createWithTwoActions(MoveBy::create(0.4f, Vec2(title->getContentSize().width / 4, 0)), FadeIn::create(0.5f)));
	retryButton->runAction(Spawn::createWithTwoActions(MoveBy::create(0.4f + 0.1f, Vec2(title->getContentSize().width / 4, 0)), FadeIn::create(0.5f + 0.1f)));

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ResultLayer::menuCloseCallback(Ref* i_pSender)
{

}
