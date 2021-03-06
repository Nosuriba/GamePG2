#pragma once
#include "MouseCtl.h"
#include "GameBoard.h"
#include "GameScene.h"


class PlayerType
{
public:
	virtual ~PlayerType();
	virtual PL_TYPE GetType()			  = 0;
	virtual mouse_data  GetMouseData()	  = 0;
	virtual void Update(std::weak_ptr<GameBoard> boardPtr, PIECE_ST pState);
	virtual bool GetIsEnd();
	void SetIsEnd(bool isEnd);
	virtual bool GetIsTimeUp();
	void SetIsTimeUp(bool isEnd);
	void SetDefPos(std::weak_ptr<GameBoard> boardPtr);
protected:
	mouse_data data;
	std::mutex mtx;
	bool isEnd;			// 処理の終了を知らせるための判定
	bool isTimeUp;		// 制限時間を超えたかの判定

};

