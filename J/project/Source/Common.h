#pragma once
#include "../Library/GameObject.h"

class Common : public GameObject
{
public:
	Common();
	void Update() override;
	void SetLagTime();
	void SetPushStop(bool tc) { PushStop = tc; }//

public://getter
	bool GetPushStop() const { return PushStop; }

public:
	float ClearTime;
	float LagTime;
	bool PushStop;//space‚ð˜A‘±‚Å‚¨‚³‚È‚¢
	bool noDead;
};