#pragma once
#include "cocos2d.h"
#include "Piece.h"


class BaseAI
{
public:

	BaseAI(std::vector<std::vector<Piece*>> i_grid);
	
	BaseAI();

	~BaseAI();

public:
	
	virtual cocos2d::Vec2				perform() = 0;

	virtual std::vector<cocos2d::Vec2>	getLegalMoves();

	virtual bool						isGridFull();

protected:

	std::vector<std::vector<Piece*>>	m_grid;

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class KidAI : public BaseAI 
{

public:
	
	KidAI(std::vector<std::vector<Piece*>> i_grid);

	virtual cocos2d::Vec2 perform() override;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SmartAI : public BaseAI
{
private:
	
	int							getScore();
	int							getScore2();

	int							minMaxWithAlphaBeta(int i_depth, bool i_isMaximizingPlayer, int i_alpha, int i_belta);

	int							minMaxWithAlphaBeta2(int i_depth, bool i_isMaximizingPlayer, int i_alpha, int i_belta);

	int							m_maxDepth = -1;

public:

	SmartAI(std::vector<std::vector<Piece*>> i_grid);

	virtual cocos2d::Vec2 perform() override;

	virtual void setMaxDepth(const int i_maxDepth);
};