#include "TitleScene.h"
#include "MouseCtl.h"

TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

bool TitleScene::Update()
{
	bool rtnFlag = false;
	TitleScene::TitleInit();
	rtnFlag = TitleScene::Update();
	return rtnFlag;
}

void TitleScene::Draw()
{
	DxLib::ClsDrawScreen();
	/* タイトルの描画を行っている */
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/title.jpg")[0], true);
	DxLib::DrawExtendString(0, 0, 2.5f, 2.5f, "タイトル", 0xffff00);
	DxLib::ScreenFlip();

}

int TitleScene::TitleInit()
{
	if (!mousePtr)
	{
		mousePtr = std::make_unique<MouseCtl>();
	}
	return 0;
}

bool TitleScene::TitleMain()
{
	if (mousePtr->GetButton()[PUSH_NOW] & (~mousePtr->GetButton()[PUSH_OLD]) & MOUSE_INPUT_RIGHT)
	{
		return true;
	}
	mousePtr->Update();
	TitleScene::Draw();
	
	return false;
}