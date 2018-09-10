#pragma once
#include <vector>
#include <memory>
#include <list>
#include "Vector2.h"

/* ピースの状態*/
enum PIECE_ST
{
	PIECE_NON,
	PIECE_B,
	PIECE_W,
	PIECE_MAX
};

class GamePiece;

class GameBoard
{
public:
	GameBoard();
	GameBoard(Vector2 vec);
	~GameBoard();

	void SetPiecePos(Vector2 pos);

	void Update(void);
	void Draw(void);
private:

	/*コンストラクタの共通化用関数*/
	bool CommonBoard(Vector2 vec);

	// std::vector<std::vector<PIECE_ST>> pieceData;
	std::vector<PIECE_ST*> data;
	std::vector<PIECE_ST>  pieceData;

	std::list<GamePiece> pieceList;

};

int DrawLine(Vector2 sPos, Vector2 ePos, unsigned int color, int thickNess);
int DrawBox (Vector2 sPos, Vector2 ePos, unsigned int color, int fillFlag);

