#pragma once
#include "SceneState.h"
#include "GamePiece.h"

class GameBoard;
class MouseCtl;

class ResultScene :
	public SceneState
{
public:
	ResultScene(std::shared_ptr<GameBoard> boradPtr);
	~ResultScene();
	void Init();
	unique_scene Update(unique_scene own, mouse_shared sysMouse);
private:
	PIECE_ST WinJudge(PutPiece piece);		// èüé“ÇîªíËÇ∑ÇÈÇΩÇﬂÇÃÇ‡ÇÃ
	void DrawWinner(PIECE_ST pState);

	PutPiece piece = { 0,0 };

	int dispCnt;
	int pCnt;
	int pCntMax;
	int putCnt;
	int animCnt;
	bool putFlag;

	std::shared_ptr<GameBoard> gBoard;
};

