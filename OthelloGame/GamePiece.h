#pragma once
#include <vector>
#include <memory>
#include <list>
#include "Vector2.h"

/* �s�[�X�̏��*/
enum PIECE_ST
{
	PIECE_NON,		// ��
	PIECE_W,		// ��
	PIECE_B,		// ��
	PIECE_MAX		// �s�[�X�̍ő吔
};

class GamePiece
{
public:
	GamePiece();
	GamePiece(Vector2 vec);
	~GamePiece();
	PIECE_ST GetState(void);
	void SetState(PIECE_ST pState);
	void SetReverse(void);
	void Draw(void);
private:
	Vector2 pos;
	PIECE_ST pState;
};

