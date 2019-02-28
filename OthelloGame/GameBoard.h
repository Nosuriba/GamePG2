#pragma once
#include <vector>
#include <memory>
#include <list>
#include "GamePiece.h"

class Player;

class GameBoard
{
public:
	GameBoard();
	GameBoard(Vector2 vec);
	~GameBoard();

	Vector2 ChangeTblToScr(const Vector2& pNum);
	Vector2 GetDataSize();
	
	/// 指定した場所にピースを配置するもの
	void SetPiece(int x, int y, PIECE_ST state);
	bool SetPiece(const Vector2& vec, PIECE_ST id);

	/// 置かれたピースの個数を受け渡すもの
	void SetPieceCnt(PutPiece piece);
	PutPiece GetPieceCnt();

	/// 反転処理を行うためのもの
	void SetReverse(const Vector2& vec, PIECE_ST id);
	bool CheckReverse(const Vector2& vec, PIECE_ST id);
	
	bool CheckPutPiece();
	Vector2 GetRandomPos();
	void PutPieceClear();

	/// 置かれたピースの個数をカウントするもの
	PutPiece PutPieceCnt();

	PIECE_ST CheckPieceST(int x, int y);

	Vector2 GetPiecePos(PIECE_ST pState);

	void ResultPiece(int piece, PIECE_ST id);

	bool InvFlag();
	bool InvFlag(bool drawFlag);

	void MakePutPieceField(PIECE_ST id);
	void Update();
	void Draw();
private:

	const int maxPoint = 120;
	int pointTbl[8][8] = { {maxPoint, -20, 20, 5, 5, 20, -20, maxPoint},
						   {-20,-40, -5, -5, -5, -5, -40, -20},
						   {40, -5, 15, 3, 3, 15, -5, 40},
						   {25, -5, 3, 3, 3, 3, -5, 25},
						   {25, -5, 3, 3, 3, 3, -5, 25},
						   {40, -5, 15, 3, 3, 15, -5, 40},
						   {-20,-40, -5, -5, -5, -5, -40, -20},
						   {maxPoint, -20, 20, 5, 5, 20, -20, maxPoint}
						  };
	
	/// コンストラクタの共通化用関数
	void CommonBoard(Vector2 vec);

	auto AddObjList(piece_shared && objPtr);
	Vector2 ChangeScrToPos(const Vector2& pPos);

	bool CheckReverse(const Vector2& ckPos, const Vector2& pNum, PIECE_ST id);
	bool CheckDirPos(const Vector2& ckPos, const PIECE_ST& id);							
	bool CheckPiece(const Vector2& ckPos, const PIECE_ST& id, bool pieceFlag);			

	Vector2 ChoosePutPiece(std::list<Vector2> pTbl, PIECE_ST id);

	int DecidePoint(int brdPoint, Vector2 pPos, PIECE_ST id);

	void PutPieceField();																// ピースが置ける位置の描画

	/// ピースの方向を確認するための変数 
	Vector2 pCheckTbl[8] = { { 1,0 },{ 1,1 },{ 0,1 },{ -1,1 },{ -1,0 },{ -1,-1 },{ 0,-1 },{ 1,-1 } };
	Vector2 pPos;

	bool drawFlag;
	int invCnt;

	/// ピースの個数カウント用 
	PutPiece piece = { 0,0 };

	/// ピースの処理を行うために必要な変数 
	piece_sharedList   pieceList;
	std::list<Vector2> reverseTbl;				// ピースの反転できる方向の登録用
	std::list<Vector2> putPieceTbl;				// ピースの置ける位置の登録用

	/// ピースの中身を格納するための配列 
	std::vector<std::weak_ptr<GamePiece>*> data;
	std::vector<std::weak_ptr<GamePiece>>  pieceData;

	Vector2 boardSize;
	Vector2 boardOffset;

	const int pieceSize;
	const int defBoardCnt;
	const int reverseInvCnt;	
};

int DrawLine(Vector2 sPos, Vector2 ePos, unsigned int color, int thickNess);
