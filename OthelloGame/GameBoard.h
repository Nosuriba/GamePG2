#pragma once
#include <vector>
#include <memory>
#include <list>
#include "Vector2.h"
#include "GamePiece.h"

class Player;

class GameBoard
{
public:
	GameBoard();
	GameBoard(Vector2 vec);
	~GameBoard();

	// �s�[�X�̃T�C�Y���擾������� 
	Vector2 GetDataSize(void);

	Vector2 ChangeTblToScr(const Vector2& pNum);
	
	// �w�肵���ꏊ�Ƀs�[�X��z�u�������
	void SetPiece(int x, int y, PIECE_ST state);
	bool SetPiece(const Vector2& vec, PIECE_ST id);

	// �u���ꂽ�s�[�X�̌����󂯓n������
	void SetPieceCnt(PutPiece piece);
	PutPiece GetPieceCnt(void);

	// ���U���g�Ńs�[�X�̕��т𐮂��邽�߂̂���
	void ResultPiece(PutPiece piece);

	// ���]�������s�����߂̂���
	void SetReverse(const Vector2& vec, PIECE_ST id);
	bool CheckReverse(const Vector2& vec, PIECE_ST id);
	
	// �s�[�X�̒u����ʒu�̐ݒ�Ɋ֘A���������
	void MakePutPieceField(PIECE_ST id);
	bool CheckPutPiece(void);
	void PutPieceClear(void);

	// �u���ꂽ�s�[�X�̌����J�E���g�������
	PIECE_ST CheckPutPieceST(int x, int y);

	std::list<Vector2> GetPieceTbl();

	bool InvFlag(void);
	bool InvFlag(bool drawFlag);
	void Update(void);
	void Draw(void);
private:

	// �R���X�g���N�^�̋��ʉ��p�֐�
	bool CommonBoard(Vector2 vec);

	auto AddObjList(piece_shared && objPtr);

	bool CheckReverse(const Vector2& ckNum, const Vector2& pNum, PIECE_ST id);
	// �s�[�X���u����ʒu�̕`��
	void PutPieceField(void);

	void SetInvCnt(int reverseCnt);

	Vector2 ChangeScrToPos(const Vector2& pPos);

	// �s�[�X�̕������m�F���邽�߂̕ϐ� 
	Vector2 pCheckTbl[8] = { { 1,0 },{ 1,1 },{ 0,1 },{ -1,1 },{ -1,0 },{ -1,-1 },{ 0,-1 },{ 1,-1 } };
	Vector2 pPos;

	bool drawFlag;
	int invCnt;

	// �s�[�X�̌��J�E���g�p 
	PutPiece piece = { 0,0 };

	// �s�[�X�̏������s�����߂ɕK�v�ȕϐ� 
	piece_sharedList   pieceList;
	std::list<Vector2> reverseTbl;
	std::list<Vector2> putPieceTbl;

	// �s�[�X�̒��g���i�[���邽�߂̔z�� 
	std::vector<std::weak_ptr<GamePiece>*> data;
	std::vector<std::weak_ptr<GamePiece>>  pieceData;
};

int DrawLine(Vector2 sPos, Vector2 ePos, unsigned int color, int thickNess);
