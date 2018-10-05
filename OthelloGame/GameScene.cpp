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

void GameScene::NextPlayer(void)
{
	/*bool rtnFlag = false;*/

	player++;
	if (player == playerList.end())
	{
		player = playerList.begin();
	}
}

bool GameScene::AutoPassPlayer(void)
{
	player++;
	if (player == playerList.end())
	{
		player = playerList.begin();
	}

	if (boardPtr->CheckPutPieceFlag((*player)->pGetID()))
	{
		return true;
	}
	return false;
}

void GameScene::PutPieceST(void)
{
	pieceW = 0;
	pieceB = 0;

	/* ピースの色を取得して、それぞれの個数をカウントしている */
	for (int y = 0; y < boardPtr->GetDataSize().y; y++)
	{
		for (int x = 0; x < boardPtr->GetDataSize().x; x++)
		{
			if (boardPtr->CheckPutPieceST(x, y) == PIECE_W)
			{
				pieceW++;
			}
			else if (boardPtr->CheckPutPieceST(x, y) == PIECE_B)
			{
				pieceB++;
			}
			else{}
		}
	}
}

bool GameScene::WinJudge(void)
{
	return false;
}

int GameScene::SysInit()
{
	/* システムの初期化が終わった後、ゲームの初期化をする処理用関数に移行している */
	gScenePtr = &GameScene::TitleInit;

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
	return 0;
}

int GameScene::SysDestroy()
{
	return 0;
}

int GameScene::TitleInit()
{
	gScenePtr = &GameScene::TitleMain;
	/* 登録されたプレイヤーの初期化を行っている */
	playerList.clear();					
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
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/title.jpg")[0], true);
	DxLib::DrawExtendString(0, 0, 1.5f, 1.5f, "タイトルシーンだよ", 0x000000);
	DxLib::ScreenFlip();

	return 0;
}

int GameScene::GameInit()
{
	gScenePtr = &GameScene::GameMain;
	boardPtr = std::make_unique<GameBoard>();
	boardPtr->PieceClear();
	boardPtr->SetPiece({ 3,3 }, true);			// true : 通常の白黒配置, false : 白黒を反転して配置
	PutPieceST();
	/* プレイヤーの登録を行っている */
	MakePlayer();
	MakePlayer();
	player = playerList.begin();
	return 0;
}

int GameScene::GameMain()
{
	if (mousePtr->GetButton()[PUSH_NOW] & (~mousePtr->GetButton()[PUSH_OLD]) & MOUSE_INPUT_RIGHT)
	{
		gScenePtr = &GameScene::ResultInit;
		boardPtr->PieceClear();
	}

	if ((*player)->TurnAct(*mousePtr, *boardPtr))
	{
		boardPtr->SetReverse(mousePtr->GetPoint(), (*player)->pGetID());
		PutPieceST();
		NextPlayer();
		
	}

	if (!boardPtr->CheckPutPieceFlag((*player)->pGetID()))
	{
		if (!AutoPassPlayer())
		{
			gScenePtr = &GameScene::ResultInit;
		}
	}
	mousePtr->Update();
	DxLib::ClsDrawScreen();
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/gameBG.png")[0], true);
	DxLib::DrawExtendString(0, 0,1.5f, 1.5f, "ゲームシーンだよ", 0xffffff);
	/* 現在ターン処理を行っているピースを描画している */
	DxLib::DrawGraph(0, 50, (*player)->pGetID() == PIECE_W ? LpImageMng.ImgGetID("image/player1.png")[0] 
														   : LpImageMng.ImgGetID("image/player2.png")[0], true);
	DxLib::DrawFormatString(0, 200, 0xfffffff, "白 : %d", pieceW);
	DxLib::DrawFormatString(0, 230, 0xfffffff, "黒 : %d", pieceB);
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
	/*PutPieceST();*/
	/*boardPtr->PieceClear();*/
	boardPtr->ResultPiece(pieceB, pieceW);

	mousePtr->Update();
	DxLib::ClsDrawScreen();
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/gameBG.png")[0], true);
	DxLib::DrawExtendString(0, 0, 1.5f, 1.5f,"リザルトシーンだよ", 0xffffff);
	boardPtr->Draw();
	DxLib::ScreenFlip();
	
	return 0;
}

