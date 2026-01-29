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
	void INIT();
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
	void PlayStartSound();//スタートジングルを再生
	//void StopOpenDoorSound();//ドアを開けるジングルを停止
	void PlayClearMusic(); //クリアBGMを再生
	void StopClearMusic(); //クリアBGMを停止
	void PlayProJingle(); //プロローグジングルを再生
	void StopProJingle(); //プロローグジングルを停止

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
	//BGM
	const int HELL_MUSIC = LoadSoundMem("data/sound/top1.mp3");
	const int HEAVEN_MUSIC = LoadSoundMem("data/sound/NormalMusic.mp3");
	//歩く効果音
	const int WALK_SOUND = LoadSoundMem("data/sound/walk.mp3");
	//ドア開ける効果音
	const int DOOR_OPEN_TWO_SOUND = LoadSoundMem("data/sound/opentwodoor.mp3");
	//Start音
	const int START_SOUND = LoadSoundMem("data/sound/start.mp3");
	//ClearBGM
	const int CLEAR_MUSIC = LoadSoundMem("data/sound/clearmusic.mp3");
	//ProJingle
	const int PRO_JINGLE = LoadSoundMem("data/sound/chime.mp3");
public:
	void SetWarpOut(int x, int y) {
		warpOutX = x; warpOutY = y;
	}
	int GetwarpOutX() { return warpOutX; }
	int GetwarpOutY() { return warpOutY; }


private://state
	COMMON_STATE nowState;
};