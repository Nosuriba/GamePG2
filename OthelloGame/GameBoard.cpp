#include <DxLib.h>
#include "PieceST.h"
#include "GameBoard.h"
#include "GamePiece.h"
#include "GameScene.h"
#include "AudioMng.h"

GameBoard::GameBoard() : pieceSize(64),
defBoardCnt(8),
reverseInvCnt(20),
maxPoint(120)
{
	CommonBoard(Vector2(defBoardCnt, defBoardCnt));
}

GameBoard::GameBoard(Vector2 vec) : pieceSize(64),
defBoardCnt(8),
reverseInvCnt(20),
maxPoint(120)
{
	CommonBoard(vec);
}

GameBoard::~GameBoard()
{
}

void GameBoard::CommonBoard(Vector2 vec)
{
	pPos	 = { 0,0 };
	drawFlag = false;
	invCnt	 = 0;
	// ピースを格納するためのサイズを取得している 
	pieceData.resize(vec.y * vec.x);
	data.resize(vec.y);
	for (unsigned int i = 0; i < data.size(); i++)
	{
		data[i] = &pieceData[i * vec.x];
	}
	
	boardSize   = pieceSize * vec;
	boardOffset = ((LpGameScene.GetScreenSize() - boardSize) / 2);
}

auto GameBoard::AddObjList(piece_shared && objPtr)
{
	pieceList.push_back(objPtr);
	auto itr = pieceList.end();
	itr--;

	return itr;
}
 
Vector2 GameBoard::ChangeScrToPos(const Vector2& pPos)
{
	return Vector2((pPos.x - boardOffset.x), (pPos.y - boardOffset.y));
}

Vector2 GameBoard::ChangeTblToScr(const Vector2& pNum)
{
	return Vector2((pNum.x * pieceSize) + boardOffset.x, (pNum.y * pieceSize) + boardOffset.y);
}

Vector2 GameBoard::GetDataSize()
{
	return Vector2(pieceData.size() / data.size(), data.size());
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

	if (pNum >= Vector2(0, 0) && pNum < Vector2((data.size() * pieceSize), (data.size() * pieceSize)))
	{
		pNum /= pieceSize;
		pPos = ChangeTblToScr(pNum);
		if (data[pNum.y][pNum.x].expired())
		{
			LpAudioMng.PlaySE(LpAudioMng.GetSound().putSE);
			LpAudioMng.ChangeVolume(150, LpAudioMng.GetSound().putSE);
			rtnFlag = true;
			auto tmp = AddObjList(std::make_shared<GamePiece>(pPos, Vector2(0,0), id));
			data[pNum.y][pNum.x] = (*tmp);

			invCnt = reverseInvCnt * 4;		// 反転を行うまでの間隔を設定している
		}
	}
	return rtnFlag;
}

void GameBoard::SetPieceCnt(PutPiece piece)
{
	this->piece = piece;
	pieceList.clear();
}

PutPiece GameBoard::GetPieceCnt()
{
	return piece;
}

void GameBoard::SetReverse(const Vector2& vec, PIECE_ST id)
{
	Vector2 pPos	= ChangeScrToPos(vec) / pieceSize;
	Vector2 rPos	= { 0,0 };
	int reverseCnt  = 0;

	for (auto rNum : reverseTbl)
	{
		while (!data[pPos.y + rNum.y][pPos.x + rNum.x].expired())
		{
			rPos += rNum;
			// 自分のピースと違う色を見つけた場合、反転を行う
			if (CheckPiece(pPos + rPos, id, false))
			{
				reverseCnt++;
				data[pPos.y + rPos.y][pPos.x + rPos.x].lock()->SetState(id, reverseCnt * reverseInvCnt);
			}
			else
			{
				break;
			}
		}
		// コマの配置ができない間隔の設定
		if (invCnt < (reverseCnt * reverseInvCnt))
		{
			invCnt = reverseCnt * reverseInvCnt;
		}
		reverseCnt = 0;
		rPos = { 0,0 };
	}
	reverseTbl.clear();
}

bool GameBoard::CheckReverse(const Vector2& vec, PIECE_ST id)
{
	reverseTbl.clear();
	bool rtnFlag = false;
	Vector2 pNum = ChangeScrToPos(vec);

	if (pNum >= Vector2(0, 0) && pNum < Vector2(data.size() * pieceSize, data.size() * pieceSize))
	{
		pNum /= pieceSize;
		if (data[pNum.y][pNum.x].expired())
		{
			for (auto ckNum : pCheckTbl)
			{
				if (CheckReverse(ckNum, pNum, id))
				{
					rtnFlag = true;
				}
			}
		}
	}
	return rtnFlag;
}

