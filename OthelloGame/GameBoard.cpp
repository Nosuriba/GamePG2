#include <DxLib.h>
#include "GameBoard.h"
#include "GamePiece.h"
#include "MouseCtl.h"
#include "Player.h"

#define PIECE_SIZE		(64)
#define BOARD_OFFSET_X	((PIECE_SIZE * 2) + (PIECE_SIZE / 4))
#define BOARD_OFFSET_Y	(PIECE_SIZE)
#define DEF_BOARD_CNT	(8)
/* �Ֆʂ̃T�C�Y���ς��\��������̂ŁA���̐ݒ�ɏC��������\��������*/
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
	pPos = { 0,0 };
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

Vector2 GameBoard::ChangeScrToPos(Vector2 pPos)
{
	return Vector2((pPos.x - BOARD_OFFSET_X), (pPos.y - BOARD_OFFSET_Y));
}

Vector2 GameBoard::ChangeTblToScr(Vector2 pNum)
{
	/* ���Z���ʂ����������ꍇ�C�����s�� */
	return Vector2((pNum.x * PIECE_SIZE) + BOARD_OFFSET_X, (pNum.y * PIECE_SIZE) + BOARD_OFFSET_Y);
}

void GameBoard::PutPieceField(void)
{
	/* �s�[�X���u�����h��Ԃ�(������)*/
	for (auto pNum : putPieceTbl)
	{
		DrawBox(ChangeTblToScr(pNum), ChangeTblToScr(pNum) + Vector2(PIECE_SIZE, PIECE_SIZE), 0xc8c800, true);
	}
	putPieceTbl.clear();
}

void GameBoard::Update(void)
{
	
}

void GameBoard::SetPiece(const Vector2& pNum, bool pFlag)
{
	/* ���Ԃ���������A���ݔz�u���Ă���s�[�X�̔�����bool�^�̈����ɂ���ĕύX�ł���悤�ɂ�����*/
	int initPieceST = 0;
	for (int y = 0; y <= 1; y++)
	{
		for (int x = 0; x <= 1; x++)
		{
			/* �ŏ��ɔz�u�����s�[�X�̏�Ԃ�ݒ肵�Ă��� */
			if (pFlag)
			{
				initPieceST = ((x + y) < 2 ? initPieceST = ((x + y) % PIECE_MAX) + 1 : initPieceST = PIECE_W);
			}
			else
			{
				initPieceST = (((x + y) % PIECE_MAX) + 2  < 3 
							  ? initPieceST = ((x + y) % PIECE_MAX) + 2 
							  : initPieceST =  (x + y == 2 ? PIECE_B : PIECE_W));
			}

			/* �s�[�X�̔z�u�ݒ���s���Ă��� */
			pPos = ChangeTblToScr(pNum + Vector2(x, y));
			auto tmp	= AddObjList(std::make_shared<GamePiece>(pPos));
			data[pNum.y + y][pNum.x + x] = (*tmp);
			data[pNum.y + y][pNum.x + x].lock()->SetState((PIECE_ST)initPieceST);			
		}
	}

}

bool GameBoard::SetPiece(const Vector2& vec, PIECE_ST id)
{
	bool rtnFlag = false;
	Vector2 pNum = ChangeScrToPos(vec);
	/* �N���b�N�����ʒu���{�[�h�̔ՖʊO�łȂ���΁A�s�[�X�̐ݒu���s�� */
	if ((pNum >= Vector2(0, 0)) & (pNum < Vector2((data.size() * PIECE_SIZE), (data.size() * PIECE_SIZE))))
	{
		pNum /= PIECE_SIZE;
		pPos = ChangeTblToScr(pNum);
		if (data[pNum.y][pNum.x].expired())
		{
			rtnFlag = true;
			auto tmp = AddObjList(std::make_shared<GamePiece>(pPos));
			data[pNum.y][pNum.x] = (*tmp);
			data[pNum.y][pNum.x].lock()->SetState(id);
		}
	}

	return rtnFlag;
}

