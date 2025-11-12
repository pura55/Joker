#pragma once
#include "../Library/GameObject.h"

class MainMap : public GameObject 
{
public:
	MainMap();
	~MainMap();
	void Update()override;
	void Draw()override;
	int HitCheckRight(int Px, int Py); //マップの当たり判定
	int HitCheckLeft(int Px, int Py);  
	int HitCheckUp(int Px, int Py);    
	int HitCheckDown(int Px, int Py);  
	void SetStageNum(int stage) { StageNum = stage; } //ステージの番号をセットする関数
	void DrawMapArts(int MapsNum, int MapsX, int MapsY); //Mapの描画数字を管理する関数
private:
	int MapImage;//mapの描画変数
	int StageNum;
	int BgSize;

};