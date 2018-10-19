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
		/* �Q�[���V�[���N���X����x�����C���X�^���X����悤�ɂ��Ă��� */
		return *s_Instance;
	}
	void Run();
	/* �Q�[����ʂ̃T�C�Y���擾���邽�߂̊֐�*/
	Vector2 GetScreenSize(void);	
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
	int SysInit();
	int SysDestroy();
	
	static std::unique_ptr<GameScene, GameSceneDeleter>	s_Instance;
	std::unique_ptr<MouseCtl>  mousePtr;
	unique_scene gScene;
};

/* �Q�[���V�[���N���X�ɕK�v�Ȋ֐���ϐ��͎c���Ă����A
	�ړ����Ă����v�Ȃ��̂͂��ꂼ��̃V�[���̏���n���悤�ɂ���*/