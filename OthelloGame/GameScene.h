#pragma once
#include <mutex>
#include <memory>
#include <list>
#include <array>
#include "Vector2.h"
#include "SceneState.h"
#include "PieceST.h"
#include "MouseCtl.h"

enum class TIME_ST
{
	START,
	END, 
	MAX
};

#define LpGameScene (GameScene::GetInstance())

using TIME_POINT = std::chrono::system_clock::time_point;

class GameBoard;

class GameScene
{
public:
	static GameScene & GetInstance()
	{
		// �Q�[���V�[���N���X����x�����C���X�^���X����悤�ɂ��Ă��� 
		return *s_Instance;
	}
	void Run();
	// �Q�[����ʂ̃T�C�Y���擾���邽�߂̊֐�
	Vector2 GetScreenSize();	

	void StartTime();
	void EndTime();
	void ResetTime();			// ���ԃ��Z�b�g�p�֐�

	/// ���肷�鎞�Ԃ̎��
	__int64 GetSecondsTime();
	__int64 GetMilliTime();
	
private:
	
	// GameScene�N���X��deleter��ݒ肵�Ă��� 
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
	std::array<TIME_POINT, static_cast<int>(TIME_ST::MAX)>  clockTimer;		// �������Ԍv���p�̕ϐ�
	
	std::shared_ptr<MouseCtl>  mousePtr;
	// �}�E�X���v���C���[�^�C�v�̍ő吔��������Ă���(��ŏC��)
	std::shared_ptr<MouseCtl> sysMouse;
	std::array<std::shared_ptr<MouseCtl>, static_cast<int>(PIECE_ST::MAX)> mouseCtl;
	unique_scene gScene;

	const Vector2 screenSize;
};