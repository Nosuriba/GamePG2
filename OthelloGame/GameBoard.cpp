#include <DxLib.h>
#include "PieceST.h"
#include "GameBoard.h"
#include "GamePiece.h"
#include "MouseCtl.h"
#include "Player.h"

#define PIECE_SIZE		(64)
#define BOARD_OFFSET_X	((PIECE_SIZE * 2) + (PIECE_SIZE / 4))
#define BOARD_OFFSET_Y	(PIECE_SIZE)
#define DEF_BOARD_CNT	(8)
#define BOARD_SIZE		(PIECE_SIZE * DEF_BOARD_CNT)

// コマの反転間隔
#define REVERSE_INV_CNT (20)

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
	pPos	 = { 0,0 };
	invCnt	 = 0;
	// ピースを格納するためのサイズを取得している 
	pieceData.resize(vec.y * vec.x);
	data.resize(vec.y);
	for (unsigned int i = 0; i < data.size(); i++)
	{
		data[i] = &pieceData[i * vec.x];
	}
	return true;
}

auto GameBoard::AddObjList(piece_shared && objPtr)
{
	pieceList.push_back(objPtr);
	auto itr = pieceList.end();
	itr--;

	return itr;
}

// 画面サイズをクリックした座標に変換している 
Vector2 GameBoard::ChangeScrToPos(const Vector2& pPos)
{
	return Vector2((pPos.x - BOARD_OFFSET_X), (pPos.y - BOARD_OFFSET_Y));
}

// データサイズを画面サイズに変換している
Vector2 GameBoard::ChangeTblToScr(const Vector2& pNum)
{
	return Vector2((pNum.x * PIECE_SIZE) + BOARD_OFFSET_X, (pNum.y * PIECE_SIZE) + BOARD_OFFSET_Y);
}

void GameBoard::PutPieceField(void)
{
	// ピースが置ける位置の描画をしている 
	for (auto pNum : putPieceTbl)
	{
		DrawBox(ChangeTblToScr(pNum) + 1, ChangeTblToScr(pNum) + Vector2(PIECE_SIZE, PIECE_SIZE) - 1, 0xc8c800, true);
	}
}

Vector2 GameBoard::GetDataSize(void)
{
	return Vector2((pieceData.size() / data.size()), data.size());
}

void GameBoard::SetPiece(int x, int y, PIECE_ST state)
{
	// ピースの配置位置を設定している 
	pPos = ChangeTblToScr(Vector2(x, y));
	auto tmp = AddObjList(std::make_shared<GamePiece>(pPos, Vector2(0,0), state));
	data[y][x] = (*tmp);
}

bool GameBoard::SetPiece(const Vector2& vec, PIECE_ST id)
{
	bool rtnFlag = false;
	Vector2 pNum = ChangeScrToPos(vec);
	// クリックした位置に盤面上であるかの確認を行っている 
	if ((pNum >= Vector2(0, 0)) & (pNum < Vector2((data.size() * PIECE_SIZE), (data.size() * PIECE_SIZE))))
	{
		pNum /= PIECE_SIZE;
		pPos = ChangeTblToScr(pNum);
		if (data[pNum.y][pNum.x].expired())
		{
			rtnFlag = true;
			auto tmp = AddObjList(std::make_shared<GamePiece>(pPos, Vector2(0,0), id));
			data[pNum.y][pNum.x] = (*tmp);
		}
	}
	return rtnFlag;
}

void GameBoard::SetPieceCnt(PutPiece piece)
{
	this->piece = piece;
	pieceList.clear();
}

PutPiece GameBoard::GetPieceCnt(void)
{
	return piece;
}

