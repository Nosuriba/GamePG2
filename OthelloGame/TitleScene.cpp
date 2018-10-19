#include "TitleScene.h"
#include "MainScene.h"
#include "MouseCtl.h"

TitleScene::TitleScene()
{
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
	mouse.Update();
	/* 右クリックをした時、ゲームメインのシーンに移行する */
	if (mouse.GetButton()[PUSH_NOW] & (~mouse.GetButton()[PUSH_OLD]) & MOUSE_INPUT_RIGHT)
	{
		return std::make_unique<MainScene>();
	}

	/* タイトルの描画を行っている */
	DxLib::ClsDrawScreen();
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/title.jpg")[0], true);
	DxLib::DrawExtendString(0, 0, 2.5f, 2.5f, "タイトル", 0xffff00);
	DxLib::ScreenFlip();

	return std::move(own);
}
