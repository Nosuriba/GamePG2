#pragma once
#include "SceneState.h"
#include "MouseCtl.h"

struct TitleScene : SceneState
{
	TitleScene();
	~TitleScene();
	void Init();
	void DrawPlType(void);
	unique_scene Update(unique_scene own, mouse_shared sysMouse);

	std::array<PL_TYPE, static_cast<int>(PL_TYPE::MAX)> plType;

	
};

