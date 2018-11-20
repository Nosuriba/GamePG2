#include "PieceTray.h"
#include "GameScene.h"

PieceTray::PieceTray(PIECE_ST pState, const Vector2& boardSize)
{
	// �v���C���[���g���C�ɏ������Ă���s�[�X�̍��W 
	this->pos = Vector2( 30, 100 ) + (Vector2(LpGameScene.GetScreenSize().x - 130, 0) * (pState == PIECE_ST::B ? 0 : 1));
	this->pState = pState;
	int pieceMax = ((boardSize.x * boardSize.y) / 2) - 2;

	// �v���C���[����������s�[�X�̌���ǉ����Ă��� 
	for (int p = 0; p < pieceMax; p++)
	{
		AddPiece();
	}
}

PieceTray::~PieceTray()
{
}

bool PieceTray::SetTurnFlag(bool flag)
{
	turnFlag = flag;
	return turnFlag;
}

bool PieceTray::Draw(void)
{
	int cnt = 0;
	// ���݃^�[���������s���Ă���v���C���[�ɘg��`�悵�Ă��� 
	if (turnFlag)
	{
		DrawBox(pos - 5, pos + Vector2(70, 320) + 5, 0xeeeeee, true);
	}

	// �s�[�X��u�����߂̃g���C��`�悵�Ă��� 
	DrawBox(pos, pos + Vector2(70, 320), 0x00aa00, true);
	for (auto data : pieceList)
	{
		// �g���C�̏�ɃZ�b�g�����s�[�X�̕`����s���Ă��� 
		if (cnt < 5)
		{
			cnt++;
			(*data).SetPos(Vector2(0, ((*data).GetSize() * cnt) - (*data).GetSize()));
			(*data).Draw();
		}
	}
	return true;
}

bool PieceTray::AddPiece(void)
{
	pieceList.push_back(std::make_shared<GamePiece>(Vector2(0,0), pos, pState));
	return true;
}
