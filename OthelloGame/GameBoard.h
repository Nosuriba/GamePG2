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
	void SetPiece(const Vector2& pNum);						// ピースの初期配置を設定するための関数
	bool SetPiece(const Vector2& vec, PIECE_ST pState);		// 指定した場所にピースを配置するための関数
	void CheckReverse(const Vector2& pNum);
	bool CheckReverse(const Vector2& ckNum, const Vector2& pNum);
	void Draw(void);
private:

	/*コンストラクタの共通化用関数*/
	bool CommonBoard(Vector2 vec);
	void SetReverse(void);

	auto AddObjList(piece_ptr && objPtr);
	piece_list  pieceList;
	std::vector<std::weak_ptr<GamePiece>*> data;
	std::vector<std::weak_ptr<GamePiece>>  pieceData;

	Vector2 pPos;
	/* ピースの方向を確認するための変数 */
	Vector2 pCheckTbl[8] = { {0,-1}, {1,-1}, {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1} };	
};

int DrawLine(Vector2 sPos, Vector2 ePos, unsigned int color, int thickNess);
int DrawBox (Vector2 sPos, Vector2 ePos, unsigned int color, int fillFlag);
