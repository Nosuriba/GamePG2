#include "SceneState.h"
#include "MouseCtl.h"

/* シーンの呼び出しで現在行っているシーンからtrueの情報が返ってきたらシーンの切り替えをするようにする
　 とりあえず、これは仮設定の考えなので実装ができ次第修正を行うようにする*/
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
