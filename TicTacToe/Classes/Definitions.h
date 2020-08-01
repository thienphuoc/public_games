#pragma once

#include "cocos2d.h"

USING_NS_CC;

#define ROW_NUM				3
#define COL_NUM				3
#define WINNABLE_LENGTH		3
#define INVALID_POS			Vec2(-1,-1)
#define INFI				1000

enum class E_RESULT
{
	WIN,
	LOSS,
	DRAW
};