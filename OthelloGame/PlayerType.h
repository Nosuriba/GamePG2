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
	bool isEnd;			// ˆ—‚ÌI—¹‚ğ’m‚ç‚¹‚é‚½‚ß‚Ì”»’è
	bool isTimeUp;		// §ŒÀŠÔ‚ğ’´‚¦‚½‚©‚Ì”»’è

};

