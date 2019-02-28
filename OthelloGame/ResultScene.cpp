#include "ResultScene.h"
#include "TitleScene.h"
#include "MouseCtl.h"
#include "GameBoard.h"
#include "AudioMng.h"
#include "NetWork.h"

ResultScene::ResultScene(std::shared_ptr<GameBoard> gBoard)
{
	lpNetWork.CloseNetWork();
	this->gBoard = gBoard;
	dispCnt		 = 0;
	animCnt		 = 0;
	piece		 = (*gBoard).GetPieceCnt();
	pCnt		 = 0;
	pCntMax		 = (piece.b + piece.w);
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
		DxLib::DrawExtendString(240, 5, 2.5f, 2.5f, "先手[黒]の勝利なり", 0xaaaaaa);
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
	DxLib::ClsDrawScreen();
	if ((*sysMouse).GetButton()[PUSH_NOW] & (~(*sysMouse).GetButton()[PUSH_OLD]) & MOUSE_INPUT_LEFT && putFlag)
	{
		LpAudioMng.PlaySE(LpAudioMng.GetSound().decideSE);
		return std::make_unique<TitleScene>();
	}

	if (pCnt == pCntMax)
	{	
		if (!putFlag)
		{
			if (dispCnt > 40)
			{
				putFlag = true;
				LpAudioMng.PlaySE(LpAudioMng.GetSound().countEndSE);
				dispCnt = 0;
			}
			else
			{
				dispCnt++;
			}
		}	
	}
	else
	{
		LpAudioMng.StopBGM();
		if (dispCnt > 6)
		{
			LpAudioMng.PlaySE(LpAudioMng.GetSound().countSE);
			if (pCnt < piece.b)
			{
				(*gBoard).ResultPiece(pCnt, PIECE_ST::B);
			}
			else
			{
				(*gBoard).ResultPiece(pCnt, PIECE_ST::W);
			}
			pCnt++;
			dispCnt = 0;
		}
		else
		{
			dispCnt++;
		}
	}

	// リザルトの情報を描画している 
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("resource/image/gameBG.png")[0], true);
	(*gBoard).Draw();
	if (putFlag)
	{
		DrawWinner(WinJudge(piece));
		DxLib::DrawExtendFormatString(700, 100, 3.f, 3.f, 0xfffacd, "%d", piece.w);
		DxLib::DrawExtendFormatString(50,  100, 3.f, 3.f, 0x999999, "%d", piece.b);
		if (!((animCnt / 30) % 2))
		{
			DxLib::DrawExtendString(150, 550, 2.f, 2.f, "左クリックでタイトルに戻るよ", 0xffd700);
		}
		if (dispCnt > 60)
		{
			animCnt++;
			LpAudioMng.PlayBGM(LpAudioMng.GetSound().resultBGM);
		}
		else
		{
			dispCnt++;
		}
	}
	
	DxLib::ScreenFlip();

	return std::move(own);
}