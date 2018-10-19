#pragma once
#include "SceneState.h"
#include "GamePiece.h"

class GameBoard;

class ResultScene :
	public SceneState
{
public:
	ResultScene(std::shared_ptr<GameBoard> boradPtr);
	~ResultScene();
	void Init();
	unique_scene Update(unique_scene own, MouseCtl& mouse);
	
private:
	PutPiece piece = {0,0};
	PIECE_ST WinJudge(int pCntB, int pCntW);
	void DrawWinner(PIECE_ST pState);
	std::shared_ptr<GameBoard> boardPtr;
};

