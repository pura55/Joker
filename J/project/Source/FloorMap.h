#pragma once
#include "../Library/GameObject.h"
#include <vector>

using namespace std;

class FloorMap : public GameObject
{
public:
	FloorMap(int floor);
	~FloorMap();
	void Update()override;
	void Draw()override;
	int HitCheckRight(int Px, int Py); //マップの当たり判定
	int HitCheckLeft(int Px, int Py);
	int HitCheckUp(int Px, int Py);
	int HitCheckDown(int Px, int Py);
	void SetTargerWarpFloor(int floor) { targetWarpFloor = floor; }
	void SetScrollX(int sx) { scrollX = sx; }
	void SetScrollY(int sy) { scrollY = sy; }
	void SetStageNum(int stage) { StageNum = stage; } //ステージの番号をセットする関数
	void DrawMapArts(int MapsNum, int MapsX, int MapsY); //Mapの描画数字を管理する関数
	bool Warp(int Px, int Py);//ワープポイントの関数

public://getter
	int GetScrollX() { return scrollX; }
	int GetScrollY() { return scrollY; }
	int GetTargetWarpFloor() const { return targetWarpFloor; }
	int GetWarpOutX() const { return warpOutX; }
	int GetWarpOutY() const { return warpOutY; }

private:
	int FloorImage;//mapの描画変数
	int StageNum;
	int BgSize;
	int scrollX;
	int scrollY;
	int targetWarpStage;
	int targetWarpFloor;
	int warpOutX = 0;
	int warpOutY = 0;

};