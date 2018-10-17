#pragma once
#include "SceneState.h"

class GameBoard;
class Player;
class MouseCtl;

using player_ptr = std::shared_ptr<Player>;
using player_list = std::list<player_ptr>;

class MainScene :
	public SceneState
{
public:
	MainScene();
	~MainScene();
	virtual int Update();
	virtual void Draw();
private:
	int GameInit();
	int GameMain();

	/* プレイヤー関係の処理 (ゲーム)*/
	void MakePlayer(void);
	void NextPlayer(void);
	bool AutoPassPlayer(void);

	void PutPieceST(void);

	player_list playerList;
	player_list::iterator player;
	std::unique_ptr<GameBoard> boardPtr;
	std::unique_ptr<MouseCtl> mousePtr;

	int pieceW;
	int pieceB;
};

