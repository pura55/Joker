#pragma once
#include "../Library/GameObject.h"

enum class COMMON_STATE
{
	STATE_WARP = 1,
	STATE_TEXT
};

class Common : public GameObject
{
public:
	Common();
	~Common();
	void Update() override;
	void WarpLag();
	void TextLag();

	void PlayHeavenMusic();  //先生チェイス用BGMを再生
	void StopHeavenMusic();  //先生チェイス用BGMを停止
	void PlayHellMusic();    //校長先生チェイス用BGMを再生
	void StopHellMusic();    //校長先生チェイス用BGMを停止
	void PlayWalkSound();    //プレイヤーwalk用ジングルを再生
	void StopWalkSound();    //プレイヤーwalk用ジングルを停止
	void PlayOpenDoorSound();//ドアを開けるジングルを再生
	//void StopOpenDoorSound();//ドアを開けるジングルを停止

public://setter
	void SetLagIn_W()
	{
		lagCheck = false;
		nowState = COMMON_STATE::STATE_WARP;
	}
	void SetLagIn_T()
	{
		lagCheck = false;
		nowState = COMMON_STATE::STATE_TEXT;
	}
	void SetFirstSpawn() { firstSpawn = false; }
	void SetFirstMove() { firstMove = false; }

public://getter
	bool GetLagCheck() const { return lagCheck; }
	bool GetFirstSpawn() const { return firstSpawn; }
	bool GetFirstMove() const { return firstMove; }
	bool GetPlayWlak() const { return playWalkFlag; }

public:
	float ClearTime;
	float TimeLag;//タイムラグ
	float walkTime;//効果音を止める時間
	float openTime;//効果音を止める時間
	bool lagCheck;//spaceを連続でおさない
	bool noDead;
	bool playWalkFlag; //歩くサウンドの判定
	bool playOpenFlag; //ドアを開けるサウンドの判定


	//校長先生用
	bool firstSpawn;     //校長最初の生成
	bool firstMove;      //校長先生の最初の移動
	bool firstText;      //校長先生出現テキスト生成
	bool firstPlaySound; //音割れサウンドを一回だけ再生

private:
	int warpOutX = 0;
	int warpOutY = 0;

private:
	const int HELL_MUSIC = LoadSoundMem("data/sound/bossMusic.mp3");
	const int HEAVEN_MUSIC = LoadSoundMem("data/sound/NormalMusic.mp3");
	const int WALK_SOUND = LoadSoundMem("data/sound/walk.mp3");
	const int DOOR_OPEN_TWO_SOUND = LoadSoundMem("data/sound/opentwodoor.mp3");

public:
	void SetWarpOut(int x, int y) {
		warpOutX = x; warpOutY = y;
	}
	int GetwarpOutX() { return warpOutX; }
	int GetwarpOutY() { return warpOutY; }


private://state
	COMMON_STATE nowState;
};