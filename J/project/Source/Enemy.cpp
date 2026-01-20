#include "Enemy.h"
#include "Player.h"
#include "MainMap.h"
#include "Fader.h"
#include "GameManager.h"

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

	//追加
	avoidTimer = 0.0f;
	state = MoveAxis::CHASE;
	moveAxis = MoveAxis::X;
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

	GameManager* gameManager = FindGameObject<GameManager>();
	Player* player = FindGameObject<Player>();
	Fader* fader = FindGameObject<Fader>();

	if (player->IsHit(EnemyX, EnemyY))
	{
		gameManager->SetGameOver();
		fader->FadeIn(1.0f);
		SceneManager::ChangeScene("GAMEOVER");
	}

	////after////

	VECTOR3 pPos = player->GetPosition();
	MainMap* ObjectHit = FindGameObject<MainMap>();

	float dx = pPos.x - EnemyX;
	float dy = pPos.y - EnemyY;

	float moveX = 0.0f;
	float moveY = 0.0f;

	//チェイス
	if (state == MoveAxis::CHASE)
	{
		//x軸とy軸の差を図る
		if (fabs(dx) > fabs(dy))
			moveAxis = MoveAxis::X;
		else
			moveAxis = MoveAxis::Y;

		if (moveAxis == MoveAxis::X)
		{
			moveX = (dx > 0) ? speed : -speed;
		}
		else
		{
			moveY = (dy > 0) ? speed : -speed;
		}

		int push1_R = ObjectHit->HitCheckRight(EnemyX + 50 + moveX, EnemyY + 64);
		int push2_R = ObjectHit->HitCheckRight(EnemyX + 50 + moveX, EnemyY + 95);
		int push1_L = ObjectHit->HitCheckLeft(EnemyX + 14 + moveX, EnemyY + 64);
		int push2_L = ObjectHit->HitCheckLeft(EnemyX + 14 + moveX, EnemyY + 95);
		int push1_U = ObjectHit->HitCheckUp(EnemyX + 24, EnemyY + 64 + moveY);
		int push2_U = ObjectHit->HitCheckUp(EnemyX + 50, EnemyY + 64 + moveY);
		int push1_D = ObjectHit->HitCheckDown(EnemyX + 24, EnemyY + 95 + moveY);
		int push2_D = ObjectHit->HitCheckDown(EnemyX + 50, EnemyY + 95 + moveY);


		if (max(push1_R, push2_R) || max(push1_L, push2_L) || max(push1_U, push2_U) || max(push1_D, push2_D))
		{
			//回避へ遷移
			state = MoveAxis::AVOID;
			avoidTimer = 0.3f;

			//回避軸は追尾軸と逆
			moveAxis = (moveAxis == MoveAxis::X) ? MoveAxis::Y : MoveAxis::X;

			if (moveAxis == MoveAxis::X)
			{
				moveX = (dx > 0) ? speed : -speed;
			}
			else
			{
				moveY = (dy > 0) ? speed : -speed;
			}
		}
	}
	else//回避
	{
		avoidTimer -= Time::DeltaTime();

		//回避中は軸を固定
		if (moveAxis == MoveAxis::X)
		{
			moveX = (dx > 0) ? speed : -speed;
		}
		else
		{
			moveY = (dy > 0) ? speed : -speed;
		}

		if (avoidTimer <= 0.0f)
		{
			state = MoveAxis::CHASE;
		}
	}

	if (EnemyX != 0)
	{
		EnemyX += moveX;
		if (moveX > 0)
		{
			DirChara = 1;
		}
		if (moveX < 0)
		{
			DirChara = 0;
		}

		MovementsCount += 1; //キャラクターの動作の処理
		if (MovementsCount >= 15) {

			MovementsPattern = (MovementsPattern + 1) % 3 + 0;

			MovementsCount = 0;
		}

		int push1_R = ObjectHit->HitCheckRight(EnemyX + 50, EnemyY + 64);
		int push2_R = ObjectHit->HitCheckRight(EnemyX + 50, EnemyY + 95);
		int push1_L = ObjectHit->HitCheckLeft(EnemyX + 14, EnemyY + 64);
		int push2_L = ObjectHit->HitCheckLeft(EnemyX + 14, EnemyY + 95);
		EnemyX -= max(push1_R, push2_R);
		EnemyX += max(push1_L, push2_L);
	}


	if (EnemyY != 0)
	{
		EnemyY += moveY;
		if (moveY > 0)
		{
			DirChara = 3;
		}
		if (moveY < 0)
		{
			DirChara = 2;
		}

		MovementsCount += 1; //キャラクターの動作の処理
		if (MovementsCount >= 15) {

			MovementsPattern = (MovementsPattern + 1) % 3 + 0;

			MovementsCount = 0;
		}

		int push1_U = ObjectHit->HitCheckUp(EnemyX + 24, EnemyY + 64);
		int push2_U = ObjectHit->HitCheckUp(EnemyX + 50, EnemyY + 64);
		int push1_D = ObjectHit->HitCheckDown(EnemyX + 24, EnemyY + 95);
		int push2_D = ObjectHit->HitCheckDown(EnemyX + 50, EnemyY + 95);
		EnemyY -= max(push1_D, push2_D);
		EnemyY += max(push1_U, push2_U);
	}

	////before////
	
	//if (fabs(pPos.x - EnemyX) > 5.0f && HitJudge)
	//{
	//	if (pPos.x > EnemyX)//px > exの時
	//	{
	//		EnemyX += speed;//移動距離加算
	//		DirChara = 1; //方向

	//		MovementsCount += 1; //キャラクターの動作の処理
	//		if (MovementsCount >=15) {

	//			MovementsPattern = (MovementsPattern + 1) % 3 + 0;

	//			MovementsCount = 0;
	//		}

	//		MainMap* ObjectHit = FindGameObject<MainMap>();
	//		int push1 = ObjectHit->HitCheckRight(EnemyX + 50, EnemyY + 51);
	//		int push2 = ObjectHit->HitCheckRight(EnemyX + 50, EnemyY + 63);
	//		EnemyX -= max(push1, push2);
	//		if (max(push1, push2) > 0)
	//		{
	//			HitJudge = false;
	//		}
	//	}
	//	else if
	//		(pPos.x < EnemyX)//px < exの時
	//	{
	//		EnemyX -= speed;
	//		DirChara = 0;

	//		MovementsCount += 1; //キャラクターの動作の処理
	//		if (MovementsCount >= 15) {

	//			MovementsPattern = (MovementsPattern + 1) % 3 + 0;

	//			MovementsCount = 0;
	//		}

	//		MainMap* ObjectHit = FindGameObject<MainMap>();
	//		int push1 = ObjectHit->HitCheckLeft(EnemyX + 14, EnemyY + 51);
	//		int push2 = ObjectHit->HitCheckLeft(EnemyX + 14, EnemyY + 63);
	//		EnemyX += max(push1, push2);
	//		if (max(push1, push2) > 0)
	//		{
	//			HitJudge = false;
	//		}
	//	}
	//}
	//else
	//{
	//	if (pPos.y > EnemyY || !HitJudge)//py > eyの時
	//	{
	//		EnemyY += speed;
	//		DirChara = 3;

	//		MovementsCount += 1; //キャラクターの動作の処理
	//		if (MovementsCount >= 15) {

	//			MovementsPattern = (MovementsPattern + 1) % 3 + 0;

	//			MovementsCount = 0;
	//		}

	//		MainMap* ObjectHit = FindGameObject<MainMap>();
	//		int push1 = ObjectHit->HitCheckDown(EnemyX + 14, EnemyY + 63);
	//		int push2 = ObjectHit->HitCheckDown(EnemyX + 50, EnemyY + 63);
	//		EnemyY -= max(push1, push2);

	//		if (fabs(pPos.y - EnemyY) > 2.0f)
	//		{
	//			HitJudge = true;
	//		}
	//		if (max(push1, push2) > 0)
	//		{
	//			HitJudge = true;
	//		}
	//	}
	//	else if (pPos.y < EnemyY)//py < eyの時
	//	{
	//		EnemyY -= speed;
	//		DirChara = 2;

	//		MovementsCount += 1; //キャラクターの動作の処理
	//		if (MovementsCount >= 15) {

	//			MovementsPattern = (MovementsPattern + 1) % 3 + 0;

	//			MovementsCount = 0;
	//		}

	//		MainMap* ObjectHit = FindGameObject<MainMap>();
	//		int push1 = ObjectHit->HitCheckUp(EnemyX + 14, EnemyY + 51);
	//		int push2 = ObjectHit->HitCheckUp(EnemyX + 50, EnemyY + 51);
	//		EnemyY += max(push1, push2);
	//		if (fabs(pPos.y - EnemyY) > 2.0f)
	//		{
	//			HitJudge = true;
	//		}
	//		if (max(push1, push2) > 0)
	//		{
	//			HitJudge = true;
	//		}
	//	}
	//}
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