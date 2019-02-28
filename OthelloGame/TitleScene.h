#pragma once
#include "SceneState.h"
#include "MouseCtl.h"

struct TitleScene : SceneState
{
	TitleScene();
	~TitleScene();
	void Init();
	void DrawPlType();
	unique_scene Update(unique_scene own, mouse_shared sysMouse);

	const int boxOffset;
	const std::array<Vector2, static_cast<int>(PL_TYPE::MAX)> pPos = { Vector2(60, 240), Vector2(550, pPos[0].y) };
	const Vector2 netBtnPos;
	const Vector2 boxSize;
	const Vector2 netBoxSize;

	std::array<PL_TYPE, static_cast<int>(PL_TYPE::MAX)> plType;

	
};

