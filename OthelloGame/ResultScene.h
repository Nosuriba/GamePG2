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
	
	/* ŸÒ‚ğ”»’è‚·‚é‚½‚ß‚ÌŠÖ” */
	PIECE_ST WinJudge(PutPiece piece);
	void DrawWinner(PIECE_ST pState);

	PutPiece piece = { 0,0 };

	std::shared_ptr<GameBoard> boardPtr;
};