// リザルト画面でピースの並び替えを行うためのもの
void GameBoard::ResultPiece(PutPiece piece)
{
	pPos = {0,0};

	// 黒ピースの並び替えを行っている 
	for (int b = 0; b < piece.b; b++)
	{
		if (data[b / data.size()][b % data.size()].expired())
		{
			pPos = ChangeTblToScr(Vector2(b % data.size(), b / data.size()));
			auto tmp = AddObjList(std::make_shared<GamePiece>(pPos, Vector2(0,0), PIECE_ST::B));
			data[b / data.size()][b % data.size()] = (*tmp);
		}
	}
	// 白ピースの並び替えを行っている
	for (int w = piece.b; w < piece.b + piece.w; w++)
	{
		if (data[(w / data.size())][w % data.size()].expired())
		{
			pPos = ChangeTblToScr(Vector2(w % data.size(), w / data.size()));
			auto tmp = AddObjList(std::make_shared<GamePiece>(pPos, Vector2(0,0), PIECE_ST::W));
			data[(w / data.size())][w % data.size()] = (*tmp);
		}
	}
}

void GameBoard::SetReverse(const Vector2& vec, PIECE_ST id)
{
	Vector2 pNum	= ChangeScrToPos(vec);
	Vector2 rNum	= { 0,0 };
	int reverseCnt  = 0;

	if (pNum >= Vector2(0, 0) & pNum < Vector2(data.size() * PIECE_SIZE, data.size() * PIECE_SIZE))
	{
		pNum /= PIECE_SIZE;
		for (auto rPos : reverseTbl)
		{
			while (!data[pNum.y + rNum.y][pNum.x + rNum.x].expired())
			{
				rNum += rPos;
				if (!data[pNum.y + rNum.y][pNum.x + rNum.x].expired())
				{
					// 置いたピースと違う色を見つけた場合、反転を行う
					if (data[pNum.y + rNum.y][pNum.x + rNum.x].lock()->GetState() != id)
					{
						reverseCnt++;
						data[pNum.y + rNum.y][pNum.x + rNum.x].lock()->SetState(id, reverseCnt * REVERSE_INV_CNT);
					}
					else
					{
						break;
					}
				}
				else
				{
					break;
				}
			}
			GameBoard::SetInvCnt(reverseCnt * REVERSE_INV_CNT);
			reverseCnt = 0;
			rNum = { 0,0 };
		}
		reverseTbl.clear();
	}
}

bool GameBoard::CheckReverse(const Vector2& vec, PIECE_ST id)
{
	bool rtnFlag = false;
	Vector2 pNum = ChangeScrToPos(vec);

	// クリックした位置に盤面上であるかの確認を行っている
	if (pNum >= Vector2(0, 0) & pNum < Vector2(data.size() * PIECE_SIZE, data.size() * PIECE_SIZE))
	{
		pNum /= PIECE_SIZE;
		if (data[pNum.y][pNum.x].expired())
		{
			for (auto ckPos : pCheckTbl)
			{
				if (CheckReverse(ckPos, pNum, id))
				{
					rtnFlag = true;
				}
			}
		}
	}
	return rtnFlag;
}

bool GameBoard::CheckReverse(const Vector2& ckPos, const Vector2& pNum, PIECE_ST id)
{
	bool	rtnFlag = false;
	Vector2 ckNum = pNum;

	if (pNum + ckPos >= Vector2(0, 0) & pNum + ckPos < Vector2(data.size(), data.size()))
	{
		if (!data[pNum.y + ckPos.y][pNum.x + ckPos.x].expired())
		{
			if (data[pNum.y + ckPos.y][pNum.x + ckPos.x].lock()->GetState() != id)
			{
				while (!rtnFlag)
				{
					ckNum += ckPos;
					if (ckNum >= Vector2(0, 0) & ckNum < Vector2(data.size(), data.size()))
					{
						if (!data[ckNum.y][ckNum.x].expired())
						{
							if (data[ckNum.y][ckNum.x].lock()->GetState() == id)
							{
								rtnFlag = true;
								reverseTbl.push_back(ckPos);
							}
						}
						else
						{
							break;
						}
					}
					else
					{
						break;
					}
				}
			}
		}
	}
	return rtnFlag;
}

