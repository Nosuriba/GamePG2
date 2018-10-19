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
	/* �E�N���b�N���������A�Q�[�����C���̃V�[���Ɉڍs���� */
	if (mouse.GetButton()[PUSH_NOW] & (~mouse.GetButton()[PUSH_OLD]) & MOUSE_INPUT_RIGHT)
	{
		return std::make_unique<MainScene>();
	}

	/* �^�C�g���̕`����s���Ă��� */
	DxLib::ClsDrawScreen();
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/title.jpg")[0], true);
	DxLib::DrawExtendString(0, 0, 2.5f, 2.5f, "�^�C�g��", 0xffff00);
	DxLib::ScreenFlip();

	return std::move(own);
}
