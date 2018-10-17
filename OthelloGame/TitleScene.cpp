#include "TitleScene.h"
#include "MouseCtl.h"

TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

int TitleScene::Update()
{
	return 0;
}

void TitleScene::Draw()
{
}

int TitleScene::TitleInit()
{
	mousePtr = std::make_unique<MouseCtl>();
	/* �o�^���ꂽ�v���C���[�̏��������s���Ă��� */
	return 0;
}

int TitleScene::TitleMain()
{
	if (mousePtr->GetButton()[PUSH_NOW] & (~mousePtr->GetButton()[PUSH_OLD]) & MOUSE_INPUT_RIGHT)
	{
		/*gScenePtr = &GameScene::GameInit;*/
	}
	mousePtr->Update();
	DxLib::ClsDrawScreen();

	/* �^�C�g���̕`����s���Ă��� */
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/title.jpg")[0], true);
	DxLib::DrawExtendString(0, 0, 2.5f, 2.5f, "�^�C�g��", 0xffff00);
	DxLib::ScreenFlip();

	return 0;
}