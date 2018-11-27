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

	// ピースのサイズを取得するもの 
	Vector2 GetDataSize(void);

	Vector2 ChangeTblToScr(const Vector2& pNum);
	
	// 指定した場所にピースを配置するもの
	void SetPiece(int x, int y, PIECE_ST state);
	bool SetPiece(const Vector2& vec, PIECE_ST id);

	// 置かれたピースの個数を受け渡すもの
	void SetPieceCnt(PutPiece piece);
	PutPiece GetPieceCnt(void);

	// リザルトでピースの並びを整えるためのもの
	void ResultPiece(PutPiece piece);

	// 反転処理を行うためのもの
	void SetReverse(const Vector2& vec, PIECE_ST id);
	bool CheckReverse(const Vector2& vec, PIECE_ST id);
	
	// ピースの置ける位置の設定に関連があるもの
	void MakePutPieceField(PIECE_ST id);
	bool CheckPutPiece(void);
	void PutPieceClear(void);

	// 置かれたピースの個数をカウントするもの
	PIECE_ST CheckPutPieceST(int x, int y);

	std::list<Vector2> GetPieceTbl();

	bool InvFlag(void);
	bool InvFlag(bool drawFlag);
	void Update(void);
	void Draw(void);
private:

	// コンストラクタの共通化用関数
	bool CommonBoard(Vector2 vec);

	auto AddObjList(piece_shared && objPtr);

	bool CheckReverse(const Vector2& ckNum, const Vector2& pNum, PIECE_ST id);
	// ピースが置ける位置の描画
	void PutPieceField(void);

	void SetInvCnt(int reverseCnt);

	Vector2 ChangeScrToPos(const Vector2& pPos);

	// ピースの方向を確認するための変数 
	Vector2 pCheckTbl[8] = { { 1,0 },{ 1,1 },{ 0,1 },{ -1,1 },{ -1,0 },{ -1,-1 },{ 0,-1 },{ 1,-1 } };
	Vector2 pPos;

	bool drawFlag;
	int invCnt;

	// ピースの個数カウント用 
	PutPiece piece = { 0,0 };

	// ピースの処理を行うために必要な変数 
	piece_sharedList   pieceList;
	std::list<Vector2> reverseTbl;
	std::list<Vector2> putPieceTbl;

	// ピースの中身を格納するための配列 
	std::vector<std::weak_ptr<GamePiece>*> data;
	std::vector<std::weak_ptr<GamePiece>>  pieceData;
};

int DrawLine(Vector2 sPos, Vector2 ePos, unsigned int color, int thickNess);