void GameBoard::MakePutPieceField(PIECE_ST id)
{
	for (unsigned int y = 0; y < data.size(); y++)
	{
		for (unsigned int x = 0; x < data.size(); x++)
		{
			if (data[y][x].expired())
			{
				for (auto ckPos : pCheckTbl)
				{
					if (CheckReverse(ckPos, Vector2(x, y), id))
					{
						// ピースの置ける位置の登録
						putPieceTbl.push_back(Vector2(x, y));
					}
				}
			}
		}
	}
	/* 反転できる場所を検索した時に反転する位置の登録をする必要がないので
	   ここでクリアをしている */
	reverseTbl.clear();
}

bool GameBoard::CheckPutPiece(void)
{
	return (putPieceTbl.size() > 0);
}

void GameBoard::PutPieceClear(void)
{
	putPieceTbl.clear();
}

PIECE_ST GameBoard::CheckPutPieceST(int x, int y)
{
	// 盤面にピースが配置されていた時、ピースの色を取得するようにしている 
	if (!data[y][x].expired())
	{
		if (data[y][x].lock()->GetState() == PIECE_ST::W)
		{
			return PIECE_ST::W;
		}
		else if (data[y][x].lock()->GetState() == PIECE_ST::B)
		{
			return PIECE_ST::B;
		}
		else{}
	}
	return PIECE_ST::NON;
}

std::list<Vector2> GameBoard::GetPieceTbl()
{
	return putPieceTbl;
}

void GameBoard::SetInvCnt(int reverseCnt)
{
	// コマの反転間隔が一番長い方を渡している
	invCnt = (invCnt > reverseCnt ? invCnt : reverseCnt);
}

bool GameBoard::InvFlag(void)
{
	if (invCnt < 0)
	{
		return true;
	}
	return false;
}

void GameBoard::Update(void)
{
	if (invCnt < 0)
	{
		return;
	}
	invCnt--;
}

void GameBoard::Draw()
{
	Vector2 sPos = { BOARD_OFFSET_X, BOARD_OFFSET_Y };
	Vector2 ePos = { BOARD_SIZE + BOARD_OFFSET_X, BOARD_SIZE + PIECE_SIZE };
	
	// 盤面の描画 
	DrawBox(sPos, ePos, 0x107010, true);

	sPos = { BOARD_OFFSET_X, BOARD_OFFSET_Y };
	ePos = { BOARD_SIZE + BOARD_OFFSET_X, BOARD_SIZE };

	// グリッドの描画 
	for (unsigned int y = 0; y <= DEF_BOARD_CNT + 1; y++)
	{
		sPos.y = PIECE_SIZE * y + BOARD_OFFSET_Y;
		ePos.y = PIECE_SIZE * y + BOARD_OFFSET_Y;
		DrawLine(sPos, ePos, 0xaaaaaa, 2);
	}

	sPos = { BOARD_OFFSET_X, BOARD_OFFSET_Y };
	ePos = { BOARD_SIZE + BOARD_OFFSET_X, BOARD_SIZE + PIECE_SIZE };
	for (unsigned int x = 0; x <= DEF_BOARD_CNT; x++)
	{
		sPos.x = (PIECE_SIZE * x) + BOARD_OFFSET_X;
		ePos.x = (PIECE_SIZE * x) + BOARD_OFFSET_X;
		DrawLine(sPos, ePos, 0xaaaaaa, 2);
	}

	if (InvFlag())
	{
		// ピースの置ける位置の描画
		PutPieceField();
	}
	else
	{
		// ピースの置いた位置の描画
		DrawBox(pPos, pPos + Vector2(PIECE_SIZE, PIECE_SIZE), 0x48d1cc, true);
	}

	// ピースの描画 
	for (auto itr : pieceList)
	{
		(*itr).Update();
		(*itr).Draw();
	}
}

int DrawLine(Vector2 sPos, Vector2 ePos, unsigned int color, int thickNess)
{
	DxLib::DrawLine(sPos.x, sPos.y, ePos.x, ePos.y, color, thickNess);
	return 0;
}