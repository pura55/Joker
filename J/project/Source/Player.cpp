#include "Player.h"
#include "Enemy.h"
#include "MainMap.h"
#include "Warp.h"
#include "FloorMap.h"
#include "Fader.h"
#include "GameManager.h"

Player::Player(int PX, int PY)//PX：プレイヤーのX座標　PY：プレイヤーのY座標
{
	CharacterImage = LoadGraph("data/image/playerAt.png");
	PlayerX = PX;
	PlayerY = PY;
	MovementsPattern = 0;
	MovementsCount = 0;
	DirChara = 2;
	onPlay = true;
}

Player::~Player() 
{
	DeleteGraph(CharacterImage);
	DeleteGraph(PLAYER_WALK_SOUND);
}

void Player::Update()
{
	GameManager* gameManager = FindGameObject<GameManager>();

	if (gameManager->GetPlayFirst())
	{
		MainMap* mainmap = FindGameObject<MainMap>();
		if (mainmap)
		{
			int scX = mainmap->GetScrollX();
			if (PlayerX - scX >= 700) mainmap->SetScrollX(PlayerX - 700);
			if (PlayerX - scX <= 500) mainmap->SetScrollX(PlayerX - 500);
			int scY = mainmap->GetScrollY();
			if (PlayerY - scY >= 350) mainmap->SetScrollY(PlayerY - 350);
			if (PlayerY - scY <= 200) mainmap->SetScrollY(PlayerY - 200);
		}
		FloorMap* floormap = FindGameObject<FloorMap>();
		if (floormap)
		{
			int scX = floormap->GetScrollX();
			if (PlayerX - scX >= 700) floormap->SetScrollX(PlayerX - 700);
			if (PlayerX - scX <= 500) floormap->SetScrollX(PlayerX - 500);
			int scY = floormap->GetScrollY();
			if (PlayerY - scY >= 350) floormap->SetScrollY(PlayerY - 350);
			if (PlayerY - scY <= 200) floormap->SetScrollY(PlayerY - 200);
		}
		return;
	}

	if (!onPlay)//プレイヤー操作時以外の硬直
	{
		return;
	}

	Fader* fader = FindGameObject<Fader>();
	if (!fader->GetRigor())//ワープ時の硬直
	{
		return;
	}
	Enemy* enemy = FindGameObject<Enemy>();
	MainMap* appear = FindGameObject<MainMap>();

	if (CheckHitKey(KEY_INPUT_D)) //Dキーを押したときの判定
	{
		DirChara = 0;
		PlayerX += speed; //座標を変数分ずらして移動する

		MovementsCount += 1; //キャラクターの動作の処理
		if (MovementsCount >= 16) {

			MovementsPattern = (MovementsPattern + 1) % 4 + 0;

			MovementsCount = 0;
		}

		MainMap* ObjectHit = FindGameObject<MainMap>();
		int push1 = ObjectHit->HitCheckRight(PlayerX + 50, PlayerY + 91);
		int push2 = ObjectHit->HitCheckRight(PlayerX + 50, PlayerY + 63);
		PlayerX -= max(push1, push2);
	}
	else if (CheckHitKey(KEY_INPUT_A)) //Aキーを押したときの判定
	{
		DirChara = 1;
		PlayerX -= speed;

		MovementsCount += 1;
		if (MovementsCount >= 16)
		{

			MovementsPattern = (MovementsPattern + 1) % 4 + 0;

			MovementsCount = 0;
		}

		MainMap* ObjectHit = FindGameObject<MainMap>();
		int push1 = ObjectHit->HitCheckLeft(PlayerX + 14, PlayerY + 91);
		int push2 = ObjectHit->HitCheckLeft(PlayerX + 14, PlayerY + 63);
		PlayerX += max(push1, push2);
	}
	else if (CheckHitKey(KEY_INPUT_S)) //Sキーを押したときの判定
	{
		DirChara = 2;
		PlayerY += speed; //座標を変数分ずらして移動する

		MovementsCount += 1;
		if (MovementsCount >= 16) {

			MovementsPattern = (MovementsPattern + 1) % 4 + 0;

			MovementsCount = 0;
		}

		MainMap* ObjectHit = FindGameObject<MainMap>();
		int push1 = ObjectHit->HitCheckDown(PlayerX + 14, PlayerY + 92);
		int push2 = ObjectHit->HitCheckDown(PlayerX + 50, PlayerY + 92);
		PlayerY -= max(push1, push2);
	}
	else if (CheckHitKey(KEY_INPUT_W)) //Wキーを押したときの判定
	{
		DirChara = 3;
		PlayerY -= speed;

		MovementsCount += 1;
		if (MovementsCount >= 16) {

			MovementsPattern = (MovementsPattern + 1) % 4 + 0;

			MovementsCount = 0;
		}

		MainMap* ObjectHit = FindGameObject<MainMap>();
		int push1 = ObjectHit->HitCheckUp(PlayerX + 14, PlayerY + 51);
		int push2 = ObjectHit->HitCheckUp(PlayerX + 50, PlayerY + 51);
		PlayerY += max(push1, push2);
	}
	// スクロール
	MainMap* mainmap = FindGameObject<MainMap>();
	if (mainmap)
	{
		int scX = mainmap->GetScrollX();
		if (PlayerX - scX >= 700) mainmap->SetScrollX(PlayerX - 700);
		if (PlayerX - scX <= 500) mainmap->SetScrollX(PlayerX - 500);
		int scY = mainmap->GetScrollY();
		if (PlayerY - scY >= 350) mainmap->SetScrollY(PlayerY - 350);
		if (PlayerY - scY <= 200) mainmap->SetScrollY(PlayerY - 200);
	}
	FloorMap* floormap = FindGameObject<FloorMap>();
	if (floormap)
	{
		int scX = floormap->GetScrollX();
		if (PlayerX - scX >= 700) floormap->SetScrollX(PlayerX - 700);
		if (PlayerX - scX <= 500) floormap->SetScrollX(PlayerX - 500);
		int scY = floormap->GetScrollY();
		if (PlayerY - scY >= 350) floormap->SetScrollY(PlayerY - 350);
		if (PlayerY - scY <= 200) floormap->SetScrollY(PlayerY - 200);
	}

	// ワープチェック
	if (mainmap && mainmap->Warp(PlayerX, PlayerY))
	{
		int prevX = PlayerX;
		int prevY = PlayerY;
		int outX = mainmap->GetWarpOutX();
		int outY = mainmap->GetWarpOutY();
		PlayerX = outX;
		PlayerY = outY;
		int targetFloor = 0;
		if (floormap)
		{
			targetFloor = floormap->GetTargetWarpFloor();
		}
		new Warp(mainmap->GetTargetWarpStage(),targetFloor, outX, outY);
		DestroyMe();
	}
}

void Player::Draw()
{
	//プレイヤー描写
	MainMap* mainmap = FindGameObject<MainMap>();
	int scX = 0;
	int scY = 0;
	if (mainmap)
	{
		scX = mainmap->GetScrollX();
		scY = mainmap->GetScrollY();
	}

	DrawRectGraph(PlayerX - scX,PlayerY - scY, 64 * MovementsPattern, 96 * DirChara, 64, 96, CharacterImage, TRUE);
}

bool Player::IsHit(float ex, float ey)
{
	Enemy* enemy = FindGameObject<Enemy>();
	//プレイヤーの座標はpx,py
	float dx = PlayerX - ex;
	float dy = PlayerY - ey;
	float sum = sqrt(dx * dx + dy * dy);
	if (sum < 30)
	{
		return true;
	}
	return false;
}