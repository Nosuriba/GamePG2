#include "PieceTray.h"
#include "GameScene.h"

PieceTray::PieceTray()
{
	pState = PIECE_NON;
}

PieceTray::PieceTray(PIECE_ST pState)
{
	/* �v���C���[���g���C�ɏ������Ă���s�[�X�̍��W */
	this->pos = Vector2( 30, 100 ) + (Vector2(LpGameScene.GetScreenSize().x - 130, 0) * (pState == PIECE_B ? 0 : 1));
	this->pState = pState;
	int pieceMax = (LpGameScene.GetActiveBoardSize().x * LpGameScene.GetActiveBoardSize().y) / 2;

	/* �v���C���[����������s�[�X�̌���ǉ����Ă��� */
	for (int p = 0; p < pieceMax; p++)
	{
		AddPiece();
	}
}

PieceTray::~PieceTray()
{

}

bool PieceTray::Draw(void)
{
	int cnt = 0;

	if (turnFlag)
	{
		/* Vector2 + int�̉��Z�q�̃I�[�o�[���[�h������Ă���(�����)*/
		DrawBox(pos - 5, pos + Vector2(70, 320) + 5, 0xeeeeee, true);
	}

	DrawBox(pos, pos + Vector2(70, 320), 0x00aa00, true);

	for (auto data : pieceList)
	{
		/* �g���C�̏�ɔz�u����s�[�X�̕`����s���Ă��� */
		if (cnt < 5)
		{
			cnt++;
			(*data).SetPos(Vector2(0, ((*data).GetSize() * cnt) - (*data).GetSize()));
			(*data).Draw();
		}
		
	}
	return true;
}

bool PieceTray::SetTurnFlag(bool flag)
{
	turnFlag = flag;
	return turnFlag;
}

bool PieceTray::AddPiece(void)
{
	pieceList.push_back(std::make_shared<GamePiece>(Vector2(0,0), pos, pState));
	return true;
}
