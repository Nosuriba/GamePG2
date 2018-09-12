#pragma once
#include <mutex>
#include <memory>
#include <list>
#include "Vector2.h"

//class GameScene;
class GameBoard;
class MouseCtl;

#define LpGameScene (GameScene::GetInstance())

/* マウスボタンのトリガー処理用 */
//enum M_PUSH
//{
//	PUSH_NOW,
//	PUSH_OLD,
//	PUSH_MAX
//};

//static struct s_Deleter
//{
//	void operator()(std::unique_ptr<GameScene, s_Deleter>*  s_Instance)
//	{
//		delete s_Instance;
//	}
//};

class GameScene
{
public:
	~GameScene();
	static GameScene & GetInstance()
	{
		/* ゲームシーンクラスを一度だけインスタンスするようにしている */
		std::call_once(initFlag, Create);
		Create();
		return *s_Instance;
	}
	static void Create();
	static void Destroy();
	void Run();
private:
	GameScene();
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

	static std::once_flag initFlag;
	static GameScene	  *s_Instance;
	/*static std::unique_ptr<GameScene, s_Deleter> s_Instance;*/
	int (GameScene::*gScenePtr)(void);
	std::unique_ptr<GameBoard> boardPtr;
	std::unique_ptr<MouseCtl> mousePtr;

	// int mousePush[PUSH_MAX];
};