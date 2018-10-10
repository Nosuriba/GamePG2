#pragma once
#include <vector>
#include <memory>
#include <list>
#include "Vector2.h"
#include "GamePiece.h"

//class Vector2;
//class GamePiece;
class MouseCtl;
class Player;

using piece_ptr  = std::shared_ptr<GamePiece>;
using piece_list = std::list<piece_ptr>;
class GameBoard
{
public:
	GameBoard();
	GameBoard(Vector2 vec);
	~GameBoard();
	void Update(void);

	Vector2 GetDataSize(void);
	/* �s�[�X�̏����z�u��ݒ肵�āA�s�[�X��z�u���� */
	void SetPiece(const Vector2& pNum, bool pFlag);		
	/* �w�肵���ꏊ�Ƀs�[�X��z�u���� */
	bool SetPiece(const Vector2& vec, PIECE_ST id);

	void ResultPiece(int pCntB, int pCntW);
	void PieceClear(void);

	/* ���]�����֘A�̊֐�*/
	void SetReverse(const Vector2& vec, PIECE_ST id);
	bool CheckReverse(const Vector2& vec, PIECE_ST id);
	bool CheckReverse(const Vector2& ckNum, const Vector2& pNum, PIECE_ST id);

	/* �s�[�X�̒u����ʒu�����邩�ǂ����̌��� */
	bool CheckPutPieceFlag(PIECE_ST id);
	PIECE_ST CheckPutPieceST(int x, int y);
	void Draw(void);
private:

	/*�R���X�g���N�^�̋��ʉ��p�֐�*/
	bool CommonBoard(Vector2 vec);

	auto AddObjList(piece_ptr && objPtr);

	/* �X�N���[�����W����s�[�X�̔z�u�������W�ɕύX���Ă��� */
	Vector2 ChangeScrToPos(const Vector2& pPos);
	/* �z��̃f�[�^����X�N���[�����W�ɕύX���Ă��� */
	Vector2 ChangeTblToScr(const Vector2& pNum);
	void PutPieceField(void);

	piece_list  pieceList;
	std::list<Vector2> reverseTbl;
	std::list<Vector2> putPieceTbl;
	std::vector<std::weak_ptr<GamePiece>*> data;
	std::vector<std::weak_ptr<GamePiece>>  pieceData;

	Vector2 pPos;
	/* �s�[�X�̕������m�F���邽�߂̕ϐ� */
	Vector2 pCheckTbl[8] = { {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1},{ 1,-1 } };
};

int DrawLine(Vector2 sPos, Vector2 ePos, unsigned int color, int thickNess);
int DrawBox (Vector2 sPos, Vector2 ePos, unsigned int color, int fillFlag);
