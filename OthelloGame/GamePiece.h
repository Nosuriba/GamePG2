#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>
#include <list>
#include "Vector2.h"
#include "PieceState.h"

class GamePiece;

using piece_ptr = std::shared_ptr<GamePiece>;
using piece_list = std::list<piece_ptr>;

using pState_ptr = std::unique_ptr<PieceState>;
using pState_list = std::list<pState_ptr>;

/* {黒ピースの個数, 白ピースの個数}*/
typedef struct
{
	int b;		// 黒
	int w;		// 白
}PutPiece;


class GamePiece
{
public:
	GamePiece(const Vector2& pos, const Vector2& drawOffset, PIECE_ST pState);		// drawOffsetを引数に追加した形にしておく
	~GamePiece();
	
	/* pState_listの中身に対して操作を行うもの*/
	PIECE_ST GetState(void);
	void SetState(PIECE_ST pState);
	
	/* ピースの受け皿に必要な情報を受け渡しするためのもの */
	int  GetSize(void);
	bool SetPos(const Vector2& pos);
	bool SetDrawOffset(const Vector2& drawOffset);

	void Draw(void);
private:
	pState_list  pState;
	Vector2		 pos;
	Vector2		 drawOffset;
};

/* DxLib::DrawBoxをオーバーロードしたもの*/
int DrawBox(Vector2 sPos, Vector2 ePos, unsigned int color, int fillFlag);

