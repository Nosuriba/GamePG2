#include "MainScene.h"
#include "ResultScene.h"
#include "GameBoard.h"
#include "Player.h"
#include "MouseCtl.h"

MainScene::MainScene(std::array<PL_TYPE, static_cast<int>(PL_TYPE::MAX)> plType)
{
	this->plType = plType;
	reverseFlag = false;
	mPos = { 0,0 };
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
	(*mouseCtl[0]).SetPlType(plType[0]);
	(*mouseCtl[1]).SetPlType(plType[1]);

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

void MainScene::DrawPlType(void)
{
	// 1Pの描画
	if ((*mouseCtl[static_cast<int>(PIECE_ST::B)]).GetPlType() == PL_TYPE::MAN)
	{
		DxLib::DrawExtendString(25, 60, 1.5f, 1.5f,"Player", 0x7fbfff);
	}
	else
	{
		DxLib::DrawExtendString(25, 60, 1.5f, 1.5f, "CPU", 0x7fbfff);
	}

	// 2Pの描画
	if ((*mouseCtl[static_cast<int>(PIECE_ST::W)]).GetPlType() == PL_TYPE::MAN)
	{
		DxLib::DrawExtendString(700, 60, 1.5f, 1.5f, "Player", 0xff4500);
	}
	else
	{
		DxLib::DrawExtendString(700, 60, 1.5f, 1.5f, "CPU", 0xff4500);
	}
}

unique_scene MainScene::Update(unique_scene own, mouse_shared sysMouse)
{
	(**player).SetTurn(true);
	int mouseID = static_cast<int>((**player).pGetID());

	// アクティブなプレイヤーのターン処理
	if ((*boardPtr).InvFlag())
	{
		// 反転処理を行っていない時に置ける位置の登録を行っている
		if (!reverseFlag)
		{
			(*boardPtr).MakePutPieceField((**player).pGetID());
		}
		
		(*mouseCtl[mouseID]).Update(boardPtr);

		if ((*mouseCtl[mouseID]).GetButton()[PUSH_NOW] & (~(*mouseCtl[mouseID]).GetButton()[PUSH_OLD]) & MOUSE_INPUT_LEFT)
		{
			if ((**player).TurnAct(mouseCtl, *boardPtr))
			{
				reverseFlag = true;
				mPos = (*mouseCtl[mouseID]).GetPoint();
			}
		}

		// ゲーム中にプレイヤーを動的に切り替えれるようにしている
		if ((*sysMouse).GetButton()[PUSH_NOW] & (~(*sysMouse).GetButton()[PUSH_OLD]) & MOUSE_INPUT_RIGHT)
		{
			if ((*mouseCtl[mouseID]).GetPlType() == PL_TYPE::MAN)
			{
				(*mouseCtl[mouseID]).SetPlType(PL_TYPE::CPU);
			}
			else
			{
				(*mouseCtl[mouseID]).SetPlType(PL_TYPE::MAN);
			}
		}
	}

	// 間隔を空けて反転処理を行うようにしている
	if (reverseFlag)
	{
		if ((*boardPtr).InvFlag(reverseFlag))
		{
			reverseFlag = false;
			(*boardPtr).SetReverse(mPos, (**player).pGetID());
			PutPieceCnt();
			(*boardPtr).PutPieceClear();
			NextPlayer();
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

	DxLib::ClsDrawScreen();
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/gameBG.png")[0], true);

	// 操作方法のテキストを描画している
	DxLib::DrawExtendString(50, 10, 1.3f, 1.3f, "左クリックでコマが置けるよ /", 0xffff00);
	DxLib::DrawExtendString(375, 10, 1.3f, 1.3f, "右クリックでプレイヤーが切り替わるよ", 0xffff00);

	// 現在のピースの個数を描画している
	DxLib::DrawExtendFormatString(25, 450, 1.5f, 1.5f, 0xeeee00, "黒: %d", piece.b);
	DxLib::DrawExtendFormatString(700, 450, 1.5f, 1.5f, 0xeeee00, "白: %d", piece.w);

	DrawPlType();

	// 盤面の情報を描画している
	(*boardPtr).Draw();

	// プレイヤーの持ちコマの情報を描画している
	for (auto data : playerList)
	{
		(*data).Draw();
	}

	DxLib::ScreenFlip();
	return std::move(own);
}

