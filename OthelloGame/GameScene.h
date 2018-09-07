#pragma once
#include <mutex>
#include <memory>
#include <list>
#include "Vector2.h"

class GameBoard;

#define LpGameScene (GameScene::GetInstance())

/* �}�E�X�{�^���̃g���K�[�����p */
enum M_PUSH
{
	PUSH_NOW,
	PUSH_OLD,
	PUSH_MAX
};

//static struct s_Deleter
//{
//	void operator()(GameScene* s_Instance)
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
		/* �Q�[���V�[���N���X����x�����C���X�^���X����悤�ɂ��Ă��� */
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

	/* �Q�[���V�[���֌W�̊֐� */
	int TitleInit();
	int TitleMain();
	int GameInit();
	int GameMain();
	int GameDestroy();
	int ResultInit();
	int ResultMain();

	static std::once_flag initFlag;
	static GameScene	  *s_Instance;
	//static std::unique_ptr<GameScene> s_Instance;
	//static s_Deleter s_Delete ;
	int (GameScene::*gScenePtr)(void);
	std::shared_ptr<GameBoard> boardPtr;

	int mousePush[PUSH_MAX];
};