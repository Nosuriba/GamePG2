#include "MainScene.h"
#include "ResultScene.h"
#include "GamePiece.h"
#include "GameBoard.h"
#include "GameScene.h"
#include "Player.h"
#include "MouseCtl.h"

MainScene::MainScene()
{
	boardPtr = std::make_shared<GameBoard>();
	MainScene::Init();
}


MainScene::~MainScene()
{
}

void MainScene::Init()
{
	boardPtr->StartPiece({ 3,3 }, true);			// true : 通常の白黒配置, false : 白黒を反転して配置
	boardSize = boardPtr->GetDataSize();
	PutPieceST();
	SetBoardSize();
	/* プレイヤーの登録を行っている */
	MakePlayer();
	MakePlayer();
	player = playerList.begin();
}

void MainScene::SetBoardSize(void)
{
	
}

unique_scene MainScene::Update(unique_scene own,  MouseCtl& mouse)
{
	if ((*player)->TurnAct(mouse, *boardPtr))
	{
		boardPtr->SetReverse(mouse.GetPoint(), (*player)->pGetID());
		PutPieceST();
		NextPlayer();
	}

	if (!boardPtr->CheckPutPieceFlag((*player)->pGetID()))
	{
		if (!AutoPassPlayer())
		{
			boardPtr->SetPieceCnt({ pieceB, pieceW });
			boardPtr->PieceClear();
			return std::make_unique<ResultScene>(boardPtr);
		}
	}
	mouse.Update();
	DxLib::ClsDrawScreen();
	/* ゲーム中の情報を描画している */
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/gameBG.png")[0], true);
	DxLib::DrawExtendString(0, 0, 1.5f, 1.5f, "ゲームモード", 0xffffff);
	DxLib::DrawExtendFormatString(0, 170, 1.3f, 1.3f, 0xfffffff, "白 : %d", pieceW);
	DxLib::DrawExtendFormatString(0, 200, 1.3f, 1.3f, 0xfffffff, "黒 : %d", pieceB);
	boardPtr->Draw();
	boardPtr->PutPieceField();
	for (auto data : playerList)
	{
		(*data).Draw();
	}
	/*turnPLpiece->Draw();*/
	DxLib::ScreenFlip();
	return std::move(own);
}

void MainScene::MakePlayer(void)
{
	playerList.push_back(std::make_shared<Player>(boardSize));
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