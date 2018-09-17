#pragma once
#include <vector>
#include <memory>
#include <list>

class Vector2;
class GamePiece;
class MouseCtl;
class Player;

using piece_ptr  = std::shared_ptr<GamePiece>;
using piece_list = std::list<piece_ptr>;

using player_ptr  = std::shared_ptr<Player>;
using player_list = std::list<player_ptr>;

class GameBoard
{
public:
	GameBoard();
	GameBoard(Vector2 vec);
	~GameBoard();
	void Update(const MouseCtl& mouseCtl);		// ここの修正をする
	void Draw(void);
private:

	/*コンストラクタの共通化用関数*/
	bool CommonBoard(Vector2 vec);

	auto AddObjList(piece_ptr && objPtr);
	auto AddObjList(player_ptr && plPtr);

	player_list playerList;
	piece_list  pieceList;
	std::vector<std::weak_ptr<GamePiece>*> data;
	std::vector<std::weak_ptr<GamePiece>>  pieceData;
};

int DrawLine(Vector2 sPos, Vector2 ePos, unsigned int color, int thickNess);
int DrawBox (Vector2 sPos, Vector2 ePos, unsigned int color, int fillFlag);

