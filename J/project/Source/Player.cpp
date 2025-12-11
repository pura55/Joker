#include "Player.h"
#include "Enemy.h"
#include "MainMap.h"

;Player::Player(int PX, int PY)//PX：プレイヤーのX座標　PY：プレイヤーのY座標
{
	CharacterImage = LoadGraph("data/image/playerAt.png");
	PlayerX = PX;
	PlayerY = PY;
	MovementsPattern = 0;
	MovementsCount = 0;
	DirChara = 2;
}

Player::~Player() 
{

}

void Player::Update()
{
	if (!onPlay)
	{
		return;
	}
	float speed = 2.2f;

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
		int push1 = ObjectHit->HitCheckRight(PlayerX + 50, PlayerY + 51);
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
		int push1 = ObjectHit->HitCheckLeft(PlayerX + 14, PlayerY + 51);
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
		int push1 = ObjectHit->HitCheckDown(PlayerX + 14, PlayerY + 63);
		int push2 = ObjectHit->HitCheckDown(PlayerX + 50, PlayerY + 63);
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

}

void Player::Draw() 
{
	DrawRectGraph(PlayerX , PlayerY, 64 * MovementsPattern, 96 * DirChara, 64, 96, CharacterImage, TRUE); //プレイヤーの描画
}
