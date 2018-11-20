#include "MainScene.h"
#include "ResultScene.h"
#include "GameBoard.h"
#include "Player.h"
#include "MouseCtl.h"

MainScene::MainScene(PL_TYPE plType)
{
	this->plType = plType;
	MainScene::Init();
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
	// プレイヤータイプごとのマウスの情報を設定している
	for (auto unit : PIECE_ST())
	{
		mouseCtl[unit] = std::make_shared<MouseCtl>();
		(*mouseCtl[unit]).SetPlType(PL_TYPE::MAN);
	}
	(*mouseCtl[1]).SetPlType(plType);

	boardPtr = std::make_shared<GameBoard>();

	(*boardPtr).SetPiece(3, 3, PIECE_ST::B);
	(*boardPtr).SetPiece(4, 4, PIECE_ST::B);
	(*boardPtr).SetPiece(3, 4, PIECE_ST::W);
	(*boardPtr).SetPiece(4, 3, PIECE_ST::W);

	boardSize = (*boardPtr).GetDataSize();
	PutPieceCnt();

	// プレイヤーの登録を行っている
	MakePlayer();
	MakePlayer();
	player = playerList.begin();
}

void MainScene::MakePlayer()
{
	playerList.push_back(std::make_shared<Player>(boardSize));
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
	NextPlayer();
	(*boardPtr).MakePutPieceField((**player).pGetID());
	if ((*boardPtr).CheckPutPiece())
	{
		return true;
	}
	return false;
}

void MainScene::PutPieceCnt(void)
{
	piece = { 0,0 };
	// ピースの色を取得して、それぞれの個数をカウントしている 
	for (int y = 0; y < (*boardPtr).GetDataSize().y; y++)
	{
		for (int x = 0; x < (*boardPtr).GetDataSize().x; x++)
		{
			if ((*boardPtr).CheckPutPieceST(x, y) == PIECE_ST::W)
			{
				piece.w++;
			}
			else if ((*boardPtr).CheckPutPieceST(x, y) == PIECE_ST::B)
			{
				piece.b++;
			}
			else {}
		}
	}
}

unique_scene MainScene::Update(unique_scene own, mouse_shared sysMouse)
{
	(**player).SetTurn(true);

	int mouseID = static_cast<int>((**player).pGetID());
	// プレイヤーのターン処理を行っている
	if ((*boardPtr).InvFlag())
	{
		(*boardPtr).MakePutPieceField((**player).pGetID());
		(*mouseCtl[mouseID]).Update(boardPtr);

		if ((*mouseCtl[mouseID]).GetButton()[PUSH_NOW] & (~(*mouseCtl[mouseID]).GetButton()[PUSH_OLD]) & MOUSE_INPUT_LEFT)
		{
			if ((**player).TurnAct(mouseCtl, *boardPtr))
			{
				(*boardPtr).SetReverse((*mouseCtl[mouseID]).GetPoint(), (**player).pGetID());
				PutPieceCnt();
				(*boardPtr).PutPieceClear();
				NextPlayer();
			}
		}
	}

	// プレイヤーのパス処理とゲームを継続するかの管理をしている
	if ((*boardPtr).InvFlag())
	{
		if (!(*boardPtr).CheckPutPiece())
		{
			if (!AutoPassPlayer())
			{
				(*boardPtr).SetPieceCnt(piece);
				return std::make_unique<ResultScene>(boardPtr);
			}
		}
	}
	(*boardPtr).Update();

	// ゲーム中の情報を描画している 
	DxLib::ClsDrawScreen();
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/gameBG.png")[0], true);
	DxLib::DrawExtendString(200, 20, 1.9, 1.9f, "左クリックでコマが置けるよ", 0xffff00);
	DxLib::DrawExtendFormatString(700, 450, 1.5f, 1.5f, 0xeeee00, "白: %d", piece.w);
	DxLib::DrawExtendFormatString(25, 450, 1.5f, 1.5f, 0xeeee00, "黒: %d", piece.b);
	(*boardPtr).Draw();
	for (auto data : playerList)
	{
		(*data).Draw();
	}

	DxLib::ScreenFlip();
	return std::move(own);
}

