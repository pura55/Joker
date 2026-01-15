#pragma once
#include "../Library/GameObject.h"

class Player : public GameObject 
{
public:
	Player(int PX, int PY);
	~Player();
	void Update()override;
	void Draw()override;
	void SetPlay(bool flag = true) { onPlay = flag; }
	bool IsHit(float ex, float ey);

public://getter
	int GetPlayerPositionX() const { return PlayerX; }
	int GetPlayerPositionY() const { return PlayerY; }
	bool GetPlay() { return onPlay; }
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
	const int PLAYER_WALK_SOUND = LoadSoundMem("data/sound/walk.mp3");


private://定数変数
	const float speed = 8.2f;
};