#include "SceneState.h"
#include "MouseCtl.h"

/* �V�[���̌Ăяo���Ō��ݍs���Ă���V�[������true�̏�񂪕Ԃ��Ă�����V�[���̐؂�ւ�������悤�ɂ���
�@ �Ƃ肠�����A����͉��ݒ�̍l���Ȃ̂Ŏ������ł�����C�����s���悤�ɂ���*/
SceneState::~SceneState()
{
}

void SceneState::SetPieceWhite(int pieceW)
{
	this->pieceW = pieceW;
}

int SceneState::GetPieceWhite(void)
{
	return pieceW;
}

void SceneState::SetPieceBlack(int pieceB)
{
	this->pieceB = pieceB;
}

int SceneState::GetPieceBlack(void)
{
	return pieceB;
}
