#pragma once
#include "../Library/GameObject.h"

enum class MoveAxisBoss
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
	void killAll();

private:
	int BossImage;
	float BossX; //敵のX座標
	float BossY; //敵のY座標
	int MovementsPattern; //動作のパターン
	int MovementsCount; //動作のカウント
	int DirChara;
	int Xdir;           //X軸の方向
	bool HitJudge;      

	//回避
	MoveAxisBoss  state;  //エネミーの状態
	MoveAxisBoss moveAxis;//移動軸
	float avoidTimer; //回避時間

private:
	const float speed = 8.5f;
};
