#pragma once
#include "SceneState.h"
#include "GamePiece.h"

class MouseCtl;
class GameBoard;

class ResultScene :
	public SceneState
{
public:
	ResultScene();
	~ResultScene();
	bool Update();
	void Draw();
	
private:
	PIECE_ST WinJudge(int pCntB, int pCntW);
	void DrawWinner(PIECE_ST pState);

	int ResultInit();
	int ResultMain();
	std::unique_ptr<MouseCtl> mousePtr;
	std::unique_ptr<GameBoard> boardPtr;

};

