#pragma once
#include "SceneState.h"
#include "MouseCtl.h"

struct TitleScene : SceneState
{
	TitleScene();
	~TitleScene();
	void Init();
	unique_scene Update(unique_scene own, mouse_shared sysMouse);
	PL_TYPE plType;
};

