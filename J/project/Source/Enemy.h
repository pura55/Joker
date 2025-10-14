#pragma once
#include "../Library/GameObject.h"


class Enemy :public GameObject 
{
public:
	Enemy();
	~Enemy();
	void Update()override;
	void Draw()override;
private:
	int CharacterImage ;
    float EnemyX; //敵のX座標
	float EnemyY; //敵のY座標
	int MovementsPattern; //動作のパターン
	int MovementsCount; //動作のカウント
	
};

