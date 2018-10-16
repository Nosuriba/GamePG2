#pragma once
#include "SceneState.h"
class ResultScene :
	public SceneState
{
public:
	ResultScene();
	~ResultScene();
	virtual int Update();
	virtual void Draw();
};

