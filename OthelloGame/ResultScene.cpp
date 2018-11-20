#include "ResultScene.h"
#include "TitleScene.h"
#include "MouseCtl.h"
#include "GameBoard.h"

ResultScene::ResultScene(std::shared_ptr<GameBoard> gBoard)
{
	boardPtr = gBoard;
	piece	 = (*boardPtr).GetPieceCnt();
}

ResultScene::~ResultScene()
{
}

void ResultScene::Init()
{
}

PIECE_ST ResultScene::WinJudge(PutPiece piece)
{
	if (piece.b < piece.w)			// 白の勝利
	{
		return PIECE_ST::W;
	}
	else if (piece.b > piece.w)		// 黒の勝利
	{
		return PIECE_ST::B;
	}
	else if (piece.b == piece.w)	// 引き分け
	{
		return PIECE_ST::NON;
	}
	return PIECE_ST::NON;
}

void ResultScene::DrawWinner(PIECE_ST pState)
{
	// 勝者の描画
	if (pState == PIECE_ST::B)
	{
		DxLib::DrawExtendString(240, 5, 2.5f, 2.5f, "先手[黒]の勝利なり", 0xfffacd);
	}
	else if (pState == PIECE_ST::W)
	{
		DxLib::DrawExtendString(240, 5, 2.5f, 2.5f, "後手[白]の勝利なり", 0xf0f8ff);
	}
	else
	{
		// 引き分けの時の描画
		DxLib::DrawExtendString(300, 5, 2.5f, 2.5f, "決着つかず...", 0xeeee00);
	}
}

unique_scene ResultScene::Update(unique_scene own, mouse_shared sysMouse)
{
	// 右クリックをした時、タイトルのシーンに移行している
	if ((*sysMouse).GetButton()[PUSH_NOW] & (~(*sysMouse).GetButton()[PUSH_OLD]) & MOUSE_INPUT_LEFT)
	{
		return std::make_unique<TitleScene>();
	}
	// ピースの並び替えを行っている 
	(*boardPtr).ResultPiece(piece);

	// リザルトの情報を描画している 
	DxLib::ClsDrawScreen();
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/gameBG.png")[0], true);
	(*boardPtr).Draw();
	DrawWinner(WinJudge(piece));
	// DxLib::DrawExtendString(60, 300, 2.2f, 2.2f, "左クリックを押すとタイトル画面に戻るよ", 0xffff00);
	DxLib::DrawExtendFormatString(700, 450, 1.5f, 1.5f, 0xeeee00, "白: %d", piece.w);
	DxLib::DrawExtendFormatString(25 , 450, 1.5f, 1.5f, 0xeeee00, "黒: %d", piece.b);
	DxLib::ScreenFlip();

	return std::move(own);
}