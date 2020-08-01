#pragma once
#include "cocos2d.h"

class Piece : public cocos2d::Sprite
{
public:

	enum Type
	{
		X,
		O,
		EMPTY
	};

private:
	
	Type			m_type;

	cocos2d::Vec2	m_gridPosition;

public:

	static Piece*	createWithSpriteFrame(cocos2d::SpriteFrame *i_spriteFrame);
	static Piece*	createWithSpriteFrameName(const std::string& i_spriteFrameName);

	Type			getPieceType() const;
	void			setPieceType(const Type i_type);

	void			setGridPosition(const cocos2d::Vec2 i_pos);
	cocos2d::Vec2	getGridPosition() const;

};