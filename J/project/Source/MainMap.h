#pragma once
#include "../Library/GameObject.h"
#include <vector>
#include "Common.h"

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
	void AppearBoss(int Px, int Py);
	void ResetEnemyState();

public://getter
    int GetScrollX() const { return scrollX; }
    int GetScrollY() const { return scrollY; }
	int GetTargetWarpStage() const { return targetWarpStage; }
    int GetTargetWarpFloor() const { return targetWarpFloor; }
	int GetWarpOutX() const { return warpOutX; }
	int GetWarpOutY() const { return warpOutY; }
	int GetAppear() const { return appear; }


private://画像
	int GoldBoss;//像
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
	int ExtentionImage;//！マーク
	int NapoImage;//ナポリタンの画像
	int DoorImage;//屋上ドア

private://sound
	const int NEXT_TEXT_SOUND = LoadSoundMem("data/sound/Nexttext.mp3");
	const int KEY_ROCK_SOUND = LoadSoundMem("data/sound/keydoor.mp3");
	const int KEY_UNROCK_SOUND = LoadSoundMem("data/sound/keyopen.mp3");
	const int DOOR_OPEN_ONE_SOUND = LoadSoundMem("data/sound/openonedoor.mp3");
	const int DOOR_OPEN_TWO_SOUND = LoadSoundMem("data/sound/opentwodoor.mp3");
	const int BOOK_OPEN_SOUND = LoadSoundMem("data/sound/Bookopen.mp3");


public:
	int StageNum;
	int scrollX;
	int scrollY;
	int targetWarpStage;
	int targetWarpFloor;
	int warpOutX = 0;
	int warpOutY = 0;
	bool appear;
	int SpawnRate = 0;//敵の出現確率

public://！用の変数
	int MarkX_Q = 0;
	int MarkY_Q = 0;
	int MarkX_Another = 0;
	int MarkY_Another = 0;
	bool ExFlag_Q;
	bool ExFlag_Another;
	
private:
	//Common* common;
	static int Chasetimer;
	static int Intervaltimer;
	static int OfficeEnemytimer;

private://定数
	const int BgSize = 64;//マップ素材の基本の大きさ
	const float inTime = 0.2f;//フェードインにかかる時間
	const bool stop = false;//keyプッシュを止める

};