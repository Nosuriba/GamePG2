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
	return Vector2((pNum.x * PIECE_SIZE), (pNum.y * PIECE_SIZE));
}

void GameBoard::PutPieceField(void)
{
	Vector2 drawOffset = { BOARD_OFFSET_X, BOARD_OFFSET_Y };
	// ピースが置ける位置の描画をしている 
	for (auto pNum : putPieceTbl)
	{
		DrawBox(ChangeTblToScr(pNum) + drawOffset + 1, ChangeTblToScr(pNum) + Vector2(PIECE_SIZE, PIECE_SIZE) + drawOffset - 1, 0xc8c800, true);
	}
	putPieceTbl.clear();
}

Vector2 GameBoard::GetDataSize(void)
{
	return Vector2((pieceData.size() / data.size()), data.size());
}

//void GameBoard::StartPiece(const Vector2& pNum, bool pFlag)
//{
//	int initPieceST = 0;
//	int pWhite = static_cast<int>(PIECE_ST::W);
//	int pBlack = static_cast<int>(PIECE_ST::B);
//	int pMax = static_cast<int>(PIECE_ST::MAX);
//	for (int y = 0; y <= 1; y++)
//	{
//		for (int x = 0; x <= 1; x++)
//		{
//			if (data[pNum.y + y][pNum.x + x].expired())
//			{
//				// 最初に配置されるピースの状態を設定している 
//				if (pFlag)
//				{
//					initPieceST = (((x + y) % pMax) < 1
//								? initPieceST = ((x + y) % pMax)
//								: initPieceST = (x + y == 1 ? pWhite : pBlack));
//				}
//				else
//				{
//					initPieceST = ((x + y) < 1 ? initPieceST = ((x + y) % pMax) + 1 : initPieceST = pBlack);
//				}
//				// ピースの配置位置を設定している 
//				pPos = ChangeTblToScr(pNum + Vector2(x, y));
//				auto tmp = AddObjList(std::make_shared<GamePiece>(pPos, Vector2(BOARD_OFFSET_X, BOARD_OFFSET_Y), (PIECE_ST)initPieceST));
//				data[pNum.y + y][pNum.x + x] = (*tmp);
//			}
//		}
//	}
//
//}

void GameBoard::SetPiece(int x, int y, PIECE_ST state)
{
	// ピースの配置位置を設定している 
	pPos = ChangeTblToScr(Vector2(x, y));
	auto tmp = AddObjList(std::make_shared<GamePiece>(pPos, Vector2(BOARD_OFFSET_X, BOARD_OFFSET_Y), state));
	data[y][x] = (*tmp);
}

bool GameBoard::SetPiece(const Vector2& vec, PIECE_ST id)
{
	bool rtnFlag = false;
	Vector2 pNum = ChangeScrToPos(vec);
	// クリックした位置がボードの盤面外でなければ、ピースの設置を行う 
	if ((pNum >= Vector2(0, 0)) & (pNum < Vector2((data.size() * PIECE_SIZE), (data.size() * PIECE_SIZE))))
	{
		pNum /= PIECE_SIZE;
		pPos = ChangeTblToScr(pNum);
		if (data[pNum.y][pNum.x].expired())
		{
			rtnFlag = true;
			auto tmp = AddObjList(std::make_shared<GamePiece>(pPos, Vector2(BOARD_OFFSET_X, BOARD_OFFSET_Y), id));
			data[pNum.y][pNum.x] = (*tmp);
		}
	}

	return rtnFlag;
}

void GameBoard::SetPieceCnt(PutPiece piece)
{
	this->piece = piece;
}

PutPiece GameBoard::GetPieceCnt(void)
{
	return piece;
}

void GameBoard::ResultPiece(PutPiece piece)
{
	pPos = {0,0};
	// 黒ピースの並び替えを行っている 
	for (int b = 0; b < piece.b; b++)
	{
		if (data[b / data.size()][b % data.size()].expired())
		{
			pPos = ChangeTblToScr(Vector2(b % data.size(), b / data.size()));
			auto tmp = AddObjList(std::make_shared<GamePiece>(pPos, Vector2(BOARD_OFFSET_X, BOARD_OFFSET_Y), PIECE_ST::B));
			data[b / data.size()][b % data.size()] = (*tmp);
		}
	}
	// 白ピースの並び替えを行っている
	for (int w = piece.b; w < piece.b + piece.w; w++)
	{
		if (data[(w / data.size())][w % data.size()].expired())
		{
			pPos = ChangeTblToScr(Vector2(w % data.size(), w / data.size()));
			auto tmp = AddObjList(std::make_shared<GamePiece>(pPos, Vector2(BOARD_OFFSET_X, BOARD_OFFSET_Y), PIECE_ST::W));
			data[(w / data.size())][w % data.size()] = (*tmp);
		}
	}
}

void GameBoard::PieceClear(void)
{
	pieceList.clear();
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
					// 配置したピースと違う色が見つかった時、見つかったピースの色を配置したピースの色に変更してあげる
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
		putPieceTbl.clear();
	}
}

bool GameBoard::CheckReverse(const Vector2& vec, PIECE_ST id)
{
	bool rtnFlag = false;
	Vector2 pNum = ChangeScrToPos(vec);

	// クリックした位置にピースが配置できるかの確認を行っている 
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
	else
	{
		GameBoard::ReverseSkip();
	}
	return rtnFlag;
}

bool GameBoard::CheckReverse(const Vector2& ckPos, const Vector2& pNum, PIECE_ST id)
{
	bool	rtnFlag = false;
	Vector2 ckNum = pNum;

	/* 配置したピースの色と検索する方向のピースの色が違う色の時に
	　 検索する方向の列を探索している */
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
							/* 配置したピースと同じ色のピースを見つけた時探索をやめて
							　 反転することができる列方向をリストに登録している */
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


bool GameBoard::CheckPutPieceFlag(PIECE_ST id)
{
	bool rtnFlag = false;

	for (unsigned int y = 0; y < data.size(); y++)
	{
		for (unsigned int x = 0; x < data.size(); x++)
		{
			/* ピースが置かれていない時、配置した場所で反転ができるかの
			   検索をしている*/
			if (data[y][x].expired())
			{
				for (auto ckPos : pCheckTbl)
				{
					if (CheckReverse(ckPos, Vector2(x, y), id))
					{
						rtnFlag = true;
						putPieceTbl.push_back(Vector2(x, y));
					}
				}
			}
		}
	}
	/* 反転できる方向のリストに必要なく登録を行っていたため、
	   リストの中身を削除している */
	reverseTbl.clear();
	return rtnFlag;
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

Vector2 GameBoard::PutPieceCpu(void)
{
	Vector2 pNum = putPieceTbl.front();
	return ChangeTblToScr(pNum) + Vector2(BOARD_OFFSET_X, BOARD_OFFSET_Y);
}

void GameBoard::SetInvCnt(int reverseCnt)
{
	invCnt = (invCnt > reverseCnt ? invCnt : reverseCnt);
}

void GameBoard::ReverseSkip(void)
{
	for (unsigned int y = 0; y < data.size(); y++)
	{
		for (unsigned int x = 0; x < data.size(); x++)
		{
			// ピースのアニメーションをスキップ処理(未実装)
			if (!data[y][x].expired())
			{
				data[y][x].lock()->ResetAnim(0);
			}
		}
	}
}

bool GameBoard::InvFlag(void)
{
	if (invCnt < 0)
	{
		PutPieceField();
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
	DrawBox(sPos, ePos, 0x106010, true);

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