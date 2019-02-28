#include "TitleScene.h"
#include "MainScene.h"
#include "MouseCtl.h"
#include "GameScene.h"
#include "NetWork.h"
#include "NetWorkState.h"
#include "AudioMng.h"

TitleScene::TitleScene() : netBtnPos(280, 380),
boxSize(180, 80), 
netBoxSize(240, 80),
boxOffset(10)
{
	plType[0] = PL_TYPE::MAN;
	plType[1] = PL_TYPE::CPU;

	TitleScene::Init();
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
}

void TitleScene::DrawPlType()
{
	for (int i = 0; i < static_cast<int>(PL_TYPE::NET); i++)
	{
		plColor = (i == 0 ? plColor = 0x7fbfff : plColor = 0xff4500);

		DrawBox(pPos[i], pPos[i] + boxSize + Vector2(boxOffset, boxOffset), 0x666666, true);

		// プレイヤーの描画
		if (plType[i] == PL_TYPE::MAN)
		{
			DxLib::DrawExtendString(pPos[i].x, pPos[i].y, 3.0f, 3.0f, "Player", plColor);
		}
		else
		{
			DxLib::DrawExtendString(pPos[i].x, pPos[i].y, 3.0f, 3.0f, "CPU ", plColor);
		}
	}

	DxLib::DrawExtendString(LpGameScene.GetScreenSize().x / 2 - 30,  pPos[0].y, 3.0f, 3.0f, "VS", 0xffff00);
}

unique_scene TitleScene::Update(unique_scene own, mouse_shared sysMouse)
{
	LpAudioMng.PlayBGM(LpAudioMng.GetSound().titleBGM);
	LpAudioMng.ChangeVolume(70, LpAudioMng.GetSound().titleBGM);
	Vector2 onlinePos = { netBtnPos.x, (netBtnPos.y + netBoxSize.y) + 40 };

	if (lpNetWork.GetState() != NetState::READY)
	{
		if ((*sysMouse).GetButton()[PUSH_NOW] & (~(*sysMouse).GetButton()[PUSH_OLD]) & MOUSE_INPUT_LEFT)
		{
			if ((*sysMouse).GetPoint() > pPos[0] & (*sysMouse).GetPoint() <= pPos[0] + boxSize)
			{
				LpAudioMng.PlaySE(LpAudioMng.GetSound().changeSE);
				plType[0] = (PL_TYPE)(1 ^ static_cast<int>(plType[0]));
			}
			else if ((*sysMouse).GetPoint() > pPos[1] & (*sysMouse).GetPoint() <= pPos[1] + boxSize)
			{
				LpAudioMng.PlaySE(LpAudioMng.GetSound().changeSE);
				plType[1] = (PL_TYPE)(1 ^ static_cast<int>(plType[1]));
			}
			else if ((*sysMouse).GetPoint() >  netBtnPos &
					 (*sysMouse).GetPoint() <= netBtnPos + netBoxSize)
			{
				LpAudioMng.PlaySE(LpAudioMng.GetSound().decideSE);
				return std::make_unique<MainScene>(plType);
			}
			else if (((*sysMouse).GetPoint() >  onlinePos &
					  (*sysMouse).GetPoint() <= onlinePos + netBoxSize))
			{
				LpAudioMng.PlaySE(LpAudioMng.GetSound().decideSE);
				/// ホストまたはゲストの設定を行う
				if (lpNetWork.GetState() == NetState::NON)
				{
					if (!lpNetWork.SetNetWorkMode(NetWorkMode::GUEST))
					{
						lpNetWork.SetNetWorkMode(NetWorkMode::HOST);
					}
				}
				 LpGameScene.StartTime();
			}
			else {}
		}
	}
	else
	{
		lpNetWork();
		LpGameScene.EndTime();
		if (LpGameScene.GetSecondsTime() > 4)
		{
			LpAudioMng.PlaySE(LpAudioMng.GetSound().closeNetSE);
			lpNetWork.CloseNetWork();
			LpGameScene.ResetTime();
		}
	}

	// タイトルの描画を行っている 
	DxLib::ClsDrawScreen();
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("resource/image/title2.jpg")[0], true);
	DxLib::DrawExtendString(100, 120, 1.8, 1.8f, "左クリックでプレイヤーが切り替わるよ", 0xffff00);
	DrawPlType();
	// オフラインモードの表示位置
	DxLib::DrawBox(netBtnPos.x - boxOffset, netBtnPos.y - boxOffset,
				   netBtnPos.x + netBoxSize.x, netBtnPos.y + netBoxSize.y,
				   0xf0e68c, true);
	DxLib::DrawExtendString(netBtnPos.x, netBtnPos.y + boxOffset, 2.5f, 2.5f, "Offline", 0x1e90ff);

	// オンラインモードの表示位置
	DxLib::DrawBox(onlinePos.x - boxOffset, onlinePos.y - boxOffset,
				   onlinePos.x + netBoxSize.x, onlinePos.y + netBoxSize.y,
				   0xf0e68c, true);
	DxLib::DrawExtendString(onlinePos.x, onlinePos.y + boxOffset, 2.5f, 2.5f, "online", 0x1e90ff);
	lpNetWork.Draw();
	DxLib::ScreenFlip();

	if (lpNetWork.GetState() != NetState::NON)
	{
		if (lpNetWork.GetState() == NetState::START_WAIT || 
			lpNetWork.GetState() == NetState::ACTIVE)
		{
			LpAudioMng.PlaySE(LpAudioMng.GetSound().decideSE);
			return std::make_unique<MainScene>(plType);
		}
	}
	return std::move(own);
}
