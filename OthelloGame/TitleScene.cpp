#include "TitleScene.h"
#include "MainScene.h"
#include "MouseCtl.h"
#include "GameScene.h"

TitleScene::TitleScene() : startBtnPos(270, 450),
boxSize(180, 80), 
startBoxSize(240, 80),
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

void TitleScene::DrawPlType(void)
{
	for (int i = 0; i < static_cast<int>(PL_TYPE::SYS); i++)
	{
		DrawBox(pPos[i], pPos[i] + boxSize + Vector2(boxOffset, boxOffset), 0x666666, true);

	}

	DxLib::DrawExtendString(LpGameScene.GetScreenSize().x / 2 - 30,  pPos[0].y, 3.0f, 3.0f, "VS", 0xffff00);
	
	// 1P�̕`��
	if (plType[0] == PL_TYPE::MAN)
	{
		DxLib::DrawExtendString(pPos[0].x, pPos[0].y, 3.0f, 3.0f, "Player", 0x7fbfff);
	}
	else
	{
		DxLib::DrawExtendString(pPos[0].x, pPos[0].y, 3.0f, 3.0f, "CPU ", 0x7fbfff);
	}

	// 2P�̕`��
	if (plType[1] == PL_TYPE::MAN)
	{
		DxLib::DrawExtendString(pPos[1].x, pPos[1].y, 3.0f, 3.0f, "Player", 0xff4500);
	}
	else
	{
		DxLib::DrawExtendString(pPos[1].x, pPos[1].y, 3.0f, 3.0f, "CPU", 0xff4500);
	}
}

unique_scene TitleScene::Update(unique_scene own, mouse_shared sysMouse)
{
	 // �E�N���b�N���������A�Q�[�����C���̃V�[���Ɉڍs���� 
	if ((*sysMouse).GetButton()[PUSH_NOW] & (~(*sysMouse).GetButton()[PUSH_OLD]) & MOUSE_INPUT_LEFT)
	{
		if ((*sysMouse).GetPoint() > pPos[0] & (*sysMouse).GetPoint() <= pPos[0] + Vector2(boxSize.x, boxSize.y))
		{
			plType[0] = (PL_TYPE)(1 ^ static_cast<int>(plType[0]));
		}
		else if ((*sysMouse).GetPoint() > pPos[1] & (*sysMouse).GetPoint() <= pPos[1] + Vector2(boxSize.y, boxSize.y))
		{
			plType[1] = (PL_TYPE)(1 ^ static_cast<int>(plType[1]));
		}
		else if ((*sysMouse).GetPoint() >  startBtnPos & 
				 (*sysMouse).GetPoint() <= startBtnPos + Vector2(startBoxSize.x, startBoxSize.y))
		{
			return std::make_unique<MainScene>(plType);
		}
		else{}
		
	}

	// �^�C�g���̕`����s���Ă��� 
	DxLib::ClsDrawScreen();
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/title2.jpg")[0], true);
	DxLib::DrawExtendString(100, 120, 1.8, 1.8f, "���N���b�N�Ńv���C���[���؂�ւ���", 0xffff00);


	DrawPlType();

	// �X�^�[�g�{�^���̕\���ʒu
	DxLib::DrawBox(startBtnPos.x - boxOffset, startBtnPos.y - boxOffset,
				   startBtnPos.x + startBoxSize.x, startBtnPos.y + startBoxSize.y,
				   0xf0e68c, true);
	DxLib::DrawExtendString(startBtnPos.x, startBtnPos.y + boxOffset, 2.5f, 2.5f, "GAME_START", 0x1e90ff);

	DxLib::ScreenFlip();

	return std::move(own);
}
