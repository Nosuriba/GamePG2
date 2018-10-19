#pragma once
#include "SceneState.h"

class TitleScene :
	public SceneState
{
public:
	TitleScene();
	~TitleScene();
	void Init();
	unique_scene Update(unique_scene own, MouseCtl& mouse);
};

