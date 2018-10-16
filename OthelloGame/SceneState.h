#pragma once
class SceneState
{
public:
	virtual ~SceneState() = 0;
	virtual int Update()  = 0;
	virtual void Draw()   = 0;
};

