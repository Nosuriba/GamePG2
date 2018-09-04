#pragma once
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
private:
	GameScene();

	/* �Q�[�����Ɏg�p����V�[���i�R�����g�͌�Ŏ����j */
	int SysInit();
	int TitleInit();
	int TitleMain();
	int GameInit();
	int GameMain();
	int ResultInit();
	int ResultMain();

	int (GameScene::*gScenePtr)(void);
	static GameScene *s_Instance;
};

