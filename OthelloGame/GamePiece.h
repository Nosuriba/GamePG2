#pragma once
#include <vector>
#include <memory>
#include <list>
#include "Vector2.h"

/* ピースの状態*/
enum PIECE_ST
{
	PIECE_NON,
	PIECE_W,		// 白
	PIECE_C,		// 黒
	PIECE_R,		// 赤
	PIECE_B,		// 青	
	PIECE_MAX
};

class GamePiece
{
public:
	GamePiece();
	GamePiece(Vector2 vec, Vector2 offset);
	~GamePiece();
	PIECE_ST GetState(void);
	void SetState(PIECE_ST pState);
	void SetReverse(void);
	void Draw(void);
private:
	std::vector<std::weak_ptr<PIECE_ST*>> data;
	std::vector<std::weak_ptr<PIECE_ST>>  pieceData;
	/*piece_list pieceList;*/
	Vector2 pos;
	Vector2 offset;
	PIECE_ST pState;
};

