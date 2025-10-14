#include "Enemy.h"

Enemy::Enemy()
{
	CharacterImage = LoadGraph("");
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	
}

void Enemy::Draw()
{
	DrawRectGraph(EnemyX, EnemyY, 0, 0, 64, 64, CharacterImage, TRUE);
}
