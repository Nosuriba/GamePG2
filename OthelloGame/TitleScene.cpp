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
	// 1P�̕`��
	if (plType[0] == PL_TYPE::MAN)
	{
		DxLib::DrawExtendString(100, 270, 3.0f, 3.0f, "Player    VS", 0xff0000);
	}
	else
	{
		DxLib::DrawExtendString(100, 270, 3.0f, 3.0f, "CPU       VS", 0xff0000);
	}

	// 2P�̕`��
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
	// ���N���b�N���������A�ΐ탂�[�h�̐؂�ւ����s���Ă���
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

	 // �E�N���b�N���������A�Q�[�����C���̃V�[���Ɉڍs���� 
	if ((*sysMouse).GetButton()[PUSH_NOW] & (~(*sysMouse).GetButton()[PUSH_OLD]) & MOUSE_INPUT_LEFT)
	{
		return std::make_unique<MainScene>(plType);
	}

	// �^�C�g���̕`����s���Ă��� 
	DxLib::ClsDrawScreen();
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/title2.jpg")[0], true);
	DxLib::DrawExtendString(120, 120, 1.8, 1.8f, "�E�N���b�N�őΐ탂�[�h�̕ύX���ł����", 0xffff00);
	DxLib::DrawExtendString(120, 450, 1.8, 1.8f, "���N���b�N�������ƃQ�[�����n�܂��", 0xffff00);

	DrawPlType();

	DxLib::ScreenFlip();

	return std::move(own);
}