bool GameBoard::CheckReverse(const Vector2& ckNum, const Vector2& pNum, PIECE_ST id)
{
	bool	rtnFlag = false;
	Vector2 ckPos = pNum;

	if (CheckDirPos((ckPos + ckNum), id))
	{
		while (!rtnFlag)
		{
			ckPos += ckNum;
			if (CheckPiece(ckPos, id, true))
			{
				rtnFlag = true;
				reverseTbl.push_back(ckNum);
			}
			if (ckPos >= Vector2(0, 0) && ckPos < Vector2(data.size(), data.size()))
			{
				if (data[ckPos.y][ckPos.x].expired())
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
	return rtnFlag;
}

PIECE_ST GameBoard::CheckPieceST(int x, int y)
{
	// 盤面にピースが配置されている時、ピースの色を取得するようにしている 
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
		else {}
	}
	return PIECE_ST::NON;
}

// コマを置く位置から先の方向が反転できるかの判定
bool GameBoard::CheckDirPos(const Vector2 & ckPos, const PIECE_ST & id)
{
	if (ckPos >= Vector2(0, 0) && ckPos < Vector2(data.size(), data.size()))
	{
		if (!data[ckPos.y][ckPos.x].expired())
		{
			if (data[ckPos.y][ckPos.x].lock()->GetState() != id)
			{
				return true;
			}
		}
	}
	return false;
}

// true..自分の色と同じかの判定, false..自分と違う色かの判定
bool GameBoard::CheckPiece(const Vector2& ckPos, const PIECE_ST& id, bool pieceFlag)
{
	if (pieceFlag)
	{
		if (ckPos >= Vector2(0, 0) && ckPos < Vector2(data.size(), data.size()))
		{
			if (!data[ckPos.y][ckPos.x].expired())
			{
				// 自分と同じ色かの確認
				if (data[ckPos.y][ckPos.x].lock()->GetState() == id)
				{
					return true;
				}
			}
			
		}
	}
	else
	{
		if (ckPos >= Vector2(0, 0) && ckPos < Vector2(data.size(), data.size()))
		{
			if (!data[ckPos.y][ckPos.x].expired())
			{
				// 自分と違う色かの確認
				if (data[ckPos.y][ckPos.x].lock()->GetState() != id)
				{
					return true;
				}
			}

		}
	}
	return false;
}

bool GameBoard::CheckPutPiece()
{
	return (putPieceTbl.size() > 0);
}

Vector2 GameBoard::GetPiecePos(PIECE_ST id)
{
	piece = PutPieceCnt();
	// ピースを置くとき、1ターン目の場合
	if ((piece.w + piece.b) < 6)
	{
		return GetRandomPos();
	}
	else
	{
		// 評価点によってピースを配置する位置を決めている
		return ChoosePutPiece(putPieceTbl, id);
	}
}

Vector2 GameBoard::ChoosePutPiece(std::list<Vector2> pTbl, PIECE_ST id)
{
	auto rtnPos = GetRandomPos();
	auto point  = -200;	

	if (putPieceTbl.size() > 0)
	{
		// 評価点の登録を行っている
		for (Vector2 pTbl : putPieceTbl)
		{
			if (point < DecidePoint(pointTbl[pTbl.y][pTbl.x], pTbl, id))
			{
				point = DecidePoint(pointTbl[pTbl.y][pTbl.x], pTbl, id);
				rtnPos = ChangeTblToScr(pTbl);
			}
		}
	}
	
	return rtnPos;
}

int GameBoard::DecidePoint(int brdPoint, Vector2 pPos, PIECE_ST id)
{
	Vector2 ckPos = pPos;
	int point	  = brdPoint;
	int rPieceCnt = 0;			// 反転させるピースの個数
	int rDirCnt	  = 0;			// 反転できるピースの方向
	bool dirFlag  = false;
	bool rtnFlag  = false;	

	for (auto ckNum : pCheckTbl)
	{
		if (CheckDirPos((ckPos + ckNum), id))
		{
			rtnFlag = false;
			while (!rtnFlag)
			{
				ckPos += ckNum;
				if (CheckPiece(ckPos, id, false))
				{
					rPieceCnt++;
				}
				else
				{
					ckPos -= ckNum;
					for (auto ckDir : pCheckTbl)
					{
						if (CheckPiece(ckPos + ckDir, id, false))
						{
							rDirCnt++;
						}
					}
					if (rDirCnt >= 4)
					{
						dirFlag = true;
					}
					rDirCnt = 0;
					rtnFlag = true;
				}
			}
		}
	}

	if ((piece.w + piece.b < ((data.size() * data.size()) / 2)) && (rPieceCnt > 2))
	{
		point -= 18;
	}
	else
	{
		point += (rPieceCnt * 10);
	}
	if (dirFlag)
	{
		point += 30;
	}
	return point;
}

Vector2 GameBoard::GetRandomPos()
{
	/// ピースをランダムで配置している
	if (putPieceTbl.size() > 0)
	{
		auto itr = putPieceTbl.begin();
		auto rand = GetRand(putPieceTbl.size() - 1);

		for (int i = 0; i < rand; i++)
		{
			itr++;
		}
		return ChangeTblToScr((*itr));
	}
	return { 0,0 };
}

void GameBoard::PutPieceClear()
{
	putPieceTbl.clear();
}

PutPiece GameBoard::PutPieceCnt()
{
	piece = { 0,0 };
	// ピースの色を取得して、それぞれの個数をカウントしている 
	for (unsigned int y = 0; y < data.size(); y++)
	{
		for (unsigned int x = 0; x < data.size(); x++)
		{
			if (CheckPieceST(x, y) == PIECE_ST::W)
			{
				piece.w++;
			}
			else if (CheckPieceST(x, y) == PIECE_ST::B)
			{
				piece.b++;
			}
			else {}
		}
	}

	return piece;
}

void GameBoard::ResultPiece(int pCnt, PIECE_ST id)
{
	pPos = { 0,0 };

	if (data[pCnt / data.size()][pCnt % data.size()].expired())
	{
		pPos = ChangeTblToScr(Vector2(pCnt % data.size(), pCnt / data.size()));
		auto tmp = AddObjList(std::make_shared<GamePiece>(pPos, Vector2(0, 0), id));
		data[pCnt / data.size()][pCnt % data.size()] = (*tmp);
	}
}

bool GameBoard::InvFlag()
{
	if (invCnt < 0)
	{
		return true;
	}
	return false;
}

bool GameBoard::InvFlag(bool drawFlag)
{
	this->drawFlag = drawFlag;
	if (invCnt < 0)
	{
		this->drawFlag = false;
		return true;
	}
	else
	{
		invCnt--;
	}
	return false;
}

void GameBoard::MakePutPieceField(PIECE_ST id)
{
	putPieceTbl.clear();
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
						break;
					}
				}
			}
		}
	}
}

