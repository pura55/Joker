#include "Enemy.h"
#include "Player.h"
#include "MainMap.h"

Enemy::Enemy()
{
	CharacterImage = LoadGraph("");

	EnemyX = 300.0f;
	EnemyY = 300.0f;
	MovementsPattern = 0;
	MovementsCount = 0;
}

Enemy::~Enemy()
{
	
}

void Enemy::Update()
{
	
	Player* player = FindGameObject<Player>();
	VECTOR3 pPos = player->GetPosition();

	if (fabs(pPos.x - EnemyX) > 3.0f)
	{
		if (pPos.x > EnemyX)//px > exの時
		{
			EnemyX += speed;//移動距離加算


			MainMap* ObjectHit = FindGameObject<MainMap>();
			int push1 = ObjectHit->HitCheckRight(EnemyX + 50, EnemyY + 51);
			int push2 = ObjectHit->HitCheckRight(EnemyX + 50, EnemyY + 63);
			EnemyX -= max(push1, push2);
		}
		else if
			(pPos.x < EnemyX)//px < exの時
		{
			EnemyX -= speed;

			MainMap* ObjectHit = FindGameObject<MainMap>();
			int push1 = ObjectHit->HitCheckLeft(EnemyX + 14, EnemyY + 51);
			int push2 = ObjectHit->HitCheckLeft(EnemyX + 14, EnemyY + 63);
			EnemyX += max(push1, push2);
		}
	}
	else
	{
		if (pPos.y > EnemyY)//py > eyの時
		{
			EnemyY += speed;


			MainMap* ObjectHit = FindGameObject<MainMap>();
			int push1 = ObjectHit->HitCheckDown(EnemyX + 14, EnemyY + 63);
			int push2 = ObjectHit->HitCheckDown(EnemyX + 50, EnemyY + 63);
			EnemyY -= max(push1, push2);
		}
		else if (pPos.y < EnemyY)//py < eyの時
		{
			EnemyY -= speed;

			MainMap* ObjectHit = FindGameObject<MainMap>();
			int push1 = ObjectHit->HitCheckUp(EnemyX + 14, EnemyY + 51);
			int push2 = ObjectHit->HitCheckUp(EnemyX + 50, EnemyY + 51);
			EnemyY += max(push1, push2);
		}
	}
}

void Enemy::Draw()
{
	DrawRectGraph(EnemyX, EnemyY, 0, 0, 64, 64, CharacterImage, TRUE);
}

bool Enemy::Ishit(float px, float py)
{
	//プレイヤーの座標はpx,py
	float dx = px - (EnemyX);
	float dy = py - (EnemyY);
	float sum = sqrt(dx * dx + dy * dy);
	if (sum < 30)
	{
		return true;
	}
	return false;
}
