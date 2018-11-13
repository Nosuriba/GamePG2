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

	// ���N���b�N���������A�ΐ탂�[�h�̐؂�ւ����s���Ă���
	if (mouse.GetButton()[PUSH_NOW] & (~mouse.GetButton()[PUSH_OLD]) & MOUSE_INPUT_LEFT)
	{
		plType = (plType == PL_TYPE::PL_MAN ? plType = PL_TYPE::PL_CPU : plType = PL_TYPE::PL_MAN);
	}

	 // �E�N���b�N���������A�Q�[�����C���̃V�[���Ɉڍs���� 
	if (mouse.GetButton()[PUSH_NOW] & (~mouse.GetButton()[PUSH_OLD]) & MOUSE_INPUT_RIGHT)
	{
		return std::make_unique<MainScene>(plType);
	}

	// �^�C�g���̕`����s���Ă��� 
	DxLib::ClsDrawScreen();
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/title2.jpg")[0], true);
	DxLib::DrawExtendString(120, 120, 1.8, 1.8f, "���N���b�N�őΐ탂�[�h���؂�ւ���", 0xffff00);
	DxLib::DrawExtendString(120, 450, 1.8, 1.8f, "�E�N���b�N�������ƃQ�[�����n�܂��", 0xffff00);

	// �ΐ탂�[�h�̏���`�悵�Ă���
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
