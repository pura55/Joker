#pragma once
#include "../Library/GameObject.h"

enum class COMMON_STATE
{
	STATE_WARP = 1,
	STATE_TEXT
};

class Common : public GameObject
{
public:
	Common();
	void Update() override;
	void WarpLag();
	void TextLag();

public://setter
	void SetLagIn_W()
	{
		lagCheck = false;
		nowState = COMMON_STATE::STATE_WARP;
	}
	void SetLagIn_T()
	{
		lagCheck = false;
		nowState = COMMON_STATE::STATE_TEXT;
	}

public://getter
	bool GetLagCheck() const { return lagCheck; }

public:
	float ClearTime;
	float TimeLag;//タイムラグ
	bool lagCheck;//spaceを連続でおさない
	bool noDead;

private:
	int warpOutX = 0;
	int warpOutY = 0;
public:
	void SetWarpOut(int x, int y) {
		warpOutX = x; warpOutY = y;
	}
	int GetwarpOutX() { return warpOutX; }
	int GetwarpOutY() { return warpOutY; }


private://state
	COMMON_STATE nowState;
};