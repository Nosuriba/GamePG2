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

PIECE_ST ResultScene::WinJudge(PutPiece piece)
{
	/* ピースの個数を比較して、個数が多いピースの状態を返すようにしている*/
	if (piece.b < piece.w)
	{
		return PIECE_W;
	}
	else if (piece.b > piece.w)
	{
		return PIECE_B;
	}
	else if (piece.b == piece.w)
	{
		return PIECE_NON;
	}
	return PIECE_NON;
}

void ResultScene::DrawWinner(PIECE_ST pState)
{
	/* 引数で勝者のピースの状態を取得し、
	   描画を行っている */
	if (pState == PIECE_B)
	{
		DxLib::DrawExtendString(240, 0, 2.5f, 2.5f, "先手[黒]の勝利なり", 0xfffacd);
	}
	else if (pState == PIECE_W)
	{
		DxLib::DrawExtendString(240, 0, 2.5f, 2.5f, "後手[白]の勝利なり", 0xf0f8ff);
	}
	else
	{
		/* 勝者が決まらなかった時の描画 */
		DxLib::DrawExtendString(300, 0, 2.5f, 2.5f, "決着つかず...", 0xeeee00);
	}
}



void ResultScene::Init()
{
}

unique_scene ResultScene::Update(unique_scene own, MouseCtl& mouse)
{
	mouse.Update();
	/* 右クリックをした時、タイトルのシーンに移行している*/
	if (mouse.GetButton()[PUSH_NOW] & (~mouse.GetButton()[PUSH_OLD]) & MOUSE_INPUT_RIGHT)
	{
		return std::make_unique<TitleScene>();
	}
	/* ピースの並び替えを行っている */
	(*boardPtr).ResultPiece(piece);
	
	/* リザルトの情報を描画している */
	DxLib::ClsDrawScreen();
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/gameBG.png")[0], true);
	DxLib::DrawExtendString(0, 0, 1.5f, 1.5f, "リザルト", 0xffffff);
	(*boardPtr).Draw();
	DrawWinner(WinJudge(piece));
	DxLib::DrawExtendFormatString(700, 450, 1.5f, 1.5f, 0xeeee00, "白: %d", piece.w);
	DxLib::DrawExtendFormatString(25, 450, 1.5f, 1.5f, 0xeeee00, "黒: %d", piece.b);
	DxLib::ScreenFlip();

	return std::move(own);
}