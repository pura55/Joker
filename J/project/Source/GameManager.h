#pragma once
#include "../Library/GameObject.h"
#include "TextBox.h"

enum class GAME_STATE
{
	STATE_INIT = 0,   //初期化(initialize)
	STATE_PRO,        //プロローグ  
	STATE_GAME_START, //ゲームスタート
	STATE_GAME_CHECK, //ゲーム監視
	STATE_LAST_GAME,  //最終決戦のゲーム監視
	STATE_GAME_OVER,  //ゲームオーバー
	STATE_GAME_CLEAR, //ゲームクリア
	STATE_END,        //ステイト終了
	STATE_CONTINUE    //ステイト継続

};

class GameManager : public GameObject
{
public:
	GameManager();
	~GameManager();
	void Update() override;
	void Draw() override;

	//setter
	void SetGameOver() { SubState = GAME_STATE::STATE_GAME_OVER; }
	void SetGameClear() { SubState = GAME_STATE::STATE_GAME_CLEAR; }

public:
	GAME_STATE Init();
	GAME_STATE Pro();
	GAME_STATE GameCheck();
	GAME_STATE LastGame();
	GAME_STATE gameClear();
	GAME_STATE gameOver();
	
private:
	GAME_STATE MainState;
	GAME_STATE SubState;
	TextBox* textBox;

private:
	float clearLag;
	bool clearFlag;
};