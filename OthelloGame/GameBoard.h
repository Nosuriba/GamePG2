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

	/* �s�[�X�̃T�C�Y���擾����֐� */
	Vector2 GetDataSize(void);
	
	/* �s�[�X�̏����z�u��ݒ肵�āA�s�[�X��z�u����֐� */
	void StartPiece(const Vector2& pNum, bool pFlag);

	/* �w�肵���ꏊ�Ƀs�[�X��z�u����֐� */
	bool SetPiece(const Vector2& vec, PIECE_ST id);

	/* �z�u���ꂽ�s�[�X�̌����󂯓n���p */
	void SetPieceCnt(PutPiece piece);
	PutPiece GetPieceCnt(void);

	/* ���U���g�Ńs�[�X�̕��т𐮂��邽�߂̊֐� */
	void ResultPiece(PutPiece piece);
	void PieceClear(void);

	/* ���]�������s�����߂̊֐� */
	void SetReverse(const Vector2& vec, PIECE_ST id);
	bool CheckReverse(const Vector2& vec, PIECE_ST id);
	bool CheckReverse(const Vector2& ckNum, const Vector2& pNum, PIECE_ST id);

	/* �s�[�X���u���邩�̌������s���֐� */
	bool CheckPutPieceFlag(PIECE_ST id);
	PIECE_ST CheckPutPieceST(int x, int y);
	void PutPieceField(void);
	void Draw(void);
private:

	/*�R���X�g���N�^�̋��ʉ��p�֐�*/
	bool CommonBoard(Vector2 vec);

	auto AddObjList(piece_shared && objPtr);

	/* ��ʂ̃T�C�Y�A�f�[�^�̃T�C�Y��ϊ����邽�߂̊֐� */
	Vector2 ChangeScrToPos(const Vector2& pPos);
	Vector2 ChangeTblToScr(const Vector2& pNum);

	/* �s�[�X�̕������m�F���邽�߂̕ϐ� */
	Vector2 pCheckTbl[8] = { { 1,0 },{ 1,1 },{ 0,1 },{ -1,1 },{ -1,0 },{ -1,-1 },{ 0,-1 },{ 1,-1 } };

	Vector2 pPos;
	PutPiece piece = { 0,0 };

	/* �s�[�X�̏������s�����߂ɕK�v�ȕϐ� */
	piece_sharedList  pieceList;
	std::list<Vector2> reverseTbl;
	std::list<Vector2> putPieceTbl;

	/* �s�[�X�̒��g���i�[���邽�߂̔z�� */
	std::vector<std::weak_ptr<GamePiece>*> data;
	std::vector<std::weak_ptr<GamePiece>>  pieceData;
};

int DrawLine(Vector2 sPos, Vector2 ePos, unsigned int color, int thickNess);
