#pragma once
#include <mutex>
#include <memory>
#include <list>

#define LpGameScene (GameScene::GetInstance())

enum MOUSE
{
	PUSH_NOW,
	PUSH_OLD,
	PUSH_MAX
};

class GameScene
{
public:
	~GameScene();
	static GameScene & GetInstance()
	{
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
	int (GameScene::*gScenePtr)(void);

	/* マウスの情報を保存する変数 */
	int mousePush;
	int mousePushOld;

	int mousePushD[PUSH_MAX];
};