#include "PieceTray.h"
#include "GameScene.h"

PieceTray::PieceTray(PIECE_ST pState, const Vector2& boardSize)
{
	// プレイヤーがトレイに所持しているピースの座標 
	this->pos = Vector2( 30, 100 ) + (Vector2(LpGameScene.GetScreenSize().x - 130, 0) * (pState == PIECE_ST::B ? 0 : 1));
	this->pState = pState;
	int pieceMax = ((boardSize.x * boardSize.y) / 2) - 2;

	// プレイヤーが所持するピースの個数を追加している 
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
	// 現在ターン処理を行っているプレイヤーに枠を描画している 
	if (turnFlag)
	{
		DrawBox(pos - 5, pos + Vector2(70, 320) + 5, 0xeeeeee, true);
	}

	// ピースを置くためのトレイを描画している 
	DrawBox(pos, pos + Vector2(70, 320), 0x00aa00, true);
	for (auto data : pieceList)
	{
		// トレイの上にセットされるピースの描画を行っている 
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
