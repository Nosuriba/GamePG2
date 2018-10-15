#include "PieceTray.h"
#include "GameScene.h"

PieceTray::PieceTray()
{
	pState = PIECE_NON;
}

PieceTray::PieceTray(PIECE_ST pState)
{
	/* プレイヤーがトレイに所持しているピースの座標 */
	this->pos = Vector2( 30, 100 ) + (Vector2(LpGameScene.GetScreenSize().x - 130, 0) * (pState == PIECE_B ? 0 : 1));
	this->pState = pState;
	int pieceMax = (LpGameScene.GetActiveBoardSize().x * LpGameScene.GetActiveBoardSize().y) / 2;

	/* プレイヤーが所持するピースの個数を追加している */
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
	DrawBox(pos, pos + Vector2(70, 320), 0x00aa00, true);

	for (auto data : pieceList)
	{
		if (cnt < 4)
		{
			cnt++;
			/* ピースのサイズ取得などの部分を修正しておく */
			(*data).SetPos(Vector2(0, ((*data).GetSize()) * cnt));
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
