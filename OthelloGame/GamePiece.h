#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>
#include <list>
#include "Vector2.h"
#include "PieceState.h"

class GamePiece;

using piece_ptr = std::shared_ptr<GamePiece>;
using piece_list = std::list<piece_ptr>;

using pState_ptr = std::unique_ptr<PieceState>;
using pState_list = std::list<pState_ptr>;

/* {���s�[�X�̌�, ���s�[�X�̌�}*/
typedef struct
{
	int b;		// ��
	int w;		// ��
}PutPiece;


class GamePiece
{
public:
	GamePiece(const Vector2& pos, const Vector2& drawOffset, PIECE_ST pState);		// drawOffset�������ɒǉ������`�ɂ��Ă���
	~GamePiece();
	
	/* pState_list�̒��g�ɑ΂��đ�����s������*/
	PIECE_ST GetState(void);
	void SetState(PIECE_ST pState);
	
	/* �s�[�X�̎󂯎M�ɕK�v�ȏ����󂯓n�����邽�߂̂��� */
	int  GetSize(void);
	bool SetPos(const Vector2& pos);
	bool SetDrawOffset(const Vector2& drawOffset);

	void Draw(void);
private:
	pState_list  pState;
	Vector2		 pos;
	Vector2		 drawOffset;
};

/* DxLib::DrawBox���I�[�o�[���[�h��������*/
int DrawBox(Vector2 sPos, Vector2 ePos, unsigned int color, int fillFlag);

