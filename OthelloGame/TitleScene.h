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

	const int boxOffset;
	const std::array<Vector2, static_cast<int>(PL_TYPE::MAX)> pPos = { Vector2(100, 270), Vector2(550, 270) };
	const Vector2 startBtnPos;
	const Vector2 boxSize;
	const Vector2 startBoxSize;
	

	std::array<PL_TYPE, static_cast<int>(PL_TYPE::MAX)> plType;

	
};

