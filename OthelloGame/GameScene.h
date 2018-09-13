#pragma once
#include <mutex>
#include <memory>
#include <list>
#include "Vector2.h"

//class GameScene;
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
private:

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

	/* ゲームシーン関係の関数 */
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

};