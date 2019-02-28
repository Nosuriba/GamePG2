#pragma once
#include <list>
#include <memory>
#include <DxLib.h>
#include "ImageMng.h"
#include "PieceST.h"

class SceneState;
class MouseCtl;

using unique_scene = std::unique_ptr<SceneState>;
using mouse_shared = std::shared_ptr<MouseCtl>;
using mouse_array  = std::array<mouse_shared, static_cast<int>(PIECE_ST::MAX)>;

class SceneState
{
public:
	virtual ~SceneState();
	virtual void Init() = 0;
	virtual unique_scene Update(unique_scene own, mouse_shared sysMouse) = 0;
protected:
	unsigned int plColor = 0;
};

