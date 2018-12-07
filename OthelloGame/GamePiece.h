#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>
#include <list>
#include "Vector2.h"
#include "PieceState.h"

class GamePiece;

using piece_shared = std::shared_ptr<GamePiece>;
using piece_sharedList = std::list<piece_shared>;

using pState_unique = std::unique_ptr<PieceState>;
using pState_uniqueList = std::list<pState_unique>;

// {���s�[�X, ���s�[�X}
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
	
	// pState_list�̒��g�ɑ΂��đ�����s������
	PIECE_ST GetState(void);
	void SetState(PIECE_ST pState, int reserveCnt);
	
	// �s�[�X�̎󂯎M�ɕK�v�ȏ����󂯓n�����邽�߂̂��� 
	int  GetSize(void);
	bool SetPos(const Vector2& pos);
	bool SetDrawOffset(const Vector2& drawOffset);

	void Update(void);
	void Draw(void);
private:
	pState_uniqueList pState;
	std::string oldImage;
	Vector2	 pos;
	Vector2	 drawOffset;
	int		 reverseCnt;
	double   drawSize;

	const int drawPieceSize;
	const int animCnt;
	const int flameCnt;
	const int flameInvCnt;
	const int holdAnimCnt;
};

// DxLib::DrawBox���I�[�o�[���[�h��������
int DrawBox(const Vector2& sPos, const Vector2& ePos, unsigned int color, int fillFlag);

