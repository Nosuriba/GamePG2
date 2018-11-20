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
	MainScene(PL_TYPE plType);
	~MainScene();
	void Init();
	unique_scene Update(unique_scene own, mouse_shared sysMouse);
private:
	// �v���C���[�֌W�̏��� (�Q�[��)
	void MakePlayer();
	void NextPlayer(void);
	bool AutoPassPlayer(void);

	// �z�u���ꂽ�s�[�X�̌����J�E���g���邽�߂̊֐� 
	void PutPieceCnt(void);

	Vector2 boardSize;
	PutPiece piece;
	PL_TYPE plType;

	player_list playerList;
	player_list::iterator player;
	mouse_array mouseCtl;
	std::shared_ptr<GameBoard> boardPtr;

};

