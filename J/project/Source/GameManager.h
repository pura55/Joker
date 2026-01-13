#pragma once
#include "../Library/GameObject.h"

enum class GAME_STATE
{
	STATE_INIT = 0,//èâä˙âª(initialize)
	STATE_PRO,
	STATE_GAMESTART,
	STATE_GAMEOVER,
	STATE_GAMECLERE,
	STATE_END

};

class GameManager : public GameObject
{
public:
	GameManager();
	~GameManager();
	void Update() override;
	void Draw() override;

	//setter
	void SetGameOver() { state = GAME_STATE::STATE_GAMEOVER; }

public:
	GAME_STATE Init();
	GAME_STATE Pro();
	GAME_STATE GameStart();
	GAME_STATE gameClear();
	GAME_STATE gameOver();
	
private:
	GAME_STATE state;


};