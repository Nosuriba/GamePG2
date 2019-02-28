#include <DxLib.h>
#include "GameScene.h"
#include "MouseCtl.h"
#include "TitleScene.h"
#include "PieceST.h"

std::unique_ptr<GameScene, GameScene::GameSceneDeleter> GameScene::s_Instance(new GameScene());

GameScene::GameScene() : screenSize(800, 600)
{
	SysInit();
}

GameScene::~GameScene()
{
	DxLib_End();
}

void GameScene::Run()
{
	gScene = std::make_unique<TitleScene>();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		(*sysMouse).Update();
		gScene = (*gScene).Update(std::move(gScene), sysMouse);
	}
}

Vector2 GameScene::GetScreenSize()
{
	return Vector2(screenSize.x, screenSize.y);
}

void GameScene::StartTime()
{
	clockTimer[static_cast<int>(TIME_ST::START)] = std::chrono::system_clock::now();
}

void GameScene::EndTime()
{
	clockTimer[static_cast<int>(TIME_ST::END)] = std::chrono::system_clock::now();
}

void GameScene::ResetTime()
{
	clockTimer[static_cast<int>(TIME_ST::START)] = std::chrono::system_clock::now();
	clockTimer[static_cast<int>(TIME_ST::END)]	 = std::chrono::system_clock::now();;
}

__int64 GameScene::GetSecondsTime()
{
	return std::chrono::duration_cast<std::chrono::seconds>(clockTimer[static_cast<size_t>(TIME_ST::END)]
														  - clockTimer[static_cast<size_t>(TIME_ST::START)]).count();
}

__int64 GameScene::GetMilliTime()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(clockTimer[static_cast<size_t>(TIME_ST::END)]
															   - clockTimer[static_cast<size_t>(TIME_ST::START)]).count();
}

int GameScene::UpDate()
{
	return 0;
}

int GameScene::SysInit()
{
	// システムの初期化が終わった後、ゲームの初期化を行うようにしている 
	DxLib::SetGraphMode(screenSize.x, screenSize.y, 16);
	/*DxLib::SetWindowIconID();*/
	DxLib::ChangeWindowMode(true);
	DxLib::SetWindowText("1701310_北川 潤一 : OthelloGame");
	if (DxLib_Init() == -1)
	{
		return false;
	}
	DxLib::SetDrawScreen(DX_SCREEN_BACK);

	sysMouse = std::make_shared<MouseCtl>();
	return 0;
}

int GameScene::SysDestroy()
{
	return 0;
}

