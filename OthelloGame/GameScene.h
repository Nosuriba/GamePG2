#pragma once
#include <mutex>
#include <memory>
#include <list>
#include "Vector2.h"
#include "SceneState.h"
#include "PieceST.h"
#include "MouseCtl.h"

class GameBoard;

#define LpGameScene (GameScene::GetInstance())

class GameScene
{
public:
	static GameScene & GetInstance()
	{
		// ゲームシーンクラスを一度だけインスタンスするようにしている 
		return *s_Instance;
	}
	void Run();
	// ゲーム画面のサイズを取得するための関数
	Vector2 GetScreenSize(void);	
private:
	
	// GameSceneクラスのdeleterを設定している 
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
	
	static std::unique_ptr<GameScene, GameSceneDeleter>	s_Instance;
	std::shared_ptr<MouseCtl>  mousePtr;
	// マウスをプレイヤータイプの最大数分を作っている(後で修正)
	std::shared_ptr<MouseCtl> sysMouse;
	std::array<std::shared_ptr<MouseCtl>, static_cast<int>(PIECE_ST::MAX)> mouseCtl;
	unique_scene gScene;

	const Vector2 screenSize;
};