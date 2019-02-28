#include "PlayerType.h"
#include "GameScene.h"

PlayerType::~PlayerType()
{
}

bool PlayerType::GetIsEnd()
{
	return isEnd;
}

void PlayerType::SetIsEnd(bool isEnd)
{
	this->isEnd = isEnd;
}

bool PlayerType::GetIsTimeUp()
{
	return isTimeUp;
}

void PlayerType::SetIsTimeUp(bool isTimeUp)
{
	this->isTimeUp = isTimeUp;
}

void PlayerType::SetDefPos(std::weak_ptr<GameBoard> boardPtr)
{
	data.pos = boardPtr.lock()->GetRandomPos();
}

void PlayerType::Update(std::weak_ptr<GameBoard> boardPtr, PIECE_ST pState)
{
}


