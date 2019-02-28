#include "TitleScene.h"
#include "MainScene.h"
#include "ResultScene.h"
#include "GameBoard.h"
#include "Player.h"
#include "MouseCtl.h"
#include "GameScene.h"
#include "NetWork.h"
#include "AudioMng.h"

MainScene::MainScene(std::array<PL_TYPE, static_cast<int>(PL_TYPE::MAX)> plType) : plBoxSize(80, 40)
{
	this->plType = plType;
	reverseFlag = false;
	mPos = { 0,0 };
	MainScene::Init();
	LpGameScene.ResetTime();
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
	for (auto unit : PIECE_ST())
	{
		mouseCtl[unit] = std::make_shared<MouseCtl>();
	}

	// �v���C���[�^�C�v���Ƃ̃}�E�X�̏���ݒ肵�Ă���
	if (lpNetWork.GetMode() == NetWorkMode::OFFLINE)
	{
		(*mouseCtl[0]).SetPlType(plType[0]);
		(*mouseCtl[1]).SetPlType(plType[1]);
	}
	else
	{
		/// �Ƃ肠�����A�z�X�g���Q�X�g�ɂ����
		if (lpNetWork.GetMode() == NetWorkMode::HOST)
		{
			//(*mouseCtl[0]).SetPlType(plType[0]);
			(*mouseCtl[0]).SetPlType(PL_TYPE::CPU);
			(*mouseCtl[1]).SetPlType(PL_TYPE::NET);
		}
		else if (lpNetWork.GetMode() == NetWorkMode::GUEST)
		{
			(*mouseCtl[0]).SetPlType(PL_TYPE::NET);
			(*mouseCtl[1]).SetPlType(PL_TYPE::CPU);

		}
		else{}
	}
	
	gBoard = std::make_shared<GameBoard>();
	(*gBoard).SetPiece(3, 3, PIECE_ST::B);
	(*gBoard).SetPiece(4, 4, PIECE_ST::B);
	(*gBoard).SetPiece(3, 4, PIECE_ST::W);
	(*gBoard).SetPiece(4, 3, PIECE_ST::W);

	boardSize = (*gBoard).GetDataSize();
	piece = (*gBoard).PutPieceCnt();

	// �v���C���[�̓o�^���s���Ă���
	MakePlayer();
	MakePlayer();
	player = playerList.begin();
}

void MainScene::MakePlayer()
{
	playerList.push_back(std::make_shared<Player>(boardSize));
}


void MainScene::NextPlayer()
{
	(**player).SetTurn(false);
	(**player).ReleaseTray((**player).pGetID());
	player++;
	if (player == playerList.end())
	{
		player = playerList.begin();
	}
	(**player).SetTurn(true);
}

bool MainScene::AutoPassPlayer()
{
	NextPlayer();
	(*gBoard).MakePutPieceField((**player).pGetID());
	if ((*gBoard).CheckPutPiece())
	{
		return true;
	}
	return false;
}

void MainScene::DrawPlType()
{
	for (int i = 0; i < static_cast<int>(PIECE_ST::NON); i++)
	{
		int plState = (i == 0 ? plState = static_cast<int>(PIECE_ST::B) : plState = static_cast<int>(PIECE_ST::W));
		plColor = (i == 0 ? plColor = 0x7fbfff : plColor = 0xff4500);
		
		DrawBox(plPos[i], plPos[i] + plBoxSize, 0x666666, true);

		// �v���C���[�̕`��
		if ((*mouseCtl[plState]).GetPlType() == PL_TYPE::MAN)
		{
			DxLib::DrawExtendString(plPos[i].x, plPos[i].y, 1.5f, 1.5f, "Player", plColor);
		}
		else
		{
			DxLib::DrawExtendString(plPos[i].x, plPos[i].y, 1.5f, 1.5f, "CPU", plColor);
		}
	}
}

