#include <DxLib.h>
#include "PieceST.h"
#include "GameBoard.h"
#include "GamePiece.h"
#include "MouseCtl.h"
#include "Player.h"

GameBoard::GameBoard() : pieceSize(64),
defBoardCnt(8),
boardSize(pieceSize * defBoardCnt),
reverseInvCnt(20),
boardOffset((pieceSize * 2) + (pieceSize / 4), pieceSize)
{
	CommonBoard(Vector2(defBoardCnt, defBoardCnt));
}

GameBoard::GameBoard(Vector2 vec) : pieceSize(64),
defBoardCnt(8),
boardSize(pieceSize * defBoardCnt),
reverseInvCnt(20),
boardOffset((pieceSize * 2) + (pieceSize / 4), pieceSize)
{
	CommonBoard(vec);
}

GameBoard::~GameBoard()
{
}

bool GameBoard::CommonBoard(Vector2 vec)
{
	pPos	 = { 0,0 };
	drawFlag = false;
	invCnt	 = 0;
	// �s�[�X���i�[���邽�߂̃T�C�Y���擾���Ă��� 
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

// ��ʃT�C�Y���N���b�N�������W�ɕϊ����Ă��� 
Vector2 GameBoard::ChangeScrToPos(const Vector2& pPos)
{
	return Vector2((pPos.x - boardOffset.x), (pPos.y - boardOffset.y));
}

// �f�[�^�T�C�Y����ʃT�C�Y�ɕϊ����Ă���
Vector2 GameBoard::ChangeTblToScr(const Vector2& pNum)
{
	return Vector2((pNum.x * pieceSize) + boardOffset.x, (pNum.y * pieceSize) + boardOffset.y);
}

void GameBoard::PutPieceField(void)
{
	// �s�[�X���u����ʒu�̕`������Ă��� 
	for (auto pNum : putPieceTbl)
	{
		DrawBox(ChangeTblToScr(pNum) + 1, ChangeTblToScr(pNum) + Vector2(pieceSize, pieceSize) - 1, 0xc8c800, true);
	}
}

Vector2 GameBoard::GetDataSize(void)
{
	return Vector2((pieceData.size() / data.size()), data.size());
}

void GameBoard::SetPiece(int x, int y, PIECE_ST state)
{
	// �s�[�X�̔z�u�ʒu��ݒ肵�Ă��� 
	pPos = ChangeTblToScr(Vector2(x, y));
	auto tmp = AddObjList(std::make_shared<GamePiece>(pPos, Vector2(0,0), state));
	data[y][x] = (*tmp);
}

bool GameBoard::SetPiece(const Vector2& vec, PIECE_ST id)
{
	bool rtnFlag = false;
	Vector2 pNum = ChangeScrToPos(vec);
	// �N���b�N�����ʒu�ɔՖʏ�ł��邩�̊m�F���s���Ă��� 
	if ((pNum >= Vector2(0, 0)) & (pNum < Vector2((data.size() * pieceSize), (data.size() * pieceSize))))
	{
		pNum /= pieceSize;
		pPos = ChangeTblToScr(pNum);
		if (data[pNum.y][pNum.x].expired())
		{
			rtnFlag = true;
			auto tmp = AddObjList(std::make_shared<GamePiece>(pPos, Vector2(0,0), id));
			data[pNum.y][pNum.x] = (*tmp);

			invCnt = reverseInvCnt * 4;		// ���]���s���܂ł̊Ԋu��ݒ肵�Ă���
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

// ���U���g��ʂŃs�[�X�̕��ёւ����s�����߂̂���
void GameBoard::ResultPiece(PutPiece piece)
{
	pPos = {0,0};

	// ���s�[�X�̕��ёւ����s���Ă��� 
	for (int b = 0; b < piece.b; b++)
	{
		if (data[b / data.size()][b % data.size()].expired())
		{
			pPos = ChangeTblToScr(Vector2(b % data.size(), b / data.size()));
			auto tmp = AddObjList(std::make_shared<GamePiece>(pPos, Vector2(0,0), PIECE_ST::B));
			data[b / data.size()][b % data.size()] = (*tmp);
		}
	}
	// ���s�[�X�̕��ёւ����s���Ă���
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

	pNum /= pieceSize;
	for (auto rPos : reverseTbl)
	{
		while (!data[pNum.y + rNum.y][pNum.x + rNum.x].expired())
		{
			rNum += rPos;
			// �u�����s�[�X�ƈႤ�F���������ꍇ�A���]���s��
			if (data[pNum.y + rNum.y][pNum.x + rNum.x].lock()->GetState() != id)
			{
				reverseCnt++;
				data[pNum.y + rNum.y][pNum.x + rNum.x].lock()->SetState(id, reverseCnt * reverseInvCnt);
			}
			else
			{
				break;
			}
		}
		// �R�}�̔z�u���ł��Ȃ��Ԋu�̐ݒ�
		if (invCnt < (reverseCnt * reverseInvCnt))
		{
			invCnt = reverseCnt * reverseInvCnt;
		}
		reverseCnt = 0;
		rNum = { 0,0 };
	}
	reverseTbl.clear();
}

bool GameBoard::CheckReverse(const Vector2& vec, PIECE_ST id)
{
	reverseTbl.clear();		// �u����ʒu��o�^���鎞�ɓ��������X�g�̒��g���폜���Ă���
	bool rtnFlag = false;
	Vector2 pNum = ChangeScrToPos(vec);

	// �N���b�N�����ʒu�ɔՖʏ�ł��邩�̊m�F���s���Ă���
	if (pNum >= Vector2(0, 0) & pNum < Vector2(data.size() * pieceSize, data.size() * pieceSize))
	{
		pNum /= pieceSize;
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
						// �s�[�X�̒u����ʒu�̓o�^
						putPieceTbl.push_back(Vector2(x, y));
					}
				}
			}
		}
	}
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
	// �ՖʂɃs�[�X���z�u����Ă������A�s�[�X�̐F���擾����悤�ɂ��Ă��� 
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

bool GameBoard::InvFlag(void)
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
	Vector2 sPos = { boardOffset.x, boardOffset.y };
	Vector2 ePos = { boardSize + boardOffset.x, boardSize + pieceSize };
	
	// �Ֆʂ̕`�� 
	DrawBox(sPos, ePos, 0x107010, true);

	sPos = { boardOffset.x, boardOffset.y };
	ePos = { boardSize + boardOffset.x, boardSize };

	// �O���b�h�̕`�� 
	for (unsigned int y = 0; y <= defBoardCnt + 1; y++)
	{
		sPos.y = pieceSize * y + boardOffset.y;
		ePos.y = pieceSize * y + boardOffset.y;
		DrawLine(sPos, ePos, 0xaaaaaa, 2);
	}

	sPos = { boardOffset.x, boardOffset.y };
	ePos = { boardSize + boardOffset.x, boardSize + pieceSize };
	for (unsigned int x = 0; x <= defBoardCnt; x++)
	{
		sPos.x = (pieceSize * x) + boardOffset.x;
		ePos.x = (pieceSize * x) + boardOffset.x;
		DrawLine(sPos, ePos, 0xaaaaaa, 2);
	}

	if (InvFlag() | drawFlag)
	{
		// �s�[�X�̒u����ʒu�̕`��
		PutPieceField();

		if (drawFlag)
		{
			// ���]���s����܂ł̊Ԋu
			DrawBox(pPos, pPos + Vector2(pieceSize, pieceSize), 0x48d1cc, true);
		}
		
	}
	else
	{
		// �s�[�X�̒u�����ʒu�̕`��
		DrawBox(pPos, pPos + Vector2(pieceSize, pieceSize), 0x48d1cc, true);
	}

	// �s�[�X�̕`�� 
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