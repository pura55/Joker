#pragma once
#include "../Library/GameObject.h"


class Enemy :public GameObject 
{
public:
	Enemy(float x, float y);
	Enemy(float x, float y, int waitFrame);
	~Enemy();
	void Update()override;
	void Draw()override;
    bool Ishit(float px, float py);

	static void ReserveFollowSpawn(float x, float y, int waitFrame);

	static void killAll();

private:
	int CharacterImage ;
    float EnemyX; //敵のX座標
	float EnemyY; //敵のY座標
	int MovementsPattern; //動作のパターン
	int MovementsCount; //動作のカウント
	int DirChara;
	bool HitJudge;

	static bool followReserved;
	static float followX;
	static float followY;
	static int followTimer;

private:
	const float speed = 6.0f;
	
};

