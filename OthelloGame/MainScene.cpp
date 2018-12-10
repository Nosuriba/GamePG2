#include "MainScene.h"
#include "ResultScene.h"
#include "GameBoard.h"
#include "Player.h"
#include "MouseCtl.h"
#include "GameScene.h"

MainScene::MainScene(std::array<PL_TYPE, static_cast<int>(PL_TYPE::MAX)> plType) : plBoxSize(80, 40)
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
	}
	(*mouseCtl[0]).SetPlType(plType[0]);
	(*mouseCtl[1]).SetPlType(plType[1]);

	gBoard = std::make_shared<GameBoard>();
	(*gBoard).SetPiece(3, 3, PIECE_ST::B);
	(*gBoard).SetPiece(4, 4, PIECE_ST::B);
	(*gBoard).SetPiece(3, 4, PIECE_ST::W);
	(*gBoard).SetPiece(4, 3, PIECE_ST::W);

	boardSize = (*gBoard).GetDataSize();
	piece = (*gBoard).PutPieceCnt();

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
	(*gBoard).MakePutPieceField((**player).pGetID());
	if ((*gBoard).CheckPutPiece())
	{
		return true;
	}
	return false;
}

void MainScene::DrawPlType(void)
{
	for (int i = 0; i < static_cast<int>(PIECE_ST::NON); i++)
	{
		DrawBox(plPos[i], plPos[i] + plBoxSize, 0x666666, true);
	}

	// 1Pの描画
	if ((*mouseCtl[static_cast<int>(PIECE_ST::B)]).GetPlType() == PL_TYPE::MAN)
	{
		DxLib::DrawExtendString(plPos[0].x, plPos[0].y, 1.5f, 1.5f,"Player", 0x7fbfff);
	}
	else
	{
		DxLib::DrawExtendString(plPos[0].x, plPos[0].y, 1.5f, 1.5f, "CPU", 0x7fbfff);
	}

	// 2Pの描画
	if ((*mouseCtl[static_cast<int>(PIECE_ST::W)]).GetPlType() == PL_TYPE::MAN)
	{
		DxLib::DrawExtendString(plPos[1].x, plPos[1].y, 1.5f, 1.5f, "Player", 0xff4500);
	}
	else
	{
		DxLib::DrawExtendString(plPos[1].x, plPos[1].y, 1.5f, 1.5f, "CPU", 0xff4500);
	}
}

unique_scene MainScene::Update(unique_scene own, mouse_shared sysMouse)
{
	(**player).SetTurn(true);
	int mouseID = static_cast<int>((**player).pGetID());

	// アクティブなプレイヤーのターン処理
	if ((*gBoard).InvFlag())
	{
		// 反転処理を行っていない時に置ける位置の登録を行っている
		if (!reverseFlag)
		{
			(*gBoard).MakePutPieceField((**player).pGetID());
		}
		
		(*mouseCtl[mouseID]).Update(gBoard, (**player).pGetID());

		if ((*mouseCtl[mouseID]).GetButton()[PUSH_NOW] & (~(*mouseCtl[mouseID]).GetButton()[PUSH_OLD]) & MOUSE_INPUT_LEFT)
		{
			if ((**player).TurnAct(mouseCtl, *gBoard))
			{
				reverseFlag = true;
				mPos = (*mouseCtl[mouseID]).GetPoint();
			}
		}

		// ゲーム中にプレイヤーを動的に切り替えれるようにしている
		if ((*sysMouse).GetButton()[PUSH_NOW] & (~(*sysMouse).GetButton()[PUSH_OLD]) & MOUSE_INPUT_LEFT)
		{
			if ((*sysMouse).GetPoint() >  plPos[static_cast<int>(PIECE_ST::B)] &
				(*sysMouse).GetPoint() <= plPos[static_cast<int>(PIECE_ST::B)] + Vector2(plBoxSize.x, plBoxSize.y))
			{
				/// 1Pの状態を変更している
				PL_TYPE pTypeB = (*mouseCtl[static_cast<int>(PIECE_ST::B)]).GetPlType();
				(*mouseCtl[static_cast<int>(PIECE_ST::B)]).SetPlType((PL_TYPE)(1 ^ (int)(pTypeB)));
			}
			else if (((*sysMouse).GetPoint() >  plPos[static_cast<int>(PIECE_ST::W)] &
				      (*sysMouse).GetPoint() <= plPos[static_cast<int>(PIECE_ST::W)] + Vector2(plBoxSize.x, plBoxSize.y)))
			{
				/// 2Pの状態を変更している
				PL_TYPE pTypeW = (*mouseCtl[static_cast<int>(PIECE_ST::W)]).GetPlType();
				(*mouseCtl[static_cast<int>(PIECE_ST::W)]).SetPlType((PL_TYPE)(1 ^ (int)(pTypeW)));
			}
			else {}
		}
	}

	// 間隔を空けて反転処理を行うようにしている
	if (reverseFlag)
	{
		if ((*gBoard).InvFlag(reverseFlag))
		{
			reverseFlag = false;
			(*gBoard).SetReverse(mPos, (**player).pGetID());
			piece = (*gBoard).PutPieceCnt();
			(*gBoard).PutPieceClear();
			NextPlayer();
		}
	}

	// プレイヤーのパス処理とゲームを継続するかの管理をしている
	if ((*gBoard).InvFlag())
	{
		if (!(*gBoard).CheckPutPiece())
		{
			if (!AutoPassPlayer())
			{
				(*gBoard).SetPieceCnt(piece);
				return std::make_unique<ResultScene>(gBoard);
			}
		}
	}
	(*gBoard).Update();

	DxLib::ClsDrawScreen();
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/gameBG.png")[0], true);

	// 操作方法のテキストを描画している
	DxLib::DrawExtendString(200, 10, 1.5f, 1.5f, "左クリックでコマが置けるよ", 0xffff00);
	// 現在のピースの個数を描画している
	DxLib::DrawExtendFormatString(pCntPos[0].x, pCntPos[0].y, 1.5f, 1.5f, 0xeeee00, "黒: %d", piece.b);
	DxLib::DrawExtendFormatString(pCntPos[1].x, pCntPos[1].y, 1.5f, 1.5f, 0xeeee00, "白: %d", piece.w);

	DrawPlType();

	// 盤面の情報を描画している
	(*gBoard).Draw();

	// プレイヤーの持ちコマの情報を描画している
	for (auto data : playerList)
	{
		(*data).Draw();
	}
	DxLib::DrawFormatString(10, 550, 0xffdd00, "%d マイクロ秒", LpGameScene.GetMicroTime());

	DxLib::ScreenFlip();
	return std::move(own);
}

