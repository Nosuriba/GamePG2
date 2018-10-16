#pragma once
#include "SceneState.h"
class MainScene :
	public SceneState
{
public:
	MainScene();
	~MainScene();
	virtual int Update();
	virtual void Draw();
};

