#include "ResultScene.h"
#include "TitleScene.h"
#include "MouseCtl.h"
#include "GameBoard.h"

ResultScene::ResultScene(std::shared_ptr<GameBoard> gBoard)
{
	/* ここsharedで動かしてみる(動いたらuniqueに変えておく)*/
	boardPtr = gBoard;
	piece	 = boardPtr->GetPieceCnt();
}


ResultScene::~ResultScene()
{
}

PIECE_ST ResultScene::WinJudge(int pCntB, int pCntW)
{
	/* ピースの個数を比較して、個数が多い色の状態を返すようにしている*/
	if (pCntB < pCntW)
	{
		return PIECE_W;
	}
	else if (pCntB > pCntW)
	{
		return PIECE_B;
	}
	else if (pCntB == pCntW)
	{
		return PIECE_NON;
	}
	return PIECE_NON;
}

void ResultScene::DrawWinner(PIECE_ST pState)
{
	if (pState == PIECE_B)
	{
		DxLib::DrawExtendString(250, 0, 2.5f, 2.5f, "先手[黒]の勝利なり", 0xfffacd);
	}
	else if (pState == PIECE_W)
	{
		DxLib::DrawExtendString(250, 0, 2.5f, 2.5f, "後手[白]の勝利なり", 0xf0f8ff);
	}
	else
	{
		DxLib::DrawExtendString(300, 0, 2.5f, 2.5f, "決着つかず...", 0xeeee00);
	}
}



void ResultScene::Init()
{
}

unique_scene ResultScene::Update(unique_scene own, MouseCtl& mouse)
{
	if (mouse.GetButton()[PUSH_NOW] & (~mouse.GetButton()[PUSH_OLD]) & MOUSE_INPUT_RIGHT)
	{
		return std::make_unique<TitleScene>();
	}
	boardPtr->ResultPiece(piece.b, piece.w);
	/* マウスのクリックが押した瞬間になっていないので、そこの修正を行う*/
	mouse.Update();

	/* リザルトの情報を描画している */
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/gameBG.png")[0], true);
	DxLib::DrawExtendString(0, 0, 1.5f, 1.5f, "リザルト", 0xffffff);
	boardPtr->Draw();
	DrawWinner(WinJudge(piece.b, piece.w));
	DxLib::DrawExtendFormatString(0, 170, 1.3f, 1.3f, 0xfffffff, "白 : %d", piece.w);
	DxLib::DrawExtendFormatString(0, 200, 1.3f, 1.3f, 0xfffffff, "黒 : %d", piece.b);
	DxLib::ScreenFlip();

	return std::move(own);
}