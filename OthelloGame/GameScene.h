#pragma once
#include <mutex>
#include <memory>
#include <list>
#include "Vector2.h"
#include "SceneState.h"

class GameBoard;
class MouseCtl;

#define LpGameScene (GameScene::GetInstance())

class GameScene
{
public:
	
	static GameScene & GetInstance()
	{
		/* ゲームシーンクラスを一度だけインスタンスするようにしている */
		return *s_Instance;
	}
	void Run();
	/* ゲーム画面のサイズを取得するための関数*/
	Vector2 GetScreenSize(void);	
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
	
	static std::unique_ptr<GameScene, GameSceneDeleter>	s_Instance;
	std::unique_ptr<MouseCtl>  mousePtr;
	unique_scene gScene;
};

/* ゲームシーンクラスに必要な関数や変数は残しておき、
	移動しても大丈夫なものはそれぞれのシーンの情報を渡すようにする*/