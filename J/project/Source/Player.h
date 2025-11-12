#pragma once
#include "../Library/GameObject.h"

class Player : public GameObject 
{
public:
	Player(int PX, int PY);
	~Player();
	void Update()override;
	void Draw()override;
	
private:
	int CharacterImage;//キャラクターの描画変数
	float PlayerX; //プレイヤーのX座標
	float PlayerY; //プレイヤーのY座標
	
};