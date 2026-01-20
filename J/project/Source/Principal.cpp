#include "Principal.h"
#include "GameManager.h"
#include "MainMap.h"
#include "Player.h"
#include "Fader.h"

Principal::Principal(float x, float y)
{
	//画像の読み込み
	BossImage = LoadGraph("data/image/Principal.png");

	//初期化
	BossX = x;
	BossY = y;
	MovementsPattern = 0;
	MovementsCount = 0;
	DirChara = 3;
	HitJudge = true;
	Xdir = 1;

	//追加
	avoidTimer = 0.0f;
	state = MoveAxis::CHASE;
	moveAxis = MoveAxis::X;
}

Principal::~Principal()
{
	DeleteGraph(BossImage);
}

void Principal::Update()
{

	GameManager* gameManager = FindGameObject<GameManager>();
	Player* player = FindGameObject<Player>();
	Fader* fader = FindGameObject<Fader>();

	if (player->IsHit(BossX + 192/2, BossY + 256/2))
	{
		gameManager->SetGameOver();
		fader->FadeIn(1.0f);
		SceneManager::ChangeScene("GAMEOVER");
	}

	////after////

	VECTOR3 pPos = player->GetPosition();
	MainMap* ObjectHit = FindGameObject<MainMap>();

	float dx = pPos.x - BossX;
	float dy = pPos.y - BossY;

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

		int push1_R = ObjectHit->HitCheckRight(BossX + 50 + moveX, BossY + 64);
		int push2_R = ObjectHit->HitCheckRight(BossX + 50 + moveX, BossY + 95);
		int push1_L = ObjectHit->HitCheckLeft(BossX + 14 + moveX, BossY + 64);
		int push2_L = ObjectHit->HitCheckLeft(BossX + 14 + moveX, BossY + 95);
		int push1_U = ObjectHit->HitCheckUp(BossX + 24, BossY + 64 + moveY);
		int push2_U = ObjectHit->HitCheckUp(BossX + 50, BossY + 64 + moveY);
		int push1_D = ObjectHit->HitCheckDown(BossX + 24, BossY + 95 + moveY);
		int push2_D = ObjectHit->HitCheckDown(BossX + 50, BossY + 95 + moveY);


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

	if (BossX != 0)
	{
		BossX += moveX;
		if (moveX > 0)
		{
			DirChara = 1;
			Xdir = 0;
		}
		if (moveX < 0)
		{
			DirChara = 1;
			Xdir = 1;
		}

		MovementsCount += 1; //キャラクターの動作の処理
		if (MovementsCount >= 15) {

			MovementsPattern = (MovementsPattern + 1) % 3 + 0;

			MovementsCount = 0;
		}

		int push1_R = ObjectHit->HitCheckRight(BossX + 50, BossY + 64);
		int push2_R = ObjectHit->HitCheckRight(BossX + 50, BossY + 95);
		int push1_L = ObjectHit->HitCheckLeft(BossX + 14, BossY + 64);
		int push2_L = ObjectHit->HitCheckLeft(BossX + 14, BossY + 95);
		BossX -= max(push1_R, push2_R);
		BossX += max(push1_L, push2_L);
	}


	if (BossY != 0)
	{
		BossY += moveY;
		if (moveY > 0)
		{
			DirChara = 0;
			Xdir = 0;
		}
		if (moveY < 0)
		{
			DirChara = 2;
			Xdir = 0;
		}

		MovementsCount += 1; //キャラクターの動作の処理
		if (MovementsCount >= 15) {

			MovementsPattern = (MovementsPattern + 1) % 3 + 0;

			MovementsCount = 0;
		}

		int push1_U = ObjectHit->HitCheckUp(BossX + 24, BossY + 64);
		int push2_U = ObjectHit->HitCheckUp(BossX + 50, BossY + 64);
		int push1_D = ObjectHit->HitCheckDown(BossX + 24, BossY + 95);
		int push2_D = ObjectHit->HitCheckDown(BossX + 50, BossY + 95);
		BossY -= max(push1_D, push2_D);
		BossY += max(push1_U, push2_U);
	}


	//if (fabs(pPos.x - BossX) > 5.0f && HitJudge)
	//{
	//	if (pPos.x > BossX)//px > exの時
	//	{
	//		BossX += speed;//移動距離加算
	//		DirChara = 1; //方向

	//		MovementsCount += 1; //キャラクターの動作の処理
	//		if (MovementsCount >= 15) {

	//			MovementsPattern = (MovementsPattern + 1) % 3 + 0;

	//			MovementsCount = 0;
	//		}

	//		MainMap* ObjectHit = FindGameObject<MainMap>();
	//		int push1 = ObjectHit->HitCheckRight(BossX + 50, BossY + 51);
	//		int push2 = ObjectHit->HitCheckRight(BossX + 50, BossY + 63);
	//		BossX -= max(push1, push2);
	//		if (max(push1, push2) > 0)
	//		{
	//			HitJudge = false;
	//		}
	//	}
	//	else if
	//		(pPos.x < BossX)//px < exの時
	//	{
	//		BossX -= speed;
	//		DirChara = 1;

	//		MovementsCount += 1; //キャラクターの動作の処理
	//		if (MovementsCount >= 15) {

	//			MovementsPattern = (MovementsPattern + 1) % 3 + 0;

	//			MovementsCount = 0;
	//		}

	//		MainMap* ObjectHit = FindGameObject<MainMap>();
	//		int push1 = ObjectHit->HitCheckLeft(BossX + 11, BossY + 51);
	//		int push2 = ObjectHit->HitCheckLeft(BossX + 11, BossY + 63);
	//		BossX += max(push1, push2);
	//		if (max(push1, push2) > 0)
	//		{
	//			HitJudge = false;
	//		}
	//	}
	//}
	//else
	//{
	//	if (pPos.y > BossY || !HitJudge)//py > eyの時
	//	{
	//		BossY += speed;
	//		DirChara = 0;

	//		MovementsCount += 1; //キャラクターの動作の処理
	//		if (MovementsCount >= 15) {

	//			MovementsPattern = (MovementsPattern + 1) % 3 + 0;

	//			MovementsCount = 0;
	//		}

	//		MainMap* ObjectHit = FindGameObject<MainMap>();
	//		int push1 = ObjectHit->HitCheckDown(BossX + 11, BossY + 255);
	//		int push2 = ObjectHit->HitCheckDown(BossX + 50, BossY + 255);
	//		BossY -= max(push1, push2);

	//		if (fabs(pPos.y - BossY) > 2.0f)
	//		{
	//			HitJudge = true;
	//		}
	//		if (max(push1, push2) > 0)
	//		{
	//			HitJudge = true;
	//		}
	//	}
	//	else if (pPos.y < BossY)//py < eyの時
	//	{
	//		BossY -= speed;
	//		DirChara = 2;

	//		MovementsCount += 1; //キャラクターの動作の処理
	//		if (MovementsCount >= 15) {

	//			MovementsPattern = (MovementsPattern + 1) % 3 + 0;

	//			MovementsCount = 0;
	//		}

	//		MainMap* ObjectHit = FindGameObject<MainMap>();
	//		int push1 = ObjectHit->HitCheckUp(BossX + 11, BossY + 51);
	//		int push2 = ObjectHit->HitCheckUp(BossX + 50, BossY + 51);
	//		BossY += max(push1, push2);
	//		if (fabs(pPos.y - BossY) > 2.0f)
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

void Principal::Draw()
{
	MainMap* mainmap = FindGameObject<MainMap>();
	int scX = 0;
	int scY = 0;
	if (mainmap)
	{
		scX = mainmap->GetScrollX();
		scY = mainmap->GetScrollY();
	}
	DrawRectGraph(BossX - scX, BossY - scY, 192 * MovementsPattern, 256 * DirChara, 192, 256, BossImage, 1, Xdir, 0);
}
