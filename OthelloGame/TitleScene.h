#pragma once
#include "SceneState.h"
class TitleScene :
	public SceneState
{
public:
	TitleScene();
	~TitleScene();
	virtual int Update();
	virtual void Draw();
};

