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
	bool Update(Vector2 vec, int pNum);
	void Draw(void);
	void SetPiece(const Vector2& vec, PIECE_ST pState);
private:

	/*コンストラクタの共通化用関数*/
	bool CommonBoard(Vector2 vec);

	auto AddObjList(piece_ptr && objPtr);
	piece_list  pieceList;
	std::vector<std::weak_ptr<GamePiece>*> data;
	std::vector<std::weak_ptr<GamePiece>>  pieceData;

	/* ピースの方向を確認するための変数 */
	Vector2 pCheckPos;
	Vector2 pCheckTbl[8] = { {0,-1}, {1,-1}, {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1} };	
};

int DrawLine(Vector2 sPos, Vector2 ePos, unsigned int color, int thickNess);
int DrawBox (Vector2 sPos, Vector2 ePos, unsigned int color, int fillFlag);
