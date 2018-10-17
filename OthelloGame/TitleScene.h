#pragma once
#include "SceneState.h"

class MouseCtl;

class TitleScene :
	public SceneState
{
public:
	TitleScene();
	~TitleScene();
	virtual int Update();
	virtual void Draw();
private:
	int TitleInit();
	int TitleMain();

	std::unique_ptr<MouseCtl> mousePtr;
};

