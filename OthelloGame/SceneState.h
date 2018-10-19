#pragma once
#include <list>
#include <memory>
#include <DxLib.h>
#include "ImageMng.h"

class MouseCtl;
class SceneState;

using unique_scene = std::unique_ptr<SceneState>;

class SceneState
{
public:
	virtual ~SceneState();
	virtual void Init() = 0;
	virtual unique_scene Update(unique_scene own, MouseCtl& mousePtr)  = 0;
};

