#pragma once
#include "../Library/GameObject.h"

enum class MoveAxis
{
	//移動軸
	X,
	Y,

	//行動状態
	CHASE,
	AVOID

};

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

	//回避
	MoveAxis  state;  //エネミーの状態
	MoveAxis moveAxis;//移動軸
	float avoidTimer; //回避時間

private:
	const float speed = 6.0f;
};
