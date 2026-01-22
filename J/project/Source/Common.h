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

	void PlayHeavenMusic();
	void StopHeavenMusic();
	void PlayHellMusic();
	void StopHellMusic();

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

public:
	float ClearTime;
	float TimeLag;//タイムラグ
	bool lagCheck;//spaceを連続でおさない
	bool noDead;


	//校長先生用
	bool firstSpawn;     //校長最初の生成
	bool firstMove;      //校長先生の最初の移動
	bool firstText;      //校長先生出現テキスト生成
	bool firstPlaySound; //音割れサウンドを一回だけ再生

private:
	int warpOutX = 0;
	int warpOutY = 0;
	const int HELL_MUSIC = LoadSoundMem("data/sound/bossMusic.mp3");
	const int HEAVEN_MUSIC = LoadSoundMem("data/sound/NormalMusic.mp3");

public:
	void SetWarpOut(int x, int y) {
		warpOutX = x; warpOutY = y;
	}
	int GetwarpOutX() { return warpOutX; }
	int GetwarpOutY() { return warpOutY; }


private://state
	COMMON_STATE nowState;
};