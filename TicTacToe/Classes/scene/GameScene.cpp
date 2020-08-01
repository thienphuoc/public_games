#include "GameScene.h"
#include "MainMenuScene.h"

#include "SimpleAudioEngine.h"
#include "game/BaseAI.h"
#include "ui/CocosGUI.h"
#include "layer/ResultLayer.h"

USING_NS_CC;
using namespace ui;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Scene* GameScene::createScene()
{
    return GameScene::create();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool GameScene::init()
{
    if ( !BaseScene::init() )
    {
        return false;
    }

	GameScene::initGUI();

	GameScene::initGrid();

	GameScene::initEvents();

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameScene::initGUI()
{
	auto background = Sprite::createWithSpriteFrameName("background.png");
	background->setPosition(m_orgin + m_visibleSize / 2);
	this->addChild(background);

	background->setOpacity(0);
	background->runAction(FadeIn::create(0.5f + 0.25f));

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto backButton = ui::Button::create("back_button.png", "back_button.png", "back_button.png", ui::Widget::TextureResType::PLIST);
	backButton->setPosition(m_orgin + m_visibleSize - backButton->getContentSize());
	backButton->addClickEventListener([](cocos2d::Ref*) {
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, MainMenuScene::createScene()));
	});
	backButton->setPressedActionEnabled(true);
	this->addChild(backButton);

	backButton->setOpacity(0);
	backButton->runAction(FadeIn::create(0.5f + 0.25f));

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	const int k_checkboxNum = 3;
	const int k_aiType		= UserDefault::getInstance()->getIntegerForKey("aitype", 0);

	for (size_t i = 0; i < k_checkboxNum; i++)
	{
		auto checkbox = CheckBox::create("item_bg_02.png","item_bg_02.png", "item_bg_01.png","item_bg_01.png","item_bg_01.png", ui::Widget::TextureResType::PLIST);
		checkbox->setPosition(Vec2(m_orgin.x - checkbox->getContentSize().width*2.0f,(768.0f - 267.5f) - i*checkbox->getContentSize().height*1.2f));
		checkbox->setName(StringUtils::format("checkbox%02d", i + 1));
		checkbox->setSelected(i == k_aiType);
		checkbox->addEventListener([=](Ref* i_sender, CheckBox::EventType i_type)
		{
			switch (i_type)
			{
			case cocos2d::ui::CheckBox::EventType::SELECTED:
			{
				for (size_t j = 0; j < k_checkboxNum; j++)
				{
					if (j == i) continue;

					//if A checked -> B,C,D must uncheck
					((cocos2d::ui::CheckBox*)this->getChildByName(cocos2d::StringUtils::format("checkbox%02d", j + 1)))->setSelected(false);
				}

				UserDefault::getInstance()->setIntegerForKey("aitype", i);

				Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GameScene::createScene()));

				break;
			}
			case cocos2d::ui::CheckBox::EventType::UNSELECTED:
			{
				((cocos2d::ui::CheckBox*)this->getChildByName(cocos2d::StringUtils::format("checkbox%02d", i + 1)))->setSelected(true);
				break;
			}
			default:
				break;
			}

		});
		this->addChild(checkbox);

		checkbox->setOpacity(0);
		checkbox->runAction(Spawn::createWithTwoActions(MoveTo::create(0.5f+i*0.25f, Vec2(Vec2(m_orgin.x + checkbox->getContentSize().width*0.55f, (768.0f - 267.5f) - i * checkbox->getContentSize().height*1.2f))), FadeIn::create(0.5f + i * 0.25f)));

		auto title = Label::createWithTTF(i==0?"Kid AI":(i==1?"Audult AI":("Wise Man AI")), "fonts/SVN-Nexa Light.ttf", 21.0f);
		title->setPosition(checkbox->getContentSize() / 2);
		checkbox->addChild(title);

	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameScene::initGrid()
{
	const Vec2 k_startPos = Vec2(400.0f, 768.0f - 219.0f);

	for (int i = 0; i < ROW_NUM; i++)
	{
		std::vector<Piece*> gridRow;

		for (int j = 0; j < COL_NUM; j++)
		{
			Piece* emptyPiece = Piece::createWithSpriteFrameName("empty_piece.png");
			emptyPiece->setGridPosition(Vec2(i, j));
			emptyPiece->setPieceType(Piece::Type::EMPTY);
			//emptyPiece->setColor(Color3B::RED);
			emptyPiece->setPosition(k_startPos + Vec2(j * 165, -i * 163));
			addChild(emptyPiece);
			gridRow.push_back(emptyPiece);

			emptyPiece->setOpacity(0);
			emptyPiece->runAction(Sequence::createWithTwoActions(DelayTime::create(0.75f),FadeIn::create(0.0f)));
		}

		m_grid.push_back(gridRow);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameScene::initEvents()
{
	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool GameScene::onTouchBegan(cocos2d::Touch * i_touch, cocos2d::Event * i_event)
{
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameScene::onTouchMoved(cocos2d::Touch * i_touch, cocos2d::Event * i_event)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameScene::onTouchEnded(cocos2d::Touch * i_touch, cocos2d::Event * i_event)
{
	if (m_gameTurn == GAMETURN::PALYER)
	{
		checkAndPlacePiece(i_touch->getLocation());
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameScene::menuCloseCallback(Ref* i_pSender)
{
	BaseScene::menuCloseCallback(i_pSender);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool GameScene::checkWin(Piece::Type i_type)
{
	for (int i = 0; i < ROW_NUM; i++)
	{
		for (int j = 0; j < COL_NUM; j++)
		{
			if (m_grid[i][j]->getPieceType() == i_type)
			{
				int cases[4] = { 0,0,0,0 };

				for (int k = 1; k < WINNABLE_LENGTH; k++)
				{
					cases[0] = (i + k < ROW_NUM && j + k < COL_NUM && m_grid[i + k][j + k]->getPieceType() == i_type && cases[0] >= 0) ? 1 : -1;

					cases[2] = (j + k < ROW_NUM && m_grid[i][j + k]->getPieceType() == i_type && cases[2] >= 0) ? 1 : -1;

					cases[3] = (i + k < ROW_NUM && m_grid[i + k][j]->getPieceType() == i_type && cases[3] >= 0) ? 1 : -1;

					cases[1] = (i - k >= 0 && j + k < COL_NUM && m_grid[i - k][j + k]->getPieceType() == i_type && cases[1] >= 0) ? 1 : -1;
				}

				for (int case_i = 0; case_i < 4; case_i++)
				{
					if (cases[case_i] == 1)
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool GameScene::checkAndPlacePiece(cocos2d::Vec2 i_position)
{
	for (int i = 0; i < ROW_NUM; i++)
	{
		for (int j = 0; j < COL_NUM; j++)
		{
			if (m_grid[i][j]->getPieceType() == Piece::Type::EMPTY && m_grid[i][j]->getBoundingBox().containsPoint(i_position))
			{
				m_grid[i][j]->setSpriteFrame(Piece::createWithSpriteFrameName("x.png")->getSpriteFrame());
				m_grid[i][j]->setPieceType(Piece::Type::X);
				
				if (checkWin(Piece::Type::X)) 
				{
					cocos2d::log("player_win!");

					m_gameTurn = GAMETURN::NONE;

					m_grid[i][j]->runAction(Sequence::createWithTwoActions(Repeat::create(Sequence::createWithTwoActions(ScaleTo::create(0.25f, 0.8f), ScaleTo::create(0.25f, 1.0f)), 2), CallFunc::create([=]() {

						GameScene::showResult(E_RESULT::WIN);
						//Director::getInstance()->replaceScene(GameScene::createScene());

					})));
				}
				else
				{
					const int k_aiType = UserDefault::getInstance()->getIntegerForKey("aitype", 0);

					GameScene::performAI((AITYPE)k_aiType);
				}

				return true;
			}
		}
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool GameScene::isDraw()
{
	for (int i = 0; i < ROW_NUM; i++)
	{
		for (int j = 0; j < COL_NUM; j++)
		{
			if (m_grid[i][j]->getPieceType() == Piece::Type::EMPTY)
			{
				return false;
			}
		}
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameScene::performAI(AITYPE i_type)
{
	if (isDraw())
	{
		GameScene::showResult(E_RESULT::DRAW);
		return;
	}

	Vec2 bestMove = INVALID_POS;

	if (i_type == AITYPE::KID)
	{
		KidAI ai = KidAI(m_grid);
		bestMove = ai.perform();
	}
	else if (i_type == AITYPE::ADULT)
	{
		SmartAI smartAI = SmartAI(m_grid);
		smartAI.setMaxDepth(2);
		bestMove = smartAI.perform();
	}
	else if (i_type == AITYPE::WISEMAN)
	{
		SmartAI smartAI = SmartAI(m_grid);
		bestMove = smartAI.perform();
	}

	//make sure that we found a valid position.
	if (bestMove == INVALID_POS)
	{
		return;
	}

	m_gameTurn = GAMETURN::AI;

	m_grid[bestMove.x][bestMove.y]->setSpriteFrame(Piece::createWithSpriteFrameName("o.png")->getSpriteFrame());
	m_grid[bestMove.x][bestMove.y]->setPieceType(Piece::Type::O);

	if (checkWin(Piece::Type::O))
	{
		//cocos2d::log("AI_WIN!");

		m_gameTurn = GAMETURN::NONE;

		m_grid[bestMove.x][bestMove.y]->runAction(Sequence::createWithTwoActions(Repeat::create(Sequence::createWithTwoActions(ScaleTo::create(0.25f, 0.8f), ScaleTo::create(0.25f, 1.0f)), 2), CallFunc::create([=]() {

			GameScene::showResult(E_RESULT::LOSS);
			//Director::getInstance()->replaceScene(GameScene::createScene());

		})));

		return;
	}

	m_gameTurn = GAMETURN::PALYER;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameScene::showResult(E_RESULT i_result)
{
	this->addChild(ResultLayer::createResultLayer(i_result));
}




