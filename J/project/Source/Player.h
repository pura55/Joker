#pragma once
#include "../Library/GameObject.h"

class Player : public GameObject 
{
public:
	//基本関数
	Player(int PX, int PY);
	~Player();
	void Update()override;
	void Draw()override;
	//動作
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();
	//プレイ状態を設定
	void SetPlay(bool flag = true) { onPlay = flag; }
	//敵との当たり判定
	bool IsHit(float ex, float ey);
	bool BossIsHit(float ex, float ey);

public://getter
	//座標を取得
	int GetPlayerPositionX() const { return PlayerX; }
	int GetPlayerPositionY() const { return PlayerY; }
	//プレイ状態を取得
	bool GetPlay() { return onPlay; }
	//座標を取得
	VECTOR3 GetPosition() const { return VECTOR3(PlayerX, PlayerY, 0); }

private:
	int CharacterImage;//キャラクターの描画変数
	int MovementsPattern; //動作のパターン
	int MovementsCount; //動作のカウント
	int DirChara;//向いてる方向
	float PlayerX; //プレイヤーのX座標
	float PlayerY; //プレイヤーのY座標
	bool onPlay; //プレイ中のフラッグ

private://sound
	//歩く効果音
	const int PLAYER_WALK_SOUND = LoadSoundMem("data/sound/walk.mp3");


private://定数変数
	const float speed = 6.0f;
};