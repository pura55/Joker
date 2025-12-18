#pragma once
#include "../Library/GameObject.h"

class Common : public GameObject
{
public:
	Common();
	void Update() override;
	void SetLagTime();
	void SetTimeCheck(bool tc) { TimeCheck = tc; }

public://getter
	bool GetTimeCheck() const { return TimeCheck; }

public:
	float ClearTime;
	float LagTime;
	bool TimeCheck;
	bool noDead;
};