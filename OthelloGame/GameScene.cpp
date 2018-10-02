#include <DxLib.h>
#include "GameScene.h"
#include "GameBoard.h"
#include "MouseCtl.h"
#include "Player.h"
#include "ImageMng.h"

#define SCREEN_SIZE_X (800)
#define SCREEN_SIZE_Y (600)

/* 静的なメンバ変数の定義 */
std::unique_ptr<GameScene, GameScene::GameSceneDeleter> GameScene::s_Instance(new GameScene());

GameScene::GameScene()
{
	gScenePtr		= &GameScene::SysInit;
}

GameScene::~GameScene()
{
	DxLib_End();
}

void GameScene::Run()
{
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		(this->*gScenePtr)();
	}
	/*GameSceneDeleter(s_Instance);*/
}

int GameScene::UpDate()
{
	return 0;
}

void GameScene::MakePlayer(void)
{
	playerList.push_back(std::make_shared<Player>());
}

bool GameScene::NextPlayer(void)
{
	bool rtnFlag = false;

	player++;
	if (player == playerList.end())
	{
		player = playerList.begin();
	}
	return rtnFlag;
}

int GameScene::SysInit()
{
	/* システムの初期化が終わった後、ゲームの初期化をする処理用関数に移行している */
	gScenePtr = &GameScene::GameInit;

	/* 表示するウィンドウの初期設定を行っている */
	DxLib::SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	DxLib::ChangeWindowMode(true);
	DxLib::SetWindowText("1701310_北川 潤一 : OthelloGame");
	if (DxLib_Init() == -1)
	{
		return false;
	}
	DxLib::SetDrawScreen(DX_SCREEN_BACK);
	mousePtr = std::make_unique<MouseCtl>();

	/* プレイヤーの登録を行っている */
	/*MakePlayer();
	MakePlayer();
*/
	return 0;
}

int GameScene::SysDestroy()
{
	return 0;
}

int GameScene::TitleInit()
{
	gScenePtr = &GameScene::TitleMain;
	playerList.clear();					// 登録されたプレイヤーの情報を全て削除する。
	return 0;
}

int GameScene::TitleMain()
{
	if (mousePtr->GetButton()[PUSH_NOW] & (~mousePtr->GetButton()[PUSH_OLD]) & MOUSE_INPUT_RIGHT)
	{
		gScenePtr = &GameScene::GameInit;
	}
	mousePtr->Update();	
	DxLib::ClsDrawScreen();
	DxLib::DrawGraph(100, 50, LpImageMng.ImgGetID("image/sample2.png")[0], true);
	DxLib::DrawExtendString(0, 0, 1.5f, 1.5f, "タイトルシーンだよ", 0xffffff);
	DxLib::ScreenFlip();

	return 0;
}

int GameScene::GameInit()
{
	gScenePtr = &GameScene::GameMain;
	boardPtr = std::make_unique<GameBoard>();
	boardPtr->StartPiece({ 3,3 }, true);		// true : 通常の白黒配置, false : 白黒を反転して配置

	/* プレイヤーの登録を行っている */
	MakePlayer();
	MakePlayer();
	player = playerList.begin();
	return 0;
}

int GameScene::GameMain()
{
	/* リザルトシーンに移動する(仮実装)*/
	if (mousePtr->GetButton()[PUSH_NOW] & (~mousePtr->GetButton()[PUSH_OLD]) & MOUSE_INPUT_RIGHT)
	{
		gScenePtr = &GameScene::ResultInit;
	}

	if ((*player)->TurnAct(*mousePtr, *boardPtr))
	{
		boardPtr->SetReverse(mousePtr->GetPoint(), (*player)->pGetID());
		NextPlayer();	
	}
	mousePtr->Update();
	DxLib::ClsDrawScreen();
	DxLib::DrawExtendString(0, 0,1.5f, 1.5f, "ゲームシーンだよ", 0xffffff);
	
	boardPtr->Draw();
	DxLib::ScreenFlip();
	return 0;
}

int GameScene::GameDestroy()
{
	return 0;
}

int GameScene::ResultInit()
{
	gScenePtr = &GameScene::ResultMain;
	return 0;
}

int GameScene::ResultMain()
{
	if (mousePtr->GetButton()[PUSH_NOW] & (~mousePtr->GetButton()[PUSH_OLD]) & MOUSE_INPUT_RIGHT)
	{
		gScenePtr	 = &GameScene::TitleInit;
	}

	mousePtr->Update();
	DxLib::ClsDrawScreen();
	DxLib::DrawExtendString(0, 0, 1.5f, 1.5f,"リザルトシーンだよ", 0xffffff);
	DxLib::ScreenFlip();
	
	return 0;
}

