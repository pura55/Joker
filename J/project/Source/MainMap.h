#pragma once
#include "../Library/GameObject.h"
#include <vector>

using namespace std;

class MainMap : public GameObject 
{
public:
	MainMap(int stage);
	~MainMap();
	void Update()override;
	void Draw()override;
	int HitCheckRight(int Px, int Py); //マップの当たり判定
	int HitCheckLeft(int Px, int Py);  
	int HitCheckUp(int Px, int Py);    
	int HitCheckDown(int Px, int Py); 
	void SetScrollX(int sx) { scrollX = sx; }
	void SetScrollY(int sy) { scrollY = sy; }
	void SetStageNum(int stage) { StageNum = stage; } //ステージの番号をセットする関数
	bool Warp(int Px, int Py);//ワープポイントの関数

public://getter
    int GetScrollX() const { return scrollX; }
    int GetScrollY() const { return scrollY; }
	int GetTargetWarpStage() const { return targetWarpStage; }
    int GetTargetWarpFloor() const { return targetWarpFloor; }
	int GetWarpOutX() const { return warpOutX; }
	int GetWarpOutY() const { return warpOutY; }


private://画像
	int FloorImage;//相沢お手製の床壁諸々
	int ArtImage;//アート系
	int BodyModelImage;//人体模型
	int ChoiceImage;//文字出るところ
	int MusicImage;//音楽系
	int PianoImage;//ピアノ
	int Pierrot2;//ピアノの椅子とか
	int ChairImage;//よさげな椅子
	int SofaImage;//よさげなソファ
	int STImage1;//教室系
	int STImage2;//教室系
	int STImage3;//教室系
	int STImage4;//教室系
	int STImage5;//教室系
	int STImage6;//教室系
	int STImage7;//教室系
	int STImage8;//教室系
	int ScienceChairImage;
	int LockerImage;//ロッカー
	int ScienceTableImage;
	int STChairImage;//机椅子
	int StaffChairImage;
	int ExclamationImage;//！マーク

public:
	int StageNum;
	int scrollX;
	int scrollY;
	int targetWarpStage;
	int targetWarpFloor;
	int warpOutX = 0;
	int warpOutY = 0;
	int MarkX = 0;
	int MarkY = 0;
	bool ExFlag;
	
private://定数
	const int BgSize = 64;//マップ素材の基本の大きさ
	const float inTime = 0.2f;//フェードインにかかる時間
	const bool stop = false;//keyプッシュを止める

};