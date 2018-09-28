#include <DxLib.h>
#include "GameBoard.h"
#include "GamePiece.h"
#include "MouseCtl.h"
#include "Player.h"

#define PIECE_SIZE		(64)
#define BOARD_OFFSET_X	(PIECE_SIZE * 2)
#define BOARD_OFFSET_Y	(PIECE_SIZE)
#define PIECE_OFFSET_X	(BOARD_OFFSET_X + (PIECE_SIZE / 2))
#define PIECE_OFFSET_Y  (BOARD_OFFSET_Y + (PIECE_SIZE / 2))
#define DEF_BOARD_CNT	(8)
/* 盤面のサイズが変わる可能性があるので、この設定に修正が入る可能性がある*/
#define BOARD_SIZE		(PIECE_SIZE * DEF_BOARD_CNT)

GameBoard::GameBoard()
{
	CommonBoard(Vector2(DEF_BOARD_CNT, DEF_BOARD_CNT));
}

GameBoard::GameBoard(Vector2 vec)
{
	CommonBoard(vec);
}

GameBoard::~GameBoard()
{
}

bool GameBoard::CommonBoard(Vector2 vec)
{
	
	pieceData.resize(vec.y * vec.x);
	data.resize(vec.y);
	for (unsigned int i = 0; i < data.size(); i++)
	{
		data[i] = &pieceData[i * vec.x];
	}

	return true;
}

auto GameBoard::AddObjList(piece_ptr && objPtr)
{
	pieceList.push_back(objPtr);
	auto itr = pieceList.end();
	itr--;

	return itr;
}

//auto GameBoard::AddObjList(player_ptr && plPtr)
//{
//	playerList.push_back(plPtr);
//	auto itr = playerList.end();
//	itr--;
//
//	return itr;
//
//}

bool GameBoard::Update(Vector2 vec, int pNum)
{
	Vector2 mPos = { (vec.x - BOARD_OFFSET_X),
					 (vec.y- BOARD_OFFSET_Y) };
	/* クリックした位置がボードの盤面外でなければ、ピースの設置を行う */
	if ((mPos >= Vector2(0,0)) & (mPos < Vector2((data.size() * PIECE_SIZE), (data.size() * PIECE_SIZE))))
	{
		/* ピースを格納するための設定 */
		mPos /= PIECE_SIZE;
		Vector2 pPos = { mPos.x * PIECE_SIZE, mPos.y * PIECE_SIZE };
		if (data[mPos.y][mPos.x].expired())
		{
			auto tmp = AddObjList(std::make_shared<GamePiece>(pPos, Vector2(PIECE_OFFSET_X, PIECE_OFFSET_Y)));
			data[mPos.y][mPos.x] = (*tmp);
				
			/* プレイヤーの番号に対してピースの色を設定している */
			if(pNum == PIECE_C)
			{
				data[mPos.y][mPos.x].lock()->SetState(PIECE_C);
			}
			else if (pNum == PIECE_W)
			{
				data[mPos.y][mPos.x].lock()->SetState(PIECE_W);
			}
			else if (pNum == PIECE_R)
			{
				data[mPos.y][mPos.x].lock()->SetState(PIECE_R);
			}
			else if (pNum == PIECE_B)
			{
				data[mPos.y][mPos.x].lock()->SetState(PIECE_B);
			}
			else
			{
				/* プレイヤーが設定した人数を超えたときの処理 */
				data[mPos.y][mPos.x].lock()->SetState(PIECE_W);
			}
			return true;
		}
		else
		{
			data[mPos.y][mPos.x].lock()->SetReverse();
			return false;
		}
	}
	return false;
}

void GameBoard::Draw()
{
	Vector2 sPos = { BOARD_OFFSET_X, BOARD_OFFSET_Y };
	Vector2 ePos = { BOARD_SIZE + BOARD_OFFSET_X, BOARD_SIZE + PIECE_SIZE };

	/* 盤面の描画 */
	DrawBox(sPos, ePos, 0x104010, true);

	sPos = { BOARD_OFFSET_X, BOARD_OFFSET_Y };
	ePos = { BOARD_SIZE + BOARD_OFFSET_X, BOARD_SIZE };

	/* グリッドの描画 */
	for (unsigned int y = 0; y <= DEF_BOARD_CNT + 1; y++)
	{
		sPos.y = PIECE_SIZE * y;
		ePos.y = PIECE_SIZE * y;
		DrawLine(sPos, ePos, 0xcccccc, 1);
	}

	sPos = { BOARD_OFFSET_X, BOARD_OFFSET_Y };
	ePos = { BOARD_SIZE + BOARD_OFFSET_X, BOARD_SIZE + PIECE_SIZE};

	for (unsigned int x = 0; x <= DEF_BOARD_CNT; x++)
	{
		sPos.x = (PIECE_SIZE * x) + BOARD_OFFSET_X;
		ePos.x = (PIECE_SIZE * x) + BOARD_OFFSET_X;
		DrawLine(sPos, ePos, 0xcccccc, 1);
	}

	/* ピースの描画 */
	for (auto itr : pieceList)
	{
		itr->Draw();
	}
}

void GameBoard::SetPiece(const Vector2& vec, PIECE_ST pState)
{
	Vector2 mPos = { (vec.x - BOARD_OFFSET_X),
					 (vec.y - BOARD_OFFSET_Y) };
	/* クリックした位置がボードの盤面外でなければ、ピースの設置を行う */
	if ((mPos >= Vector2(0, 0)) & (mPos < Vector2((data.size() * PIECE_SIZE), (data.size() * PIECE_SIZE))))
	{
		/* ピースを格納するための設定 */
		mPos /= PIECE_SIZE;
		/* ピース座標の設定*/
		Vector2 pPos = { mPos.x * PIECE_SIZE, mPos.y * PIECE_SIZE };
		if (data[mPos.y][mPos.x].expired())
		{
			auto tmp = AddObjList(std::make_shared<GamePiece>(pPos, Vector2(PIECE_OFFSET_X, PIECE_OFFSET_Y)));
			data[mPos.y][mPos.x] = (*tmp);
			data[mPos.y][mPos.x].lock()->SetState(pState);

			///* プレイヤーの番号に対してピースの色を設定している */
			//if (pNum == PIECE_C)
			//{
			//	data[mPos.y][mPos.x].lock()->SetState(PIECE_C);
			//}
			//else if (pNum == PIECE_W)
			//{
			//	data[mPos.y][mPos.x].lock()->SetState(PIECE_W);
			//}
			//else if (pNum == PIECE_R)
			//{
			//	data[mPos.y][mPos.x].lock()->SetState(PIECE_R);
			//}
			//else if (pNum == PIECE_B)
			//{
			//	data[mPos.y][mPos.x].lock()->SetState(PIECE_B);
			//}
			//else
			//{
			//	/* プレイヤーが設定した人数を超えたときの処理 */
			//	data[mPos.y][mPos.x].lock()->SetState(PIECE_W);
			//}
		}
		else
		{
			data[mPos.y][mPos.x].lock()->SetReverse();
		}
	}
}

int DrawLine(Vector2 sPos, Vector2 ePos, unsigned int color, int thickNess)
{
	DxLib::DrawLine(sPos.x, sPos.y, ePos.x, ePos.y, color, thickNess);
	return 0;
}

int DrawBox(Vector2 sPos, Vector2 ePos, unsigned int color, int fillFlag)
{
	DxLib::DrawBox(sPos.x, sPos.y, ePos.x, ePos.y, color, fillFlag);
	return 0;
}
