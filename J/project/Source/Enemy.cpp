#include "Enemy.h"
#include "Player.h"
#include "MainMap.h"


Enemy::Enemy()
{
	CharacterImage = LoadGraph("data/image/teacher.png");

	EnemyX = 300.0f;
	EnemyY = 300.0f;
	MovementsPattern = 0;
	MovementsCount = 0;
	DirChara = 3;
	HitJudge = true;
}

Enemy::~Enemy()
{
	
}

void Enemy::Update()
{
	
	Player* player = FindGameObject<Player>();
	VECTOR3 pPos = player->GetPosition();

	if (fabs(pPos.x - EnemyX) > 5.0f && HitJudge)
	{
		if (pPos.x > EnemyX)//px > exの時
		{
			EnemyX += speed;//移動距離加算
			DirChara = 1;

			MovementsCount += 1; //キャラクターの動作の処理
			if (MovementsCount >=12) {

				MovementsPattern = (MovementsPattern + 1) % 3 + 0;

				MovementsCount = 0;
			}

			MainMap* ObjectHit = FindGameObject<MainMap>();
			int push1 = ObjectHit->HitCheckRight(EnemyX + 50, EnemyY + 51);
			int push2 = ObjectHit->HitCheckRight(EnemyX + 50, EnemyY + 63);
			EnemyX -= max(push1, push2);
			if (max(push1, push2) > 0)
			{
				HitJudge = false;
			}
		}
		else if
			(pPos.x < EnemyX)//px < exの時
		{
			EnemyX -= speed;
			DirChara = 0;

			MovementsCount += 1; //キャラクターの動作の処理
			if (MovementsCount >= 12) {

				MovementsPattern = (MovementsPattern + 1) % 3 + 0;

				MovementsCount = 0;
			}

			MainMap* ObjectHit = FindGameObject<MainMap>();
			int push1 = ObjectHit->HitCheckLeft(EnemyX + 14, EnemyY + 51);
			int push2 = ObjectHit->HitCheckLeft(EnemyX + 14, EnemyY + 63);
			EnemyX += max(push1, push2);
			if (max(push1, push2) > 0)
			{
				HitJudge = false;
			}
		}
	}
	else
	{
		if (pPos.y > EnemyY || !HitJudge)//py > eyの時
		{
			EnemyY += speed;
			DirChara = 3;

			MovementsCount += 1; //キャラクターの動作の処理
			if (MovementsCount >= 12) {

				MovementsPattern = (MovementsPattern + 1) % 3 + 0;

				MovementsCount = 0;
			}

			MainMap* ObjectHit = FindGameObject<MainMap>();
			int push1 = ObjectHit->HitCheckDown(EnemyX + 14, EnemyY + 63);
			int push2 = ObjectHit->HitCheckDown(EnemyX + 50, EnemyY + 63);
			EnemyY -= max(push1, push2);

			if (fabs(pPos.y - EnemyY) > 5.0f)
			{
				HitJudge = true;
			}
			if (max(push1, push2) > 0)
			{
				HitJudge = true;
			}
		}
		else if (pPos.y < EnemyY)//py < eyの時
		{
			EnemyY -= speed;
			DirChara = 2;

			MovementsCount += 1; //キャラクターの動作の処理
			if (MovementsCount >= 12) {

				MovementsPattern = (MovementsPattern + 1) % 3 + 0;

				MovementsCount = 0;
			}

			MainMap* ObjectHit = FindGameObject<MainMap>();
			int push1 = ObjectHit->HitCheckUp(EnemyX + 14, EnemyY + 51);
			int push2 = ObjectHit->HitCheckUp(EnemyX + 50, EnemyY + 51);
			EnemyY += max(push1, push2);
			if (fabs(pPos.y - EnemyY) > 5.0f)
			{
				HitJudge = true;
			}
			if (max(push1, push2) > 0)
			{
				HitJudge = true;
			}
		}
	}
}

void Enemy::Draw()
{
	MainMap* mainmap = FindGameObject<MainMap>();
	int scX = 0;
	int scY = 0;
	if (mainmap)
	{
		scX = mainmap->GetScrollX();
		scY = mainmap->GetScrollY();
	}
	DrawRectGraph(EnemyX - scX, EnemyY - scY, 64 * MovementsPattern, 96 * DirChara, 64, 96, CharacterImage, TRUE);
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
