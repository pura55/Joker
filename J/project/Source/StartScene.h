#pragma once
#include "../Library/SceneBase.h"

class StartScene : public SceneBase
{
public:
	StartScene();
	~StartScene();
	void Update() override;
	void Draw() override;
};
