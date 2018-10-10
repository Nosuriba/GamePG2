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
	/* ピースの初期配置を設定して、ピースを配置する */
	void SetPiece(const Vector2& pNum, bool pFlag);		
	/* 指定した場所にピースを配置する */
	bool SetPiece(const Vector2& vec, PIECE_ST id);

	void ResultPiece(int pCntB, int pCntW);
	void PieceClear(void);

	/* 反転処理関連の関数*/
	void SetReverse(const Vector2& vec, PIECE_ST id);
	bool CheckReverse(const Vector2& vec, PIECE_ST id);
	bool CheckReverse(const Vector2& ckNum, const Vector2& pNum, PIECE_ST id);

	/* ピースの置ける位置があるかどうかの検索 */
	bool CheckPutPieceFlag(PIECE_ST id);
	PIECE_ST CheckPutPieceST(int x, int y);
	void Draw(void);
private:

	/*コンストラクタの共通化用関数*/
	bool CommonBoard(Vector2 vec);

	auto AddObjList(piece_ptr && objPtr);

	/* スクリーン座標からピースの配置される座標に変更している */
	Vector2 ChangeScrToPos(const Vector2& pPos);
	/* 配列のデータからスクリーン座標に変更している */
	Vector2 ChangeTblToScr(const Vector2& pNum);
	void PutPieceField(void);

	piece_list  pieceList;
	std::list<Vector2> reverseTbl;
	std::list<Vector2> putPieceTbl;
	std::vector<std::weak_ptr<GamePiece>*> data;
	std::vector<std::weak_ptr<GamePiece>>  pieceData;

	Vector2 pPos;
	/* ピースの方向を確認するための変数 */
	Vector2 pCheckTbl[8] = { {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1},{ 1,-1 } };
};

int DrawLine(Vector2 sPos, Vector2 ePos, unsigned int color, int thickNess);
int DrawBox (Vector2 sPos, Vector2 ePos, unsigned int color, int fillFlag);
