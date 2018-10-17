#include "MainScene.h"
#include "GamePiece.h"
#include "GameBoard.h"
#include "Player.h"
#include "MouseCtl.h"

MainScene::MainScene()
{
}


MainScene::~MainScene()
{
}

bool MainScene::Update()
{
	return 0;
}

void MainScene::Draw()
{
}

void MainScene::MakePlayer(void)
{
	playerList.push_back(std::make_shared<Player>());
}

void MainScene::NextPlayer(void)
{
	(*player)->SetTurn(false);
	player++;
	if (player == playerList.end())
	{
		player = playerList.begin();
	}
	(*player)->SetTurn(true);
}

bool MainScene::AutoPassPlayer(void)
{
	NextPlayer();
	if (boardPtr->CheckPutPieceFlag((*player)->pGetID()))
	{
		return true;
	}
	return false;
}

void MainScene::PutPieceST(void)
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
			else {}
		}
	}
}

int MainScene::GameInit()
{
	/*gScenePtr = &GameScene::GameMain;*/
	boardPtr = std::make_unique<GameBoard>();
	boardPtr->PieceClear();
	boardPtr->StartPiece({ 3,3 }, true);			// true : 通常の白黒配置, false : 白黒を反転して配置
	PutPieceST();
	/* プレイヤーの登録を行っている */
	MakePlayer();
	MakePlayer();
	player = playerList.begin();
	return 0;
}

int MainScene::GameMain()
{
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
			boardPtr->PieceClear();
			/*gScenePtr = &GameScene::ResultInit;*/
		}
	}
	mousePtr->Update();
	DxLib::ClsDrawScreen();
	/* ゲーム中の情報を描画している */
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/gameBG.png")[0], true);
	DxLib::DrawExtendString(0, 0, 1.5f, 1.5f, "ゲームモード", 0xffffff);
	DxLib::DrawExtendFormatString(0, 170, 1.3f, 1.3f, 0xfffffff, "白 : %d", pieceW);
	DxLib::DrawExtendFormatString(0, 200, 1.3f, 1.3f, 0xfffffff, "黒 : %d", pieceB);
	boardPtr->Draw();
	for (auto data : playerList)
	{
		(*data).Draw();
	}
	/*turnPLpiece->Draw();*/
	DxLib::ScreenFlip();
	return 0;
}