void GameBoard::SetReverse(const Vector2& vec, PIECE_ST id)
{
	/* �z�񁨃X�N���[���T�C�Y, �X�N���[���T�C�Y���z��ɕϊ����邽�߂̊֐���K������Ă���*/
	bool    reverseFlag = true;
	Vector2 pNum = ChangeScrToPos(vec);
	Vector2 rNum = { 0,0 };

	if (pNum >= Vector2(0, 0) & pNum < Vector2(data.size() * PIECE_SIZE, data.size() * PIECE_SIZE))
	{
		pNum /= PIECE_SIZE;
		for (auto rPos : reverseTbl)
		{
			while (reverseFlag)
			{
				rNum += rPos;
				if (!data[pNum.y + rNum.y][pNum.x + rNum.x].expired())
				{
					if (data[pNum.y + rNum.y][pNum.x + rNum.x].lock()->GetState() != id)
					{
						data[pNum.y + rNum.y][pNum.x + rNum.x].lock()->SetReverse();
					}
					else
					{
						reverseFlag = false;
					}
				}
				else
				{
					reverseFlag = false;
				}
			}
			rNum = { 0,0 };
			reverseFlag = true;
		}
		reverseTbl.clear();
	}
}

bool GameBoard::CheckOutPass(PIECE_ST id)
{
	bool rtnFlag = false;
	for (int y = 0; y < data.size(); y++)
	{
		for (int x = 0; x < data.size(); x++)
		{
			/* �s�[�X���u����Ă��Ȃ����A�z�u�����ꏊ�Ŕ��]���ł��邩��
			���������Ă���*/
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
	/* ���]�ł�������̃��X�g�ɕK�v�Ȃ��o�^���s���Ă������߁A
	���X�g�̒��g���폜���Ă��� */
	reverseTbl.clear();
	return rtnFlag;
}

bool GameBoard::CheckReverse(const Vector2& vec, PIECE_ST id)
{
	bool rtnFlag = false;
	Vector2 pNum = ChangeScrToPos(vec);

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
	bool	rtnFlag	= false;
	Vector2 ckNum	= pNum;

	/* �z�u�����s�[�X�̐F�ƌ�����������̃s�[�X�̐F���Ⴄ�F�̎���
	�@ ������������̗��T�����Ă��� */
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
							/* �z�u�����s�[�X�Ɠ����F�̃s�[�X�����������T������߂�
							�@ ���]���邱�Ƃ��ł������������X�g�ɓo�^���Ă��� */
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

void GameBoard::Draw()
{
	Vector2 sPos = { BOARD_OFFSET_X, BOARD_OFFSET_Y };
	Vector2 ePos = { BOARD_SIZE + BOARD_OFFSET_X, BOARD_SIZE + PIECE_SIZE };

	/* �Ֆʂ̕`�� */
	DrawBox(sPos, ePos, 0x106010, true);

	PutPieceField();

	sPos = { BOARD_OFFSET_X, BOARD_OFFSET_Y };
	ePos = { BOARD_SIZE + BOARD_OFFSET_X, BOARD_SIZE };

	/* �O���b�h�̕`�� */
	for (unsigned int y = 0; y <= DEF_BOARD_CNT + 1; y++)
	{
		sPos.y = PIECE_SIZE * y + BOARD_OFFSET_Y;
		ePos.y = PIECE_SIZE * y + BOARD_OFFSET_Y;
		DrawLine(sPos, ePos, 0xcccccc, 1);
	}

	sPos = { BOARD_OFFSET_X, BOARD_OFFSET_Y };
	ePos = { BOARD_SIZE + BOARD_OFFSET_X, BOARD_SIZE + PIECE_SIZE };

	for (unsigned int x = 0; x <= DEF_BOARD_CNT; x++)
	{
		sPos.x = (PIECE_SIZE * x) + BOARD_OFFSET_X;
		ePos.x = (PIECE_SIZE * x) + BOARD_OFFSET_X;
		DrawLine(sPos, ePos, 0xcccccc, 1);
	}

	/* �s�[�X�̕`�� */
	for (auto itr : pieceList)
	{
		itr->Draw();
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
