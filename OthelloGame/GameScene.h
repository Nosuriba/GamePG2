#pragma once
#include <mutex>
#include <memory>
#include <list>
#include <array>
#include "Vector2.h"
#include "GamePiece.h"

//class GameScene;
class GameBoard;
class MouseCtl;
class Player;

#define LpGameScene (GameScene::GetInstance())

using player_ptr = std::shared_ptr<Player>;
using player_list = std::list<player_ptr>;

class GameScene
{
public:
	
	static GameScene & GetInstance()
	{
		/* �Q�[���V�[���N���X����x�����C���X�^���X����悤�ɂ��Ă��� */
		return *s_Instance;
	}
	void Run();
private:

	/* GameScene�N���X��deleter��ݒ肵�Ă��� */
	struct GameSceneDeleter
	{
		void operator ()(GameScene* gameScene) const
		{
			delete gameScene;
		}
	};

	GameScene();
	~GameScene();

	int UpDate();

	void MakePlayer(void);

	int SysInit();
	int SysDestroy();

	/* �Q�[���V�[���֌W�̊֐� */
	int TitleInit();
	int TitleMain();
	int GameInit();
	int GameMain();
	int GameDestroy();
	int ResultInit();
	int ResultMain();
	int (GameScene::*gScenePtr)(void);

	static std::unique_ptr<GameScene, GameSceneDeleter>	s_Instance;
	std::unique_ptr<GameBoard> boardPtr;
	std::unique_ptr<MouseCtl>  mousePtr;
	std::unique_ptr<GamePiece> playerPiece;

	std::array <unsigned int, PIECE_MAX> pieceCnt;
	
	player_list playerList;
	player_list::iterator player;
};