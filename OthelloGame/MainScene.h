#pragma once
#include "SceneState.h"
#include "GamePiece.h"

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
	void Init();
	unique_scene Update(unique_scene own,  MouseCtl& mouse);	
private:
	void SetBoardSize(void);

	/* �v���C���[�֌W�̏��� (�Q�[��)*/
	void MakePlayer(void);
	void NextPlayer(void);
	bool AutoPassPlayer(void);

	/* �z�u���ꂽ�s�[�X�̌����J�E���g���邽�߂̊֐� */
	void PutPieceCnt(void);

	Vector2 boardSize;
	PutPiece piece;

	player_list playerList;
	player_list::iterator player;
	std::shared_ptr<GameBoard> boardPtr;

};

