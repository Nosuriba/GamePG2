#pragma once
#include <list>
#include <memory>
#include <DxLib.h>
#include "ImageMng.h"

class SceneState
{
public:
	virtual ~SceneState() = 0;
	virtual int Update()  = 0;
	virtual void Draw()   = 0;
protected:
	/* リザルトシーンに渡すためのピースの個数 (修正する可能性あり) */
	void SetPieceWhite(int pieceW);
	int  GetPieceWhite(void);
	void SetPieceBlack(int pieceB);
	int  GetPieceBlack(void);

	int pieceW;
	int pieceB;
};

