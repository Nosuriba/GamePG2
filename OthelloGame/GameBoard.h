#pragma once
#include <vector>
#include <memory>
#include <list>
#include "Vector2.h"

class GamePiece;
class MouseCtl;

using piece_ptr  = std::shared_ptr<GamePiece>;
using piece_list = std::list<piece_ptr>;

class GameBoard
{
public:
	GameBoard();
	GameBoard(Vector2 vec);
	~GameBoard();
	void Update(const MouseCtl& mouseCtl);
	void Draw(void);
private:

	/*コンストラクタの共通化用関数*/
	bool CommonBoard(Vector2 vec);
	auto AddObjList(piece_ptr && objPtr);

	piece_list pieceList;
	std::vector<std::weak_ptr<GamePiece>*> data;
	std::vector<std::weak_ptr<GamePiece>>  pieceData;
	Vector2 pieceSize = { 0,0 };
};

int DrawLine(Vector2 sPos, Vector2 ePos, unsigned int color, int thickNess);
int DrawBox (Vector2 sPos, Vector2 ePos, unsigned int color, int fillFlag);

