#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>
#include <list>
#include "Vector2.h"
#include "PieceState.h"

class GamePiece;

using piece_shared = std::shared_ptr<GamePiece>;
using piece_sharedList = std::list<piece_shared>;

using pState_unique = std::unique_ptr<PieceState>;
using pState_uniqueList = std::list<pState_unique>;

/* {黒ピース, 白ピース}*/
typedef struct
{
	int b;		// 黒
	int w;		// 白
}PutPiece;

/* 反転処理がスキップできるように設定をしておく */

class GamePiece
{
public:
	GamePiece(const Vector2& pos, const Vector2& drawOffset, PIECE_ST pState);		// drawOffsetを引数に追加した形にしておく
	~GamePiece();
	
	/* pState_listの中身に対して操作を行うもの*/
	PIECE_ST GetState(void);
	void SetState(PIECE_ST pState, int reserveCnt);
	
	/* ピースの受け皿に必要な情報を受け渡しするためのもの */
	int  GetSize(void);
	bool SetPos(const Vector2& pos);
	bool SetDrawOffset(const Vector2& drawOffset);

	void ResetAnim(int reverseCnt);
	
	void Update(void);
	void Draw(void);
private:
	pState_uniqueList pState;
	PIECE_ST oldState;
	PIECE_ST state;
	Vector2	 pos;
	Vector2	 drawOffset;
	int		 reverseCnt;
};

/* DxLib::DrawBoxをオーバーロードしたもの*/
int DrawBox(const Vector2& sPos, const Vector2& ePos, unsigned int color, int fillFlag);

