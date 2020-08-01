#include "BaseAI.h"
#include "Definitions.h"
#include "Piece.h"

USING_NS_CC;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BaseAI::BaseAI(std::vector<std::vector<Piece*>> i_grid)
:m_grid(i_grid)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BaseAI::BaseAI()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BaseAI::~BaseAI()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<cocos2d::Vec2> BaseAI::getLegalMoves()
{
	std::vector<cocos2d::Vec2> legalMoves;

	for (size_t i = 0; i < ROW_NUM; i++)
	{
		for (size_t j = 0; j < COL_NUM; j++)
		{
			if (m_grid[i][j]->getPieceType() == Piece::Type::EMPTY)
			{
				legalMoves.push_back(Vec2(i, j));
			}
		}
	}

	return legalMoves;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool BaseAI::isGridFull()
{
	for (size_t i = 0; i < ROW_NUM; i++)
	{
		for (size_t j = 0; j < COL_NUM; j++)
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

KidAI::KidAI(std::vector<std::vector<Piece*>> i_grid)
	:BaseAI(i_grid)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

cocos2d::Vec2 KidAI::perform()
{
	const std::vector<cocos2d::Vec2> k_legalMoves = getLegalMoves();

	return k_legalMoves.empty() ? INVALID_POS : k_legalMoves[cocos2d::RandomHelper::random_int(0, (int)k_legalMoves.size() - 1)];
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SmartAI::SmartAI(std::vector<std::vector<Piece*>> i_grid)
	:BaseAI(i_grid)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//win :		get 10 points
//lose:		get -10 points
//draw:		get 0 points.

int SmartAI::getScore()
{
	for (int i = 0; i < ROW_NUM; i++)
	{
		for (int j = 0; j < COL_NUM; j++)
		{
			if (m_grid[i][j]->getPieceType() == Piece::Type::O)
			{
				int cases[4] = { 0,0,0,0 };

				for (int k = 1; k < WINNABLE_LENGTH; k++)
				{
					cases[0] = (i + k < ROW_NUM && j + k < COL_NUM && m_grid[i + k][j + k]->getPieceType() == Piece::Type::O && cases[0] >= 0) ? 1 : -1;

					cases[2] = (j + k < ROW_NUM && m_grid[i][j + k]->getPieceType() == Piece::Type::O && cases[2] >= 0) ? 1 : -1;

					cases[3] = (i + k < ROW_NUM && m_grid[i + k][j]->getPieceType() == Piece::Type::O && cases[3] >= 0) ? 1 : -1;

					cases[1] = (i - k >= 0 && j + k < COL_NUM && m_grid[i - k][j + k]->getPieceType() == Piece::Type::O && cases[1] >= 0) ? 1 : -1;
				}

				for (int case_i = 0; case_i < 4; case_i++)
				{
					if (cases[case_i] == 1)
					{
						return +10;
					}
				}
			}
			else if (m_grid[i][j]->getPieceType() == Piece::Type::X)
			{
				int cases[4] = { 0,0,0,0 };

				for (int k = 1; k < WINNABLE_LENGTH; k++)
				{
					cases[0] = (i + k < ROW_NUM && j + k < COL_NUM && m_grid[i + k][j + k]->getPieceType() == Piece::Type::X && cases[0] >= 0) ? 1 : -1;

					cases[2] = (j + k < ROW_NUM && m_grid[i][j + k]->getPieceType() == Piece::Type::X && cases[2] >= 0) ? 1 : -1;

					cases[3] = (i + k < ROW_NUM && m_grid[i + k][j]->getPieceType() == Piece::Type::X && cases[3] >= 0) ? 1 : -1;

					cases[1] = (i - k >= 0 && j + k < COL_NUM && m_grid[i - k][j + k]->getPieceType() == Piece::Type::X && cases[1] >= 0) ? 1 : -1;
				}

				for (int case_i = 0; case_i < 4; case_i++)
				{
					if (cases[case_i] == 1)
					{
						return -10;
					}
				}
			}
		}
	}

	return 0;
}

int SmartAI::getScore2()
{
	for (int i = 0; i < ROW_NUM; i++)
	{
		for (int j = 0; j < COL_NUM; j++)
		{
			if (m_grid[i][j]->getPieceType() == Piece::Type::O)
			{
				int cases[4] = { 0,0,0,0 };

				for (int k = 1; k < WINNABLE_LENGTH; k++)
				{
					cases[0] = (i + k < ROW_NUM && j + k < COL_NUM && m_grid[i + k][j + k]->getPieceType() == Piece::Type::O && cases[0] >= 0) ? 1 : -1;

					cases[2] = (j + k < ROW_NUM && m_grid[i][j + k]->getPieceType() == Piece::Type::O && cases[2] >= 0) ? 1 : -1;

					cases[3] = (i + k < ROW_NUM && m_grid[i + k][j]->getPieceType() == Piece::Type::O && cases[3] >= 0) ? 1 : -1;

					cases[1] = (i - k >= 0 && j + k < COL_NUM && m_grid[i - k][j + k]->getPieceType() == Piece::Type::O && cases[1] >= 0) ? 1 : -1;
				}

				for (int case_i = 0; case_i < 4; case_i++)
				{
					if (cases[case_i] == 1)
					{
						return +10;
					}
				}
			}
			else if (m_grid[i][j]->getPieceType() == Piece::Type::X)
			{
				int cases[4] = { 0,0,0,0 };

				for (int k = 1; k < WINNABLE_LENGTH; k++)
				{
					cases[0] = (i + k < ROW_NUM && j + k < COL_NUM && m_grid[i + k][j + k]->getPieceType() == Piece::Type::X && cases[0] >= 0) ? 1 : -1;

					cases[2] = (j + k < ROW_NUM && m_grid[i][j + k]->getPieceType() == Piece::Type::X && cases[2] >= 0) ? 1 : -1;

					cases[3] = (i + k < ROW_NUM && m_grid[i + k][j]->getPieceType() == Piece::Type::X && cases[3] >= 0) ? 1 : -1;

					cases[1] = (i - k >= 0 && j + k < COL_NUM && m_grid[i - k][j + k]->getPieceType() == Piece::Type::X && cases[1] >= 0) ? 1 : -1;
				}

				for (int case_i = 0; case_i < 4; case_i++)
				{
					if (cases[case_i] == 1)
					{
						return -10;
					}
				}
			}
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int SmartAI::minMaxWithAlphaBeta(int i_depth, bool i_isComputerTurn, int i_alpha, int i_beta)
{
	static int abc = 0;
	int score = getScore();

	cocos2d::log("abc:%d", abc);

	//if node is a leaf node :
	//return value of the node

	if (score == 10) 
	{
		abc += 1;
		return score - i_depth;
	}
	
	if (score == -10) 
	{
		abc += 1;
		return score + i_depth;
	}

	if (isGridFull() || (m_maxDepth != -1 && i_depth >= m_maxDepth ))
	{
		abc += 1;
		return 0;
	}

	if (i_isComputerTurn)
	{
		int bestVal = -INFI;

		const std::vector<cocos2d::Vec2> k_legalMoves = getLegalMoves() ;

		for (int i = 0; i < k_legalMoves.size(); i++)
		{
			m_grid[k_legalMoves[i].x][k_legalMoves[i].y]->setPieceType(Piece::Type::O);

			const int k_value = minMaxWithAlphaBeta(i_depth + 1, false, i_alpha, i_beta);

			bestVal = std::max(bestVal, k_value);
			
			i_alpha = std::max(i_alpha, bestVal);

			//revert
			m_grid[k_legalMoves[i].x][k_legalMoves[i].y]->setPieceType(Piece::Type::EMPTY);

			if (i_beta <= i_alpha)
			{
				break;
			}
		}

		return bestVal;
	}
	else 
	{
		int bestVal = +INFI;

		const std::vector<cocos2d::Vec2> k_legalMoves = getLegalMoves();

		for (int i = 0; i < k_legalMoves.size(); i++)
		{
			m_grid[k_legalMoves[i].x][k_legalMoves[i].y]->setPieceType(Piece::Type::X);

			const int k_value = minMaxWithAlphaBeta(i_depth + 1, true, i_alpha, i_beta);

			bestVal = std::min(bestVal, k_value);

			i_beta = std::min(bestVal, i_beta);

			//revert
			m_grid[k_legalMoves[i].x][k_legalMoves[i].y]->setPieceType(Piece::Type::EMPTY);

			if (i_beta <= i_alpha)
			{
				break;
			}
		}

		return bestVal;
	}
	
}

int SmartAI::minMaxWithAlphaBeta2(int i_depth, bool i_isMaximizingPlayer, int i_alpha, int i_beta)
{
	int score = getScore();

	//if node is a leaf node :
	//return value of the node

	if (score == 10)
	{
		return score - i_depth;
	}

	if (score == -10)
	{
		return score + i_depth;
	}

	if (isGridFull() || (m_maxDepth != -1 && i_depth >= m_maxDepth))
	{
		return 0;
	}

	if (i_isMaximizingPlayer)
	{
		int bestVal = -INFI;

		const std::vector<cocos2d::Vec2> k_legalMoves = getLegalMoves();

		for (int i = 0; i < k_legalMoves.size(); i++)
		{
			m_grid[k_legalMoves[i].x][k_legalMoves[i].y]->setPieceType(Piece::Type::O);

			const int k_value = minMaxWithAlphaBeta(i_depth + 1, false, i_alpha, i_beta);

			bestVal = std::max(bestVal, k_value);

			i_alpha = std::max(i_alpha, bestVal);

			//revert
			m_grid[k_legalMoves[i].x][k_legalMoves[i].y]->setPieceType(Piece::Type::EMPTY);

			if (i_beta <= i_alpha)
			{
				break;
			}
		}

		return bestVal;
	}
	else
	{
		int bestVal = +INFI;

		const std::vector<cocos2d::Vec2> k_legalMoves = getLegalMoves();

		for (int i = 0; i < k_legalMoves.size(); i++)
		{
			m_grid[k_legalMoves[i].x][k_legalMoves[i].y]->setPieceType(Piece::Type::X);

			const int k_value = minMaxWithAlphaBeta(i_depth + 1, true, i_alpha, i_beta);

			bestVal = std::min(bestVal, k_value);

			i_beta = std::min(bestVal, i_beta);

			//revert
			m_grid[k_legalMoves[i].x][k_legalMoves[i].y]->setPieceType(Piece::Type::EMPTY);

			if (i_beta <= i_alpha)
			{
				break;
			}
		}

		return bestVal;
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

cocos2d::Vec2 SmartAI::perform()
{
	int bestVal		= -INFI;
	int alpha		= -INFI;
	int beta		=  INFI;

	const std::vector<cocos2d::Vec2> k_legalMoves = getLegalMoves();
	
	Vec2 bestMove = INVALID_POS;

	for (int i = 0; i < k_legalMoves.size(); i++)
	{
		m_grid[k_legalMoves[i].x][k_legalMoves[i].y]->setPieceType(Piece::Type::O);
		
		const int k_moveVal = minMaxWithAlphaBeta(0, false, alpha, beta);

		//revert
		m_grid[k_legalMoves[i].x][k_legalMoves[i].y]->setPieceType(Piece::Type::EMPTY);

		if (k_moveVal > bestVal)
		{
			bestMove = k_legalMoves[i];
			bestVal = k_moveVal;
		}
	}

	return bestMove;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SmartAI::setMaxDepth(const int i_maxDepth)
{
	m_maxDepth = i_maxDepth;
}
