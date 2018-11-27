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

	const std::array<Vector2, static_cast<int>(PL_TYPE::MAX)> pPos = { Vector2(100, 270), Vector2(550, 270) };
	std::array<PL_TYPE, static_cast<int>(PL_TYPE::MAX)> plType;

	
};

