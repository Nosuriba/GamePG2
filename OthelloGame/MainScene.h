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
	// プレイヤー関係の処理
	void MakePlayer();
	void NextPlayer();
	bool AutoPassPlayer();

	void DrawPlType();

	Vector2 boardSize;
	Vector2 mPos;				// クリックしたマウスの位置を保存するもの
	bool reverseFlag;			// 反転処理を行うかの判定用
	PutPiece piece;
	std::array<PL_TYPE, static_cast<int>(PL_TYPE::MAX)> plType;

	player_list playerList;
	player_list::iterator player;
	mouse_array mouseCtl;
	std::shared_ptr<GameBoard> gBoard;

	// ピースの個数の描画位置;
	const std::array<Vector2, static_cast<int>(PIECE_ST::NON)> pCntPos = { Vector2(25, 450), Vector2(700, 450) };
	const std::array<Vector2, static_cast<int>(PIECE_ST::NON)> plPos = { Vector2(25, 480), Vector2(700, 480) };
	const Vector2 plBoxSize;

};

