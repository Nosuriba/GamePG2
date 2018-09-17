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

auto GameBoard::AddObjList(player_ptr && plPtr)
{
	playerList.push_back(plPtr);
	auto itr = playerList.end();
	itr--;

	return itr;

}

void GameBoard::Update(const MouseCtl& mouseCtl)
{
	if (mouseCtl.GetButton()[PUSH_NOW] & (~mouseCtl.GetButton()[PUSH_OLD]) & MOUSE_INPUT_LEFT)
	{
		Vector2 mPos = { (mouseCtl.GetPoint().x - BOARD_OFFSET_X),
						 (mouseCtl.GetPoint().y - BOARD_OFFSET_Y) };

		/* 取得したマウス座標が、ボード座標の範囲外でない時に
		   ピースデータを情報を取得するための処理を行う		 */
		if ((mPos >= Vector2(0,0)) & (mPos < Vector2((data.size() * PIECE_SIZE), (data.size() * PIECE_SIZE))))
		{
			/* ピースを格納する配列の位置と、ピースを描画する位置座標を設定している */
			mPos /= PIECE_SIZE;
			Vector2 pPos = { mPos.x * PIECE_SIZE, mPos.y * PIECE_SIZE };
			if (data[mPos.y][mPos.x].expired())
			{
				auto tmp = AddObjList(std::make_shared<GamePiece>(pPos, Vector2(PIECE_OFFSET_X, PIECE_OFFSET_Y)));
				data[mPos.y][mPos.x] = (*tmp);
				
				if (playerList.size() == 0)
				{
					auto pl = AddObjList(std::make_shared<Player>());
				}
				/* プレイヤーが順番通りに置けているかの処理 */
				for (auto itr : playerList)
				{
					itr->registNum();
					if (itr->playerNum() % 2 == 0)
					{
						data[mPos.y][mPos.x].lock()->SetState(PIECE_W);
					}
					else
					{
						data[mPos.y][mPos.x].lock()->SetState(PIECE_B);
					}
				}	
			}
			else
			{
				data[mPos.y][mPos.x].lock()->SetReverse();
			}
		}
	}
}

void GameBoard::Draw()
{
	Vector2 sPos = { BOARD_OFFSET_X, BOARD_OFFSET_Y };
	Vector2 ePos = { BOARD_SIZE + BOARD_OFFSET_X, BOARD_SIZE + PIECE_SIZE };

	/* 盤面の描画をしている */
	DrawBox(sPos, ePos, 0x104010, true);

	sPos = { BOARD_OFFSET_X, BOARD_OFFSET_Y };
	ePos = { BOARD_SIZE + BOARD_OFFSET_X, BOARD_SIZE };

	/* グリッドの描画をしている*/
	for (unsigned int y = 0; y <= DEF_BOARD_CNT + 1; y++)
	{
		sPos.y = PIECE_SIZE * y;
		ePos.y = PIECE_SIZE * y;
		DrawLine(sPos, ePos, 0xcccccc, 1);
	}

	sPos = { BOARD_OFFSET_X, BOARD_OFFSET_Y };
	ePos = { BOARD_SIZE + BOARD_OFFSET_X, BOARD_SIZE + PIECE_SIZE};

	/* 線の位置修正を行っておく*/
	for (unsigned int x = 0; x <= DEF_BOARD_CNT; x++)
	{
		sPos.x = (PIECE_SIZE * x) + BOARD_OFFSET_X;
		ePos.x = (PIECE_SIZE * x) + BOARD_OFFSET_X;
		DrawLine(sPos, ePos, 0xcccccc, 1);
	}

	for (auto itr : pieceList)
	{
		itr->Draw();
	}

	for (auto itr : playerList)
	{
		DrawExtendFormatString(300, 0, 2, 2, 0x00ff00, "%d", itr->playerNum());
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
