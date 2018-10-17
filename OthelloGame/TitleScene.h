#pragma once
#include "SceneState.h"

class MouseCtl;

class TitleScene :
	public SceneState
{
public:
	TitleScene();
	~TitleScene();
	bool Update();
	void Draw();
private:
	int TitleInit();
	bool TitleMain();

	std::unique_ptr<MouseCtl> mousePtr;
};

