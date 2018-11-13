#include "TitleScene.h"
#include "MainScene.h"
#include "MouseCtl.h"

TitleScene::TitleScene()
{
	plType = PL_TYPE::PL_CPU;
	TitleScene::Init();
}


TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
}

unique_scene TitleScene::Update(unique_scene own, MouseCtl& mouse)
{
	mouse.Update(PL_TYPE::PL_MAN);

	// 左クリックをした時、対戦モードの切り替えを行っている
	if (mouse.GetButton()[PUSH_NOW] & (~mouse.GetButton()[PUSH_OLD]) & MOUSE_INPUT_LEFT)
	{
		plType = (plType == PL_TYPE::PL_MAN ? plType = PL_TYPE::PL_CPU : plType = PL_TYPE::PL_MAN);
	}

	 // 右クリックをした時、ゲームメインのシーンに移行する 
	if (mouse.GetButton()[PUSH_NOW] & (~mouse.GetButton()[PUSH_OLD]) & MOUSE_INPUT_RIGHT)
	{
		return std::make_unique<MainScene>(plType);
	}

	// タイトルの描画を行っている 
	DxLib::ClsDrawScreen();
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/title2.jpg")[0], true);
	DxLib::DrawExtendString(120, 120, 1.8, 1.8f, "左クリックで対戦モードが切り替わるよ", 0xffff00);
	DxLib::DrawExtendString(120, 450, 1.8, 1.8f, "右クリックを押すとゲームが始まるよ", 0xffff00);

	// 対戦モードの情報を描画している
	if (plType == PL_TYPE::PL_CPU)
	{
		DxLib::DrawExtendString(100, 270, 3.0f, 3.0f, "Player    VS    CPU", 0xff0000);
	}
	else
	{
		DxLib::DrawExtendString(100, 270, 3.0f, 3.0f, "Player    VS    Player", 0xff0000);
	}
	DxLib::ScreenFlip();

	return std::move(own);
}
