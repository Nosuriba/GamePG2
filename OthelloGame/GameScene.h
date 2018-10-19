#pragma once
#include <mutex>
#include <memory>
#include <list>
#include <array>
#include "Vector2.h"
#include "GamePiece.h"
#include "PieceState.h"
#include "SceneState.h"

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
		/* ゲームシーンクラスを一度だけインスタンスするようにしている */
		return *s_Instance;
	}
	void Run();
	Vector2 GetScreenSize(void);	// ゲーム画面のサイズを取得するための関数
private:
	
	/* GameSceneクラスのdeleterを設定している */
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
	int SysInit();
	int SysDestroy();
	int pieceW = 0;
	int pieceB = 0;

	static std::unique_ptr<GameScene, GameSceneDeleter>	s_Instance;
	std::unique_ptr<GameBoard> boardPtr;
	std::unique_ptr<MouseCtl>  mousePtr;
	unique_scene gScene;

	player_list playerList;
	player_list::iterator player;
};

/* ゲームシーンクラスに必要な関数や変数は残しておき、
	移動しても大丈夫なものはそれぞれのシーンの情報を渡すようにする*/