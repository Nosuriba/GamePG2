#include "MainScene.h"
#include "ResultScene.h"
#include "GameBoard.h"
#include "Player.h"
#include "MouseCtl.h"

MainScene::MainScene(std::array<PL_TYPE, static_cast<int>(PL_TYPE::MAX)> plType)
{
	this->plType = plType;
	reverseFlag = false;
	mPos = { 0,0 };
	MainScene::Init();
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
	// �v���C���[�^�C�v���Ƃ̃}�E�X�̏���ݒ肵�Ă���
	for (auto unit : PIECE_ST())
	{
		mouseCtl[unit] = std::make_shared<MouseCtl>();
		(*mouseCtl[unit]).SetPlType(PL_TYPE::MAN);
	}
	(*mouseCtl[0]).SetPlType(plType[0]);
	(*mouseCtl[1]).SetPlType(plType[1]);

	boardPtr = std::make_shared<GameBoard>();

	(*boardPtr).SetPiece(3, 3, PIECE_ST::B);
	(*boardPtr).SetPiece(4, 4, PIECE_ST::B);
	(*boardPtr).SetPiece(3, 4, PIECE_ST::W);
	(*boardPtr).SetPiece(4, 3, PIECE_ST::W);

	boardSize = (*boardPtr).GetDataSize();
	PutPieceCnt();

	// �v���C���[�̓o�^���s���Ă���
	MakePlayer();
	MakePlayer();
	player = playerList.begin();
}

void MainScene::MakePlayer()
{
	playerList.push_back(std::make_shared<Player>(boardSize));
}


void MainScene::NextPlayer(void)
{
	(**player).SetTurn(false);
	player++;
	if (player == playerList.end())
	{
		player = playerList.begin();
	}
	(**player).SetTurn(true);
}

bool MainScene::AutoPassPlayer(void)
{
	NextPlayer();
	(*boardPtr).MakePutPieceField((**player).pGetID());
	if ((*boardPtr).CheckPutPiece())
	{
		return true;
	}
	return false;
}

void MainScene::PutPieceCnt(void)
{
	piece = { 0,0 };
	// �s�[�X�̐F���擾���āA���ꂼ��̌����J�E���g���Ă��� 
	for (int y = 0; y < (*boardPtr).GetDataSize().y; y++)
	{
		for (int x = 0; x < (*boardPtr).GetDataSize().x; x++)
		{
			if ((*boardPtr).CheckPutPieceST(x, y) == PIECE_ST::W)
			{
				piece.w++;
			}
			else if ((*boardPtr).CheckPutPieceST(x, y) == PIECE_ST::B)
			{
				piece.b++;
			}
			else {}
		}
	}
}

void MainScene::DrawPlType(void)
{
	// 1P�̕`��
	if ((*mouseCtl[static_cast<int>(PIECE_ST::B)]).GetPlType() == PL_TYPE::MAN)
	{
		DxLib::DrawExtendString(25, 60, 1.5f, 1.5f,"Player", 0x7fbfff);
	}
	else
	{
		DxLib::DrawExtendString(25, 60, 1.5f, 1.5f, "CPU", 0x7fbfff);
	}

	// 2P�̕`��
	if ((*mouseCtl[static_cast<int>(PIECE_ST::W)]).GetPlType() == PL_TYPE::MAN)
	{
		DxLib::DrawExtendString(700, 60, 1.5f, 1.5f, "Player", 0xff4500);
	}
	else
	{
		DxLib::DrawExtendString(700, 60, 1.5f, 1.5f, "CPU", 0xff4500);
	}
}

unique_scene MainScene::Update(unique_scene own, mouse_shared sysMouse)
{
	(**player).SetTurn(true);
	int mouseID = static_cast<int>((**player).pGetID());

	// �A�N�e�B�u�ȃv���C���[�̃^�[������
	if ((*boardPtr).InvFlag())
	{
		// ���]�������s���Ă��Ȃ����ɒu����ʒu�̓o�^���s���Ă���
		if (!reverseFlag)
		{
			(*boardPtr).MakePutPieceField((**player).pGetID());
		}
		
		(*mouseCtl[mouseID]).Update(boardPtr);

		if ((*mouseCtl[mouseID]).GetButton()[PUSH_NOW] & (~(*mouseCtl[mouseID]).GetButton()[PUSH_OLD]) & MOUSE_INPUT_LEFT)
		{
			if ((**player).TurnAct(mouseCtl, *boardPtr))
			{
				reverseFlag = true;
				mPos = (*mouseCtl[mouseID]).GetPoint();
			}
		}

		// �Q�[�����Ƀv���C���[�𓮓I�ɐ؂�ւ����悤�ɂ��Ă���
		if ((*sysMouse).GetButton()[PUSH_NOW] & (~(*sysMouse).GetButton()[PUSH_OLD]) & MOUSE_INPUT_RIGHT)
		{
			if ((*mouseCtl[mouseID]).GetPlType() == PL_TYPE::MAN)
			{
				(*mouseCtl[mouseID]).SetPlType(PL_TYPE::CPU);
			}
			else
			{
				(*mouseCtl[mouseID]).SetPlType(PL_TYPE::MAN);
			}
		}
	}

	// �Ԋu���󂯂Ĕ��]�������s���悤�ɂ��Ă���
	if (reverseFlag)
	{
		if ((*boardPtr).InvFlag(reverseFlag))
		{
			reverseFlag = false;
			(*boardPtr).SetReverse(mPos, (**player).pGetID());
			PutPieceCnt();
			(*boardPtr).PutPieceClear();
			NextPlayer();
		}
	}

	// �v���C���[�̃p�X�����ƃQ�[�����p�����邩�̊Ǘ������Ă���
	if ((*boardPtr).InvFlag())
	{
		if (!(*boardPtr).CheckPutPiece())
		{
			if (!AutoPassPlayer())
			{
				(*boardPtr).SetPieceCnt(piece);
				return std::make_unique<ResultScene>(boardPtr);
			}
		}
	}
	(*boardPtr).Update();

	DxLib::ClsDrawScreen();
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("image/gameBG.png")[0], true);

	// ������@�̃e�L�X�g��`�悵�Ă���
	DxLib::DrawExtendString(50, 10, 1.3f, 1.3f, "���N���b�N�ŃR�}���u����� /", 0xffff00);
	DxLib::DrawExtendString(375, 10, 1.3f, 1.3f, "�E�N���b�N�Ńv���C���[���؂�ւ���", 0xffff00);

	// ���݂̃s�[�X�̌���`�悵�Ă���
	DxLib::DrawExtendFormatString(25, 450, 1.5f, 1.5f, 0xeeee00, "��: %d", piece.b);
	DxLib::DrawExtendFormatString(700, 450, 1.5f, 1.5f, 0xeeee00, "��: %d", piece.w);

	DrawPlType();

	// �Ֆʂ̏���`�悵�Ă���
	(*boardPtr).Draw();

	// �v���C���[�̎����R�}�̏���`�悵�Ă���
	for (auto data : playerList)
	{
		(*data).Draw();
	}

	DxLib::ScreenFlip();
	return std::move(own);
}

