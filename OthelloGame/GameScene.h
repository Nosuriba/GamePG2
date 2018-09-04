#pragma once

#define LpGameScene (GameScene::GetInstance())

class GameScene
{
public:
	~GameScene();
	static GameScene & GetInstance()
	{
		Create();
		return *s_Instance;
	}
	static void Create();
	static void Destroy();
	void Run();
private:
	GameScene();
	
	/*  */
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

	static GameScene *s_Instance;
	int (GameScene::*gScenePtr)(void);

	/* マウスの情報を保存する変数 */
	int mousePush;
	int mousePushOld;
};