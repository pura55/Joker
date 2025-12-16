#pragma once
#include "../Library/GameObject.h"

class Warp : public GameObject
{
public:
	Warp(int mainMapStage, int floorMapFloor, int playerX, int playerY);
	~Warp();
	void Update() override;
	void Draw() override;
private:
};
