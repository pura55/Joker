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
	const int GetPlayerPositionX() { return PlayerX; }
	const int GetPlayerPositionY() { return PlayerY; }
	VECTOR3 GetPosition(){ return VECTOR3(PlayerX, PlayerY, 0); }

private:
	int CharacterImage;//キャラクターの描画変数
	int MovementsPattern; //動作のパターン
	int MovementsCount; //動作のカウント
	int DirChara;//向いてる方向
	float PlayerX; //プレイヤーのX座標
	float PlayerY; //プレイヤーのY座標
	bool onPlay; //プレイ中のフラッグ
};