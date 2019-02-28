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
		// ゲームシーンクラスを一度だけインスタンスするようにしている 
		return *s_Instance;
	}
	void Run();
	// ゲーム画面のサイズを取得するための関数
	Vector2 GetScreenSize();	

	void StartTime();
	void EndTime();
	void ResetTime();			// 時間リセット用関数

	/// 測定する時間の種類
	__int64 GetSecondsTime();
	__int64 GetMilliTime();
	
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
	std::array<TIME_POINT, static_cast<int>(TIME_ST::MAX)>  clockTimer;		// 処理時間計測用の変数
	
	std::shared_ptr<MouseCtl>  mousePtr;
	// マウスをプレイヤータイプの最大数分を作っている(後で修正)
	std::shared_ptr<MouseCtl> sysMouse;
	std::array<std::shared_ptr<MouseCtl>, static_cast<int>(PIECE_ST::MAX)> mouseCtl;
	unique_scene gScene;

	const Vector2 screenSize;
};