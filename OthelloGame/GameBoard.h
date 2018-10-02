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

//using player_ptr  = std::shared_ptr<Player>;
//using player_list = std::list<player_ptr>;

class GameBoard
{
public:
	GameBoard();
	GameBoard(Vector2 vec);
	~GameBoard();
	void Update(void);
	void StartPiece(const Vector2& pNum, bool pFlag);			// �s�[�X�̏����z�u��ݒ肷�邽�߂̊֐�
	bool SetPiece(const Vector2& vec, PIECE_ST id);				// �w�肵���ꏊ�Ƀs�[�X��z�u���邽�߂̊֐�
	void SetReverse(const Vector2& vec, PIECE_ST id);
	bool CheckReverse(const Vector2& vec, PIECE_ST id);
	bool CheckReverse(const Vector2& ckNum, const Vector2& pNum, PIECE_ST id);
	void Draw(void);
private:

	/*�R���X�g���N�^�̋��ʉ��p�֐�*/
	bool CommonBoard(Vector2 vec);

	auto AddObjList(piece_ptr && objPtr);
	piece_list  pieceList;
	std::list<Vector2> reverseTbl;
	std::vector<std::weak_ptr<GamePiece>*> data;
	std::vector<std::weak_ptr<GamePiece>>  pieceData;

	Vector2 pPos;
	/* �s�[�X�̕������m�F���邽�߂̕ϐ� */
	Vector2 pCheckTbl[8] = { {0,-1}, {1,-1}, {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1} };
};

int DrawLine(Vector2 sPos, Vector2 ePos, unsigned int color, int thickNess);
int DrawBox (Vector2 sPos, Vector2 ePos, unsigned int color, int fillFlag);
