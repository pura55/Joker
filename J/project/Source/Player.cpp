#include "Player.h"

;Player::Player()
{
	CharacterImage = LoadGraph("");
}

Player::~Player() 
{

}

void Player::Update()
{
	float speed = 0;
	if (CheckHitKey(KEY_INPUT_D)) //Dキーを押したときの判定
	{
		PlayerX += speed; //座標を変数分ずらして移動する

		/*MovementsCount += 1;　　　//キャラの動きの処理（変更したい場合は後々変更可）
		if (MovementsCount >= 16) 
		{

			MovementsPattern = (MovementsPattern + 1) % 4 + 0;

			MovementsCount = 0;
		}*/                                    
	}

	if (CheckHitKey(KEY_INPUT_A)) //Aキーを押したときの判定
	{
		PlayerX -= speed;

	}

	if (CheckHitKey(KEY_INPUT_W)) //Wキーを押したときの判定
	{
		PlayerY -= speed;
	} 

	if (CheckHitKey(KEY_INPUT_S)) //Sキーを押したときの判定
	{
		PlayerY += speed;
	}


}

void Player::Draw() 
{
	DrawRectGraph(PlayerX, PlayerY, 0, 0, 0, 0, CharacterImage, TRUE); //プレイヤーの描画
}
