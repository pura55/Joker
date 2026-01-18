#pragma once
#include "../Library/GameObject.h"

class Principal : public GameObject
{
public:
	Principal(float x, float y);
	~Principal();
	void Update() override;
	void Draw() override;

private:
	int BossImage;
	float BossX; //敵のX座標
	float BossY; //敵のY座標
	int MovementsPattern; //動作のパターン
	int MovementsCount; //動作のカウント
	int DirChara;
	bool HitJudge;

private:
	const float speed = 6.0f;
};
