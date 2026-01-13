#include "GameManager.h"
#include "MainMap.h"
#include "FloorMap.h"
#include "Common.h"
#include "Fader.h"
#include "Player.h"
#include "TextBox.h"

GameManager::GameManager()
{
	state = GAME_STATE::STATE_INIT;
}

GameManager::~GameManager()
{
}

void GameManager::Update()
{
	switch(state)
	{
	case GAME_STATE::STATE_INIT:
		if (GameManager::Init() == GAME_STATE::STATE_END)
		{
			state = GAME_STATE::STATE_PRO;
		}
		break;
	case GAME_STATE::STATE_PRO:
		if (GameManager::Pro() == GAME_STATE::STATE_END)
		{
			state = GAME_STATE::STATE_GAMESTART;
		}
		break;
	case GAME_STATE::STATE_GAMESTART:
		if (GameManager::GameStart() == GAME_STATE::STATE_END)
		{
			state = GAME_STATE::STATE_GAMEOVER;
		}
		break;
	case GAME_STATE::STATE_GAMEOVER:
		if (GameManager::gameOver() == GAME_STATE::STATE_END)
		{
			//blank
		}
		//GO();
		break;
	}
}

void GameManager::Draw()
{
}

GAME_STATE GameManager::Init()//‰Šúİ’è
{
		//new FloorMap(1);//‰ŠúƒtƒƒA
		//new MainMap(1);//‰Šúƒ}ƒbƒv
		//new Player(64 * 5 + 64 * 4, 64 * 3 + 64 * 1);  //‰ŠúƒvƒŒƒCƒ„[¶¬
	
	// ()‚Ì’†‚Écsv‚Ì”š“ü‚ê‚ê‚Î“Ç‚İ‚İ‚Ü‚·

	// ˆÈ‰ºMainMap&FloorMap‚Ìcsv‚Ì”š
	//1 = Eˆõº/2 = —‰Èº/3 = }‘º/4 = Z’·º/5 = ‰¹Šyº/6 = ”üpº
	//101 = ‚PŠK‹³º‚P/102 = ‚PŠK‹³º‚Q/201 = ‚QŠK‹³º‚P/202 = ‚QŠK‹³º‚Q
	//1000 = ‚PŠK˜L‰º/2000 = ‚QŠK˜L‰º

	return GAME_STATE::STATE_END;
}

GAME_STATE GameManager::Pro()
{
	//new TextBox();
	return GAME_STATE::STATE_END;
}

GAME_STATE GameManager::GameStart()
{
	return GAME_STATE::STATE_END;
}

GAME_STATE GameManager::gameClear()
{
	return GAME_STATE::STATE_END;
}

GAME_STATE GameManager::gameOver()
{
    //Šecpp‚ÅDestroyMe()
	//new GameOver();
	return GAME_STATE::STATE_END;
}
