#include "TitleScene.h"
#include "MainScene.h"
#include "MouseCtl.h"

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
	// 1Pの描画
	if (plType[0] == PL_TYPE::MAN)
	{
		DxLib::DrawExtendString(100, 270, 3.0f, 3.0f, "Player    VS", 0xff0000);
	}
	else
	{
		DxLib::DrawExtendString(100, 270, 3.0f, 3.0f, "CPU       VS", 0xff0000);
	}

	// 2Pの描画
	if (plType[1] == PL_TYPE::MAN)
	{
		DxLib::DrawExtendString(550, 270, 3.0f, 3.0f, "Player", 0xff0000);
	}
	else
	{
		DxLib::DrawExtendString(550, 270, 3.0f, 3.0f, "CPU", 0xff0000);
	}
}

unique_scene TitleScene::Update(unique_scene own, mouse_shared sysMouse)
{
	// 左クリックをした時、対戦モードの切り替えを行っている
	if ((*sysMouse).GetButton()[PUSH_NOW] & (~(*sysMouse).GetButton()[PUSH_OLD]) & MOUSE_INPUT_RIGHT)
	{
		if (plType[0] == plType[1] & plType[0] == PL_TYPE::MAN)
		{
			plType[0] = PL_TYPE::CPU;
		}
		else if (plType[0] == plType[1] & plType[0] == PL_TYPE::CPU)
		{
			plType[0] = PL_TYPE::MAN;
		}
		else
		{
			plType[1] = plType[0];
		}
	}

	 // 右クリックをした時、ゲームメインのシーンに移行する 
	if ((*sysMouse).GetButton()[PUSH_NOW] & (~(*sysMouse).GetButton()[PUSH_OLD]) & MOUSE_INPUT_LEFT)
	{
		return std::make_unique<MainScene>(plType);
	}

	// タイトルの描画を行っている 
	DxLib::ClsDrawScreen();
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/title2.jpg")[0], true);
	DxLib::DrawExtendString(120, 120, 1.8, 1.8f, "右クリックで対戦モードの変更ができるよ", 0xffff00);
	DxLib::DrawExtendString(120, 450, 1.8, 1.8f, "左クリックを押すとゲームが始まるよ", 0xffff00);

	DrawPlType();

	DxLib::ScreenFlip();

	return std::move(own);
}
