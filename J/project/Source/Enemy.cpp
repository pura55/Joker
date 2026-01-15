#include "Enemy.h"
#include "Player.h"
#include "MainMap.h"
#include "Fader.h"

bool Enemy::followReserved = false;
float Enemy::followX = 0.0f;
float Enemy::followY = 0.0f;
int Enemy::followTimer = 0;


Enemy::Enemy(float x, float y)
{
	//画像の読み込み
	CharacterImage = LoadGraph("data/image/teacher.png");

	//初期化
	EnemyX = x;
	EnemyY = y;
	MovementsPattern = 0;
	MovementsCount = 0;
	DirChara = 3;
	HitJudge = true;
}

Enemy::Enemy(float x, float y, int waitFrame)
{
	ReserveFollowSpawn(x, y, waitFrame);
}

Enemy::~Enemy()
{
	//画像・音声素材のdelete
	DeleteGraph(CharacterImage);
}

void Enemy::Update()
{
	if (followReserved)
	{
		followTimer--;
		if (followTimer <= 0)
		{
			new Enemy(followX, followY);
			followReserved = false;
		}
	}

	Player* player = FindGameObject<Player>();
	VECTOR3 pPos = player->GetPosition();

	Fader* fader = FindGameObject<Fader>();
	if (player->IsHit(EnemyX, EnemyY))
	{
		fader->FadeIn(1.0f);
		SceneManager::ChangeScene("GAMEOVER");
	}

	if (fabs(pPos.x - EnemyX) > 5.0f && HitJudge)
	{
		if (pPos.x > EnemyX)//px > exの時
		{
			EnemyX += speed;//移動距離加算
			DirChara = 1; //方向

			MovementsCount += 1; //キャラクターの動作の処理
			if (MovementsCount >=15) {

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
			if (MovementsCount >= 15) {

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
			if (MovementsCount >= 15) {

				MovementsPattern = (MovementsPattern + 1) % 3 + 0;

				MovementsCount = 0;
			}

			MainMap* ObjectHit = FindGameObject<MainMap>();
			int push1 = ObjectHit->HitCheckDown(EnemyX + 14, EnemyY + 63);
			int push2 = ObjectHit->HitCheckDown(EnemyX + 50, EnemyY + 63);
			EnemyY -= max(push1, push2);

			if (fabs(pPos.y - EnemyY) > 2.0f)
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
			if (MovementsCount >= 15) {

				MovementsPattern = (MovementsPattern + 1) % 3 + 0;

				MovementsCount = 0;
			}

			MainMap* ObjectHit = FindGameObject<MainMap>();
			int push1 = ObjectHit->HitCheckUp(EnemyX + 14, EnemyY + 51);
			int push2 = ObjectHit->HitCheckUp(EnemyX + 50, EnemyY + 51);
			EnemyY += max(push1, push2);
			if (fabs(pPos.y - EnemyY) > 2.0f)
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



void Enemy::ReserveFollowSpawn(float x, float y, int waitFrame)
{
	followReserved = true;
	followX = x;
	followY = y;
	followTimer = waitFrame;
}

void Enemy::killAll()
{
	auto enemies = FindGameObjects<Enemy>();
	for (auto e : enemies)
	{
		e->DestroyMe();
	}
}