unique_scene MainScene::Update(unique_scene own, mouse_shared sysMouse)
{
	LpAudioMng.PlayBGM(LpAudioMng.GetSound().mainBGM);
	if (lpNetWork.GetMode() != NetWorkMode::OFFLINE)
	{
		if (!lpNetWork())
		{
			lpNetWork.CloseNetWork();
			LpAudioMng.PlaySE(LpAudioMng.GetSound().closeNetSE);
			return std::make_unique<TitleScene>();
		}
	}
	(**player).SetTurn(true);
	int mouseID = static_cast<int>((**player).pGetID());

	// �A�N�e�B�u�ȃv���C���[�̃^�[������
	if ((*gBoard).InvFlag())
	{
		// ���]�������s���Ă��Ȃ����ɒu����ʒu�̓o�^���s���Ă���
		if (!reverseFlag)
		{
			(*gBoard).MakePutPieceField((**player).pGetID());
		}
		(*mouseCtl[mouseID]).Update(gBoard, (**player).pGetID());
		if ((*mouseCtl[mouseID]).GetButton()[PUSH_NOW] & (~(*mouseCtl[mouseID]).GetButton()[PUSH_OLD]) & MOUSE_INPUT_LEFT)
		{
			if ((**player).TurnAct(mouseCtl, *gBoard))
			{
				reverseFlag = true;
				mPos = (*mouseCtl[mouseID]).GetPoint();
			}
		}

		// �Q�[�����Ƀv���C���[�𓮓I�ɐ؂�ւ����悤�ɂ��Ă���
		if ((*sysMouse).GetButton()[PUSH_NOW] & (~(*sysMouse).GetButton()[PUSH_OLD]) & MOUSE_INPUT_LEFT)
		{
			/// 1P��ID��ύX���Ă���
			if ((*sysMouse).GetPoint() >  plPos[static_cast<int>(PIECE_ST::B)] &&
				(*sysMouse).GetPoint() <= plPos[static_cast<int>(PIECE_ST::B)] + Vector2(plBoxSize.x, plBoxSize.y))
			{
				LpAudioMng.PlaySE(LpAudioMng.GetSound().changeSE);
				auto pTypeB = (1 ^ (int)(*mouseCtl[static_cast<int>(PIECE_ST::B)]).GetPlType());
				(*mouseCtl[static_cast<int>(PIECE_ST::B)]).ThreadStop();
				(*mouseCtl[static_cast<int>(PIECE_ST::B)]).SetPlType((PL_TYPE)(pTypeB));
			}
			/// 2P��ID��ύX���Ă���
			else if (((*sysMouse).GetPoint() >  plPos[static_cast<int>(PIECE_ST::W)] &&
				      (*sysMouse).GetPoint() <= plPos[static_cast<int>(PIECE_ST::W)] + Vector2(plBoxSize.x, plBoxSize.y)))
			{
				LpAudioMng.PlaySE(LpAudioMng.GetSound().changeSE);
				auto pTypeW = (1 ^ (int)(*mouseCtl[static_cast<int>(PIECE_ST::W)]).GetPlType());
				(*mouseCtl[static_cast<int>(PIECE_ST::W)]).ThreadStop();
				(*mouseCtl[static_cast<int>(PIECE_ST::W)]).SetPlType((PL_TYPE)(pTypeW));
			}
			else {}
		}
	}

	// �Ԋu���󂯂Ĕ��]�������s���悤�ɂ��Ă���
	if (reverseFlag)
	{
		if ((*gBoard).InvFlag(reverseFlag))
		{
			reverseFlag = false;
			(*gBoard).SetReverse(mPos, (**player).pGetID());
			piece = (*gBoard).PutPieceCnt();
			mPos = { 0,0 };
			NextPlayer();
			(*gBoard).PutPieceClear();
			LpGameScene.ResetTime();
		}
	}

	// �v���C���[�̃p�X�����ƃQ�[�����p�����邩�̊Ǘ������Ă���
	if ((*gBoard).InvFlag())
	{
		if (!(*gBoard).CheckPutPiece())
		{
			if (!AutoPassPlayer())
			{
				piece = (*gBoard).PutPieceCnt();
				(*gBoard).SetPieceCnt(piece);
				return std::make_unique<ResultScene>(gBoard);
			}
		}
	}
	(*gBoard).Update();
	DxLib::ClsDrawScreen();
	DxLib::DrawGraph(0, 0, LpImageMng.ImgGetID("resource/image/gameBG.png")[0], true);

	// ������@�̃e�L�X�g��`�悵�Ă���
	DxLib::DrawExtendString(200, 10, 1.5f, 1.5f, "���N���b�N�ŃR�}���u�����", 0xffff00);
	// ���݂̃s�[�X�̌���`�悵�Ă���
	DxLib::DrawExtendFormatString(pCntPos[0].x, pCntPos[0].y, 1.5f, 1.5f, 0xeeee00, "��: %d", piece.b);
	DxLib::DrawExtendFormatString(pCntPos[1].x, pCntPos[1].y, 1.5f, 1.5f, 0xeeee00, "��: %d", piece.w);

	DrawPlType();

	// �Ֆʂ̏���`�悵�Ă���
	(*gBoard).Draw();

	// �v���C���[�̎����R�}�̏���`�悵�Ă���
	for (auto data : playerList)
	{
		(*data).Draw();
	}
	/// ���Ԃ̕\��
	DxLib::DrawExtendFormatString(40, 50, 1.5f, 1.5f, 0xff0000, "%d �b", LpGameScene.GetSecondsTime());
	DxLib::ScreenFlip();
	return std::move(own);
}

