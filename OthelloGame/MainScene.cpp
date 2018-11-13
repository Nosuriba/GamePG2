#include "MainScene.h"
#include "ResultScene.h"
#include "GameBoard.h"
#include "Player.h"
#include "MouseCtl.h"

MainScene::MainScene(PL_TYPE plType)
{
	this->plType = plType;
	boardPtr = std::make_shared<GameBoard>();
	MainScene::Init();
}


MainScene::~MainScene()
{
}

void MainScene::Init()
{
	(*boardPtr).StartPiece({ 3,3 }, true);			// true : 通常の白黒配置, false : 白黒を反転して配置
	boardSize = (*boardPtr).GetDataSize();
	PutPieceCnt();
	SetBoardSize();
	/* プレイヤーの登録を行っている */
	MakePlayer(PL_TYPE::PL_MAN);
	MakePlayer(plType);
	player = playerList.begin();
}

void MainScene::SetBoardSize(void)
{
	
}

unique_scene MainScene::Update(unique_scene own, MouseCtl& mouse)
{
	(**player).SetTurn(true);
	/* ゲーム中の情報を描画している */
	DxLib::ClsDrawScreen();
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/gameBG.png")[0], true);
	DxLib::DrawExtendString(0, 0, 1.5f, 1.5f, "ゲームモード", 0xffffff);
	DxLib::DrawExtendString(200, 20, 1.9, 1.9f, "左クリックでコマが置けるよ", 0xffff00);
	DxLib::DrawExtendFormatString(700, 450, 1.5f, 1.5f, 0xeeee00, "白: %d", piece.w);
	DxLib::DrawExtendFormatString(25, 450, 1.5f, 1.5f, 0xeeee00, "黒: %d", piece.b);
	(*boardPtr).Draw();

	for (auto data : playerList)
	{
		(*data).Draw();
	}

	// プレイヤーのターン処理を行っている
	if ((*boardPtr).InvFlag())
	{
		if ((**player).TurnAct(mouse, *boardPtr, (**player).pGetType()))
		{
			if ((**player).pGetType() == PL_TYPE::PL_MAN)
			{
				(*boardPtr).SetReverse(mouse.GetPoint(), (**player).pGetID());
				PutPieceCnt();
				NextPlayer();
			}
			else
			{
				(*boardPtr).SetReverse((*boardPtr).PutPieceCpu(), (**player).pGetID());
				PutPieceCnt();
				NextPlayer();
			}
		}
	}

	// プレイヤーのパス処理とゲームを継続するかの管理をしている
	if ((*boardPtr).InvFlag())
	{
		if (!(*boardPtr).CheckPutPieceFlag((**player).pGetID()))
		{
			if (!AutoPassPlayer())
			{
				(*boardPtr).SetPieceCnt(piece);
				(*boardPtr).PieceClear();
				return std::make_unique<ResultScene>(boardPtr);
			}
		}
	}
	mouse.Update(PL_TYPE::PL_MAN);
	(*boardPtr).Update();
	DxLib::ScreenFlip();
	return std::move(own);
}

void MainScene::MakePlayer(PL_TYPE type)
{
	playerList.push_back(std::make_shared<Player>(boardSize, type));
}

void MainScene::NextPlayer(void)
{
	(**player).SetTurn(false);
	player++;
	if (player == playerList.end())
	{
		player = playerList.begin();
	}
	(**player).SetTurn(true);
}

bool MainScene::AutoPassPlayer(void)
{
	/* ラムダ式を実装した後個々の部分を消す*/
	NextPlayer();
	if ((*boardPtr).CheckPutPieceFlag((**player).pGetID()))
	{
		return true;
	}
	return false;
}

void MainScene::PutPieceCnt(void)
{
	piece = { 0,0 };
	/* ピースの色を取得して、それぞれの個数をカウントしている */
	for (int y = 0; y < (*boardPtr).GetDataSize().y; y++)
	{
		for (int x = 0; x < boardPtr->GetDataSize().x; x++)
		{
			if ((*boardPtr).CheckPutPieceST(x, y) == PIECE_ST::PIECE_W)
			{
				piece.w++;
			}
			else if ((*boardPtr).CheckPutPieceST(x, y) == PIECE_ST::PIECE_B)
			{
				piece.b++;
			}
			else {}
		}
	}
}