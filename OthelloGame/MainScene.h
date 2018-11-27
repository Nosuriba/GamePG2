#pragma once
#include "SceneState.h"
#include "GamePiece.h"
#include "MouseCtl.h"

class GameBoard;
class Player;
class MouseCtl;

using player_ptr = std::shared_ptr<Player>;
using player_list = std::list<player_ptr>;

class MainScene :
	public SceneState
{
public:
	MainScene(std::array<PL_TYPE, static_cast<int>(PL_TYPE::MAX)> plType);
	~MainScene();
	void Init();
	unique_scene Update(unique_scene own, mouse_shared sysMouse);
private:
	// プレイヤー関係の処理 (ゲーム)
	void MakePlayer();
	void NextPlayer(void);
	bool AutoPassPlayer(void);

	// 配置されたピースの個数をカウントするための関数 
	void PutPieceCnt(void);

	void DrawPlType(void);

	Vector2 boardSize;
	Vector2 mPos;				// クリックしたマウスの位置を保存するもの
	bool reverseFlag;			// 反転処理を行うかの判定用
	PutPiece piece;
	std::array<PL_TYPE, static_cast<int>(PL_TYPE::MAX)> plType;

	player_list playerList;
	player_list::iterator player;
	mouse_array mouseCtl;
	std::shared_ptr<GameBoard> boardPtr;

};

