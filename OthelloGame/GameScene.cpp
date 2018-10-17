#include <DxLib.h>
#include "GameScene.h"
#include "GameBoard.h"
#include "MouseCtl.h"
#include "Player.h"
#include "ImageMng.h"
#include "TitleScene.h"
#include "MainScene.h"
#include "ResultScene.h"

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
}

Vector2 GameScene::GetScreenSize(void)
{
	return Vector2(SCREEN_SIZE_X, SCREEN_SIZE_Y);
}

Vector2 GameScene::GetActiveBoardSize(void)
{
	return boardPtr->GetBoardSize();
}

int GameScene::UpDate()
{
	return 0;
}

int GameScene::SysInit()
{
	/* システムの初期化が終わった後、ゲームの初期化を行うようにしている */
	gScenePtr = &GameScene::TitleUpdate;

	DxLib::SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	/*DxLib::SetWindowIconID();*/
	DxLib::ChangeWindowMode(true);
	DxLib::SetWindowText("1701310_北川 潤一 : OthelloGame");
	if (DxLib_Init() == -1)
	{
		return false;
	}
	DxLib::SetDrawScreen(DX_SCREEN_BACK);
	mousePtr = std::make_unique<MouseCtl>();
	return 0;
}

int GameScene::SysDestroy()
{
	return 0;
}

int GameScene::TitleUpdate()
{
	if (!gScene)
	{
		gScene = std::make_unique<TitleScene>();
	}
	
	if ((*gScene).Update())
	{
		gScenePtr = &GameScene::MainUpdate;
	}
	return 0;
}

int GameScene::MainUpdate()
{
	if (!gScene)
	{
		gScene = std::make_unique<MainScene>();
	}
	
	if ((*gScene).Update())
	{
		gScenePtr = &GameScene::MainUpdate;
	}
	else
	{
		gScenePtr = &GameScene::TitleUpdate;
	}
	return 0;
}

int GameScene::ResultUpdate()
{
	if (!gScene)
	{
		gScene = std::make_unique<ResultScene>();
	}
	if ((*gScene).Update())
	{
		gScenePtr = &GameScene::TitleUpdate;
	}
	else
	{
		gScenePtr = &GameScene::MainUpdate;
	}
	return 0;
}

//int GameScene::TitleInit()
//{
//	gScenePtr = &GameScene::TitleMain;
//	/* 登録されたプレイヤーの初期化を行っている */
//	playerList.clear();					
//	return 0;
//}
//
//int GameScene::TitleMain()
//{
//	if (mousePtr->GetButton()[PUSH_NOW] & (~mousePtr->GetButton()[PUSH_OLD]) & MOUSE_INPUT_RIGHT)
//	{
//		gScenePtr = &GameScene::GameInit;
//	}
//	mousePtr->Update();	
//	DxLib::ClsDrawScreen();
//
//	/* タイトルの描画を行っている */
//	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/title.jpg")[0], true);
//	DxLib::DrawExtendString(0, 0, 2.5f, 2.5f, "タイトル", 0xffff00);
//	DxLib::ScreenFlip();
//
//	return 0;
//}
//
//int GameScene::GameInit()
//{
//	gScenePtr	= &GameScene::GameMain;
//	boardPtr	= std::make_unique<GameBoard>();
//	boardPtr->PieceClear();
//	boardPtr->StartPiece({ 3,3 }, true);			// true : 通常の白黒配置, false : 白黒を反転して配置
//	PutPieceST();
//	/* プレイヤーの登録を行っている */
//	MakePlayer();
//	MakePlayer();
//	player = playerList.begin();
//	return 0;
//}
//
//int GameScene::GameMain()
//{
//	if ((*player)->TurnAct(*mousePtr, *boardPtr))
//	{
//		boardPtr->SetReverse(mousePtr->GetPoint(), (*player)->pGetID());
//		PutPieceST();
//		NextPlayer();
//	}
//	/* pTrayの情報を参照できるようにする */
//
//	if (!boardPtr->CheckPutPieceFlag((*player)->pGetID()))
//	{
//		if (!AutoPassPlayer())
//		{
//			boardPtr->PieceClear();
//			gScenePtr = &GameScene::ResultInit;
//		}
//	}
//	mousePtr->Update();
//	DxLib::ClsDrawScreen();
//	/* ゲーム中の情報を描画している */
//	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/gameBG.png")[0], true);
//	DxLib::DrawExtendString(0, 0, 1.5f, 1.5f, "ゲームモード", 0xffffff);
//	DxLib::DrawExtendFormatString(0, 170, 1.3f, 1.3f, 0xfffffff, "白 : %d", pieceW);
//	DxLib::DrawExtendFormatString(0, 200, 1.3f, 1.3f, 0xfffffff, "黒 : %d", pieceB);
//	boardPtr->Draw();
//	for (auto data : playerList)
//	{
//		(*data).Draw();
//	}
//	/*turnPLpiece->Draw();*/
//	DxLib::ScreenFlip();
//	return 0;
//}
//
//int GameScene::GameDestroy()
//{
//	return 0;
//}
//
//int GameScene::ResultInit()
//{
//	gScenePtr = &GameScene::ResultMain;
//	return 0;
//}
//
//int GameScene::ResultMain()
//{
//	if (mousePtr->GetButton()[PUSH_NOW] & (~mousePtr->GetButton()[PUSH_OLD]) & MOUSE_INPUT_RIGHT)
//	{
//		gScenePtr	 = &GameScene::TitleInit;
//	}
//	boardPtr->ResultPiece(pieceB, pieceW);
//	mousePtr->Update();
//
//	/* リザルトの情報を描画している */
//	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/gameBG.png")[0], true);
//	DxLib::DrawExtendString(0, 0, 1.5f, 1.5f,"リザルト", 0xffffff);
//	boardPtr->Draw();
//	DrawWinner(WinJudge(pieceB, pieceW));
//	/* ピースの個数を描画している部分を修正しておく(関数化しておくのもありかも)*/
//	DxLib::DrawExtendFormatString(0, 170, 1.3f, 1.3f, 0xfffffff, "白 : %d", pieceW);
//	DxLib::DrawExtendFormatString(0, 200, 1.3f, 1.3f, 0xfffffff, "黒 : %d", pieceB);
//	DxLib::ScreenFlip();
//	
//	return 0;
//}