void GameBoard::PutPieceField()
{
	// ピースが置ける位置の描画をしている 
	for (auto pNum : putPieceTbl)
	{
		DrawBox(ChangeTblToScr(pNum) + 1, ChangeTblToScr(pNum) + Vector2(pieceSize, pieceSize) - 1, 0xc8c800, true);
	}
}

void GameBoard::Update()
{
	if (invCnt < 0)
	{
		return;
	}
	invCnt--;
}

void GameBoard::Draw()
{
	Vector2 sPos = { boardOffset.x, boardOffset.y };
	Vector2 ePos = { boardSize.x + boardOffset.x, boardSize.y + pieceSize - 20 };
	
	// 盤面の描画 
	DrawBox(sPos, ePos, 0x107010, true);

	sPos = { boardOffset.x, boardOffset.y };
	ePos = { boardSize.x + boardOffset.x, boardSize.y};

	// グリッドの描画 
	for (unsigned int y = 0; y <= data.size() + 1; y++)
	{
		sPos.y = pieceSize * y + boardOffset.y;
		ePos.y = pieceSize * y + boardOffset.y;
		DrawLine(sPos, ePos, 0xaaaaaa, 2);
	}

	sPos = { boardOffset.x, boardOffset.y };
	ePos = { boardSize.x + boardOffset.x, boardSize .y + pieceSize - 20 };
	for (unsigned int x = 0; x <= data.size(); x++)
	{
		sPos.x = (pieceSize * x) + boardOffset.x;
		ePos.x = (pieceSize * x) + boardOffset.x;
		DrawLine(sPos, ePos, 0xaaaaaa, 2);
	}

	if (InvFlag() || drawFlag)
	{
		// ピースの置ける位置の描画
		PutPieceField();
		if (drawFlag)
		{
			// 反転が行われるまでの間隔
			DrawBox(pPos, pPos + Vector2(pieceSize, pieceSize), 0x48d1cc, true);
		}
	}
	else
	{
		// ピースの置いた位置の描画
		DrawBox(pPos, pPos + Vector2(pieceSize, pieceSize), 0x48d1cc, true);
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