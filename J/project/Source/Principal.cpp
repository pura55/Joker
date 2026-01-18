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
}

Principal::~Principal()
{
	DeleteGraph(BossImage);
}

void Principal::Update()
{

	GameManager* gameManager = FindGameObject<GameManager>();
	Player* player = FindGameObject<Player>();
	VECTOR3 pPos = player->GetPosition();
	Fader* fader = FindGameObject<Fader>();

	if (player->IsHit(BossX + 192/2, BossY + 256/2))
	{
		gameManager->SetGameOver();
		fader->FadeIn(1.0f);
		SceneManager::ChangeScene("GAMEOVER");
	}

	if (fabs(pPos.x - BossX) > 5.0f && HitJudge)
	{
		if (pPos.x > BossX)//px > exの時
		{
			BossX += speed;//移動距離加算
			DirChara = 1; //方向

			MovementsCount += 1; //キャラクターの動作の処理
			if (MovementsCount >= 15) {

				MovementsPattern = (MovementsPattern + 1) % 3 + 0;

				MovementsCount = 0;
			}

			MainMap* ObjectHit = FindGameObject<MainMap>();
			int push1 = ObjectHit->HitCheckRight(BossX + 50, BossY + 51);
			int push2 = ObjectHit->HitCheckRight(BossX + 50, BossY + 63);
			BossX -= max(push1, push2);
			if (max(push1, push2) > 0)
			{
				HitJudge = false;
			}
		}
		else if
			(pPos.x < BossX)//px < exの時
		{
			BossX -= speed;
			DirChara = 1;

			MovementsCount += 1; //キャラクターの動作の処理
			if (MovementsCount >= 15) {

				MovementsPattern = (MovementsPattern + 1) % 3 + 0;

				MovementsCount = 0;
			}

			MainMap* ObjectHit = FindGameObject<MainMap>();
			int push1 = ObjectHit->HitCheckLeft(BossX + 11, BossY + 51);
			int push2 = ObjectHit->HitCheckLeft(BossX + 11, BossY + 63);
			BossX += max(push1, push2);
			if (max(push1, push2) > 0)
			{
				HitJudge = false;
			}
		}
	}
	else
	{
		if (pPos.y > BossY || !HitJudge)//py > eyの時
		{
			BossY += speed;
			DirChara = 0;

			MovementsCount += 1; //キャラクターの動作の処理
			if (MovementsCount >= 15) {

				MovementsPattern = (MovementsPattern + 1) % 3 + 0;

				MovementsCount = 0;
			}

			MainMap* ObjectHit = FindGameObject<MainMap>();
			int push1 = ObjectHit->HitCheckDown(BossX + 11, BossY + 255);
			int push2 = ObjectHit->HitCheckDown(BossX + 50, BossY + 255);
			BossY -= max(push1, push2);

			if (fabs(pPos.y - BossY) > 2.0f)
			{
				HitJudge = true;
			}
			if (max(push1, push2) > 0)
			{
				HitJudge = true;
			}
		}
		else if (pPos.y < BossY)//py < eyの時
		{
			BossY -= speed;
			DirChara = 2;

			MovementsCount += 1; //キャラクターの動作の処理
			if (MovementsCount >= 15) {

				MovementsPattern = (MovementsPattern + 1) % 3 + 0;

				MovementsCount = 0;
			}

			MainMap* ObjectHit = FindGameObject<MainMap>();
			int push1 = ObjectHit->HitCheckUp(BossX + 11, BossY + 51);
			int push2 = ObjectHit->HitCheckUp(BossX + 50, BossY + 51);
			BossY += max(push1, push2);
			if (fabs(pPos.y - BossY) > 2.0f)
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
	DrawRectGraph(BossX - scX, BossY - scY, 192 * MovementsPattern, 256 * DirChara, 192, 256, BossImage, TRUE);
}
