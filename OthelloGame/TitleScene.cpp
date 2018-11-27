#include "TitleScene.h"
#include "MainScene.h"
#include "MouseCtl.h"

#define PL_BOX_SIZE_X (180)
#define PL_BOX_SIZE_Y (80)
#define PL_BOX_OFFSET (10)

TitleScene::TitleScene()
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

void TitleScene::DrawPlType(void)
{
	for (int i = 0; i < static_cast<int>(PL_TYPE::SYS); i++)
	{
		DrawBox(pPos[i].x - PL_BOX_OFFSET, pPos[i].y - PL_BOX_OFFSET, 
				pPos[i].x + PL_BOX_SIZE_X - PL_BOX_OFFSET, pPos[i].y + PL_BOX_SIZE_Y - PL_BOX_OFFSET,
				0xc0c0c0, true);
	}
	
	// 1Pの描画
	if (plType[0] == PL_TYPE::MAN)
	{
		DxLib::DrawExtendString(pPos[0].x, pPos[0].y, 3.0f, 3.0f, "Player    VS", 0xff0000);
	}
	else
	{
		DxLib::DrawExtendString(pPos[0].x, pPos[0].y, 3.0f, 3.0f, "CPU       VS", 0xff0000);
	}

	// 2Pの描画
	if (plType[1] == PL_TYPE::MAN)
	{
		DxLib::DrawExtendString(pPos[1].x, pPos[1].y, 3.0f, 3.0f, "Player", 0xff0000);
	}
	else
	{
		DxLib::DrawExtendString(pPos[1].x, pPos[1].y, 3.0f, 3.0f, "CPU", 0xff0000);
	}
}

unique_scene TitleScene::Update(unique_scene own, mouse_shared sysMouse)
{
	 // 右クリックをした時、ゲームメインのシーンに移行する 
	if ((*sysMouse).GetButton()[PUSH_NOW] & (~(*sysMouse).GetButton()[PUSH_OLD]) & MOUSE_INPUT_LEFT)
	{
		if ((*sysMouse).GetPoint() > pPos[0] & (*sysMouse).GetPoint() <= pPos[0] + Vector2(PL_BOX_SIZE_X, PL_BOX_SIZE_Y))
		{
			if (plType[0] == PL_TYPE::MAN)
			{
				plType[0] = PL_TYPE::CPU;
			}
			else
			{
				plType[0] = PL_TYPE::MAN;
			}
		}
		else if ((*sysMouse).GetPoint() > pPos[1] & (*sysMouse).GetPoint() <= pPos[1] + Vector2(PL_BOX_SIZE_X, PL_BOX_SIZE_Y))
		{
			if (plType[1] == PL_TYPE::MAN)
			{
				plType[1] = PL_TYPE::CPU;
			}
			else
			{
				plType[1] = PL_TYPE::MAN;
			}
		}
		else
		{
			return std::make_unique<MainScene>(plType);
		}
		
	}

	// タイトルの描画を行っている 
	DxLib::ClsDrawScreen();
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/title2.jpg")[0], true);
	DxLib::DrawExtendString(100, 120, 1.8, 1.8f, "枠内を左クリック : プレイヤーの切り替え", 0xffff00);
	DxLib::DrawExtendString(100, 180, 1.8, 1.8f, "枠外を左クリック : ゲームスタート", 0xffff00);

	DrawPlType();

	DxLib::ScreenFlip();

	return std::move(own);
}
