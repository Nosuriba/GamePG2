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

void GameBoard::Update(void)
{
	//Vector2 mPos = { (vec.x - BOARD_OFFSET_X),
	//				 (vec.y- BOARD_OFFSET_Y) };
	///* �N���b�N�����ʒu���{�[�h�̔ՖʊO�łȂ���΁A�s�[�X�̐ݒu���s�� */
	//if ((mPos >= Vector2(0,0)) & (mPos < Vector2((data.size() * PIECE_SIZE), (data.size() * PIECE_SIZE))))
	//{
	//	/* �s�[�X���i�[���邽�߂̐ݒ� */
	//	mPos /= PIECE_SIZE;
	//	Vector2 pPos = { mPos.x * PIECE_SIZE, mPos.y * PIECE_SIZE };
	//	if (data[mPos.y][mPos.x].expired())
	//	{
	//		auto tmp = AddObjList(std::make_shared<GamePiece>(pPos, Vector2(PIECE_OFFSET_X, PIECE_OFFSET_Y)));
	//		data[mPos.y][mPos.x] = (*tmp);
	//			
	//		/* �v���C���[�̔ԍ��ɑ΂��ăs�[�X�̐F��ݒ肵�Ă��� */
	//		if(pNum == PIECE_C)
	//		{
	//			data[mPos.y][mPos.x].lock()->SetState(PIECE_C);
	//		}
	//		else if (pNum == PIECE_W)
	//		{
	//			data[mPos.y][mPos.x].lock()->SetState(PIECE_W);
	//		}
	//		else if (pNum == PIECE_R)
	//		{
	//			data[mPos.y][mPos.x].lock()->SetState(PIECE_R);
	//		}
	//		else if (pNum == PIECE_B)
	//		{
	//			data[mPos.y][mPos.x].lock()->SetState(PIECE_B);
	//		}
	//		else
	//		{
	//			/* �v���C���[���ݒ肵���l���𒴂����Ƃ��̏��� */
	//			data[mPos.y][mPos.x].lock()->SetState(PIECE_W);
	//		}
	//		return true;
	//	}
	//	else
	//	{
	//		data[mPos.y][mPos.x].lock()->SetReverse();
	//		return false;
	//	}
	//}
	//return false;
}

void GameBoard::StartPiece(const Vector2& pNum, bool pFlag)
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

			pPos = { (pNum.x + x) * PIECE_SIZE, (pNum.y + y) * PIECE_SIZE };
			auto tmp	= AddObjList(std::make_shared<GamePiece>(pPos, Vector2(PIECE_OFFSET_X, PIECE_OFFSET_Y)));
			data[pNum.y + y][pNum.x + x] = (*tmp);
			data[pNum.y + y][pNum.x + x].lock()->SetState((PIECE_ST)initPieceST);			
		}
	}

}

bool GameBoard::SetPiece(const Vector2& vec, PIECE_ST id)
{
	bool rtnFlag = false;
	Vector2 pNum = { (vec.x - BOARD_OFFSET_X),
					 (vec.y - BOARD_OFFSET_Y) };
	/* �N���b�N�����ʒu���{�[�h�̔ՖʊO�łȂ���΁A�s�[�X�̐ݒu���s�� */
	if ((pNum >= Vector2(0, 0)) & (pNum < Vector2((data.size() * PIECE_SIZE), (data.size() * PIECE_SIZE))))
	{
		/* �s�[�X���i�[���邽�߂̐ݒ� */
		pNum /= PIECE_SIZE;
		/* �s�[�X���W�̐ݒ�*/
		pPos = { pNum.x * PIECE_SIZE,pNum.y * PIECE_SIZE };
		if (data[pNum.y][pNum.x].expired())
		{
			rtnFlag = true;
			auto tmp = AddObjList(std::make_shared<GamePiece>(pPos, Vector2(PIECE_OFFSET_X, PIECE_OFFSET_Y)));
			data[pNum.y][pNum.x] = (*tmp);

			data[pNum.y][pNum.x].lock()->SetState(id);
		}
	}

	return rtnFlag;
}

void GameBoard::SetReverse(const Vector2& vec, PIECE_ST id)
{
	Vector2 pNum = { (vec.x - BOARD_OFFSET_X),
					 (vec.y - BOARD_OFFSET_Y) };
	if (pNum >= Vector2(0, 0) & pNum < Vector2(data.size() * PIECE_SIZE, data.size() * PIECE_SIZE))
	{
		pNum /= PIECE_SIZE;
		if (CheckReverse(pNum, id) == true)
		{
			data[pNum.y][pNum.x].lock()->SetReverse(id);
		}
	}

}

bool GameBoard::CheckReverse(const Vector2& pNum, PIECE_ST id)
{
	bool rtnFlag = false;

	for (auto pCheckPos : pCheckTbl)
	{
		if (CheckReverse(pCheckPos, pNum, id) == true)
		{
			/*SetReverse(pPos + pCheckPos);	*/		// �������C������
			rtnFlag = true;
		}
	}
	return rtnFlag;
}

bool GameBoard::CheckReverse(const Vector2& ckPos, const Vector2& pNum, PIECE_ST id)
{
	bool rtnFlag	= false;
	Vector2 ckNum	= pNum;
	while (rtnFlag)
	{
		ckNum += ckPos;
		/* �{�[�h��Ńs�[�X�������������A���]���ł��邩�𔻒��Ԃ�����*/
		if (ckNum >= Vector2(0, 0) & ckNum < Vector2(data.size(), data.size()))
		{
			if (!data[ckNum.y][ckNum.x].expired())
			{
				/* ���̏����ɏC��������\������ */
				if (data[ckNum.y][ckNum.x].lock()->GetState() != id)
				{
					rtnFlag = true;
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
	return rtnFlag;
}

void GameBoard::Draw()
{
	Vector2 sPos = { BOARD_OFFSET_X, BOARD_OFFSET_Y };
	Vector2 ePos = { BOARD_SIZE + BOARD_OFFSET_X, BOARD_SIZE + PIECE_SIZE };

	/* �Ֆʂ̕`�� */
	DrawBox(sPos, ePos, 0x104010, true);

	sPos = { BOARD_OFFSET_X, BOARD_OFFSET_Y };
	ePos = { BOARD_SIZE + BOARD_OFFSET_X, BOARD_SIZE };

	/* �O���b�h�̕`�� */
	for (unsigned int y = 0; y <= DEF_BOARD_CNT + 1; y++)
	{
		sPos.y = PIECE_SIZE * y;
		ePos.y = PIECE_SIZE * y;
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
