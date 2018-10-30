#pragma once
#include <vector>
#include <memory>
#include <list>
#include "Vector2.h"
#include "GamePiece.h"

class Player;

class GameBoard
{
public:
	GameBoard();
	GameBoard(Vector2 vec);
	~GameBoard();

	/* ピースのサイズを取得する関数 */
	Vector2 GetDataSize(void);
	
	/* ピースの初期配置を設定して、ピースを配置する関数 */
	void StartPiece(const Vector2& pNum, bool pFlag);

	/* 指定した場所にピースを配置する関数 */
	bool SetPiece(const Vector2& vec, PIECE_ST id);

	/* 配置されたピースの個数を受け渡し用 */
	void SetPieceCnt(PutPiece piece);
	PutPiece GetPieceCnt(void);

	/* リザルトでピースの並びを整えるための関数 */
	void ResultPiece(PutPiece piece);
	void PieceClear(void);

	/* 反転処理を行うための関数 */
	void SetReverse(const Vector2& vec, PIECE_ST id);
	bool CheckReverse(const Vector2& vec, PIECE_ST id);
	bool CheckReverse(const Vector2& ckNum, const Vector2& pNum, PIECE_ST id);

	/* ピースが置けるかの検索を行う関数 */
	bool CheckPutPieceFlag(PIECE_ST id);
	PIECE_ST CheckPutPieceST(int x, int y);
	void PutPieceField(void);
	void Draw(void);
private:

	/*コンストラクタの共通化用関数*/
	bool CommonBoard(Vector2 vec);

	auto AddObjList(piece_shared && objPtr);

	/* 画面のサイズ、データのサイズを変換するための関数 */
	Vector2 ChangeScrToPos(const Vector2& pPos);
	Vector2 ChangeTblToScr(const Vector2& pNum);

	/* ピースの方向を確認するための変数 */
	Vector2 pCheckTbl[8] = { { 1,0 },{ 1,1 },{ 0,1 },{ -1,1 },{ -1,0 },{ -1,-1 },{ 0,-1 },{ 1,-1 } };

	Vector2 pPos;
	PutPiece piece = { 0,0 };

	/* ピースの処理を行うために必要な変数 */
	piece_sharedList  pieceList;
	std::list<Vector2> reverseTbl;
	std::list<Vector2> putPieceTbl;

	/* ピースの中身を格納するための配列 */
	std::vector<std::weak_ptr<GamePiece>*> data;
	std::vector<std::weak_ptr<GamePiece>>  pieceData;
};

int DrawLine(Vector2 sPos, Vector2 ePos, unsigned int color, int thickNess);
