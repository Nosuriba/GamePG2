#pragma once
#include "SceneState.h"

class MouseCtl;

struct TitleScene : SceneState
{
	TitleScene();
	~TitleScene();
	void Init();
	unique_scene Update(unique_scene own, MouseCtl& mouse);
};

