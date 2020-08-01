#pragma once

#include "BaseScene.h"
#include "game/Piece.h"

class BaseAI;

class GameScene : public BaseScene
{
public:

	enum GAMETURN
	{
		PALYER,
		AI,
		NONE
	};

	enum AITYPE 
	{
		KID,
		ADULT,
		WISEMAN
	};

    static cocos2d::Scene*	createScene();

    virtual bool			init();

private:

	std::vector<std::vector<Piece*>> m_grid;
	
	GAMETURN						 m_gameTurn = GAMETURN::PALYER;

private:

	void initGUI();

	void initGrid();

	void initEvents();

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);

	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

    void menuCloseCallback(cocos2d::Ref* pSender);
    
	bool checkWin(Piece::Type i_type);

	bool checkAndPlacePiece(cocos2d::Vec2 i_position);

	bool isDraw();

	void performAI(AITYPE i_type);

	void showResult(E_RESULT i_result);

    CREATE_FUNC(GameScene);
};

