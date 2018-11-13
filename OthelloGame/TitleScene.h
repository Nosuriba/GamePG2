#pragma once
#include "SceneState.h"
#include "PlayerType.h"

class MouseCtl;

struct TitleScene : SceneState
{
	TitleScene();
	~TitleScene();
	void Init();
	unique_scene Update(unique_scene own, MouseCtl& mouse);
	PL_TYPE plType;
};

