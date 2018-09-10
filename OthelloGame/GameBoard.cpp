#include <DxLib.h>
#include "GameBoard.h"
#include "GamePiece.h"

#define PIECE_SIZE		(64)
#define BOARD_OFFSET_X	(PIECE_SIZE * 2)
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
	pieceData.resize(vec.y * vec.x);
	data.resize(vec.y);
	for (unsigned int i = 0; i < data.size(); i++)
	{
		data[i] = &pieceData[i * vec.x];
	}

	return true;
}


Vector2 GameBoard::GetSize(void)
{
	pieceSize = { PIECE_SIZE, PIECE_SIZE };

	return pieceSize;
}

Vector2 GameBoard::GetBoardSize(void)
{
	boardSize = { BOARD_SIZE, BOARD_SIZE };

	return boardSize;
}

void GameBoard::SetPiecePos(Vector2 pos)
{
	/* �Ֆʂ̕`�悷��ʒu�����炵�Ă���̂ō��W���擾���鎞�A���炵�����̍��W������
	   �n�����W�ɂ��ꂪ�N���Ȃ��悤�ɂ��Ă��� */
	Vector2 vec = { ((pos.x - BOARD_OFFSET_X) / PIECE_SIZE), ((pos.y - BOARD_OFFSET_Y) / PIECE_SIZE) };

	/* X�͈̔͂�0�`7�܂ł�8�A�f�[�^��n���悤�ɂ��Ă���*/
	if ( ((vec.y >= 0) & (vec.y < data.size())) & ((vec.x >= 0) & (vec.x <= data.size() - 1)) )
	{
		data[vec.y][vec.x] = PIECE_W;
	}
	else
	{
		return;
	}	
}

void GameBoard::Update(void)
{
	pieceList.push_back(GamePiece());
	auto itr = pieceList.end();
	itr--;
}

void GameBoard::Draw()
{
	Vector2 sPos = { BOARD_OFFSET_X, BOARD_OFFSET_Y };
	Vector2 ePos = { BOARD_SIZE + BOARD_OFFSET_X, BOARD_SIZE + PIECE_SIZE };

	/* �Ֆʂ̕`������Ă��� */
	DrawBox(sPos, ePos, 0x104010, true);

	sPos = { BOARD_OFFSET_X, BOARD_OFFSET_Y };
	ePos = { BOARD_SIZE + BOARD_OFFSET_X, BOARD_SIZE };

	/* �O���b�h�̕`������Ă���*/
	for (unsigned int y = 0; y <= data.size() + 1; y++)
	{
		sPos.y = PIECE_SIZE * y;
		ePos.y = PIECE_SIZE * y;
		DrawLine(sPos, ePos, 0x000000, 1);
	}

	sPos = { BOARD_OFFSET_X, BOARD_OFFSET_Y };
	ePos = { BOARD_SIZE + BOARD_OFFSET_X, BOARD_SIZE + PIECE_SIZE};

	for (unsigned int x = 0; x <= data.size() + 1; x++)
	{
		sPos.x = PIECE_SIZE * x;
		ePos.x = PIECE_SIZE * x;
		DrawLine(sPos, ePos, 0x000000, 1);
	}

	/* �s�[�X�̏�Ԃ�`�悵�Ă��� */
	for (unsigned int y = 0; y < data.size(); y++)
	{
		for (unsigned int x = 0; x < data.size(); x++)
		{
			if (data[y][x] == PIECE_NON)
			{
				DrawString((PIECE_SIZE * x) + BOARD_OFFSET_X, (PIECE_SIZE * y) + PIECE_SIZE, "��", 0xff0000);
			}
			else if (data[y][x] == PIECE_W)
			{
				DrawString((PIECE_SIZE * x) + BOARD_OFFSET_X, (PIECE_SIZE * y) + PIECE_SIZE, "��", 0xffffff);
			}
			else if (data[y][x] == PIECE_B)
			{
				DrawString((PIECE_SIZE * x) + BOARD_OFFSET_X, (PIECE_SIZE * y) + PIECE_SIZE, "��", 0xffffff);
			}
			else
			{

			}
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
