#include "GameManager.h"
#include "MainMap.h"
#include "FloorMap.h"
#include "Common.h"
#include "Fader.h"
#include "Player.h"
#include "TextBox.h"
#include "KeyManager.h"
#include "Enemy.h"

GameManager::GameManager()
{
	//init
	Fader* fader = FindGameObject<Fader>();
	fader->FadeIn(4.0f);
	MainState = GAME_STATE::STATE_INIT;
	SubState = GAME_STATE::STATE_CONTINUE;
	textBox = FindGameObject<TextBox>();
	clearLag = 0.0f;
	clearFlag = false;
	playFirst = true;
}

GameManager::~GameManager()
{
}

void GameManager::Update()
{
	switch(MainState)
	{
	case GAME_STATE::STATE_INIT:
		if (GameManager::Init() == GAME_STATE::STATE_END)
		{
			MainState = GAME_STATE::STATE_PRO;
		}
		break;
	case GAME_STATE::STATE_PRO:
		if (GameManager::Pro() == GAME_STATE::STATE_END)
		{
			SubState = GAME_STATE::STATE_CONTINUE;
			MainState = GAME_STATE::STATE_GAME_CHECK;
		}
		break;
	case GAME_STATE::STATE_GAME_CHECK:
		playFirst = false;
		switch (GameCheck())
		{
	    case GAME_STATE::STATE_GAME_OVER:
		     MainState = GAME_STATE::STATE_GAME_OVER;
		     break;
		case GAME_STATE::STATE_LAST_GAME:
			MainState = GAME_STATE::STATE_LAST_GAME;
			break;
		case GAME_STATE::STATE_GAME_CLEAR:
			MainState = GAME_STATE::STATE_GAME_CLEAR;
			break;
	    }
	break;
	case GAME_STATE::STATE_LAST_GAME:
		switch (GameCheck())
		{
		case GAME_STATE::STATE_LAST_GAME:
			MainState = GAME_STATE::STATE_LAST_GAME;
			break;
		case GAME_STATE::STATE_GAME_CLEAR:
			MainState = GAME_STATE::STATE_GAME_CLEAR;
			break;
		}
		break;
	case GAME_STATE::STATE_GAME_CLEAR:
		clearLag += Time::DeltaTime();
		if (clearLag > 3.0f)
		{
			clearFlag = true;
		}
		if (clearFlag)
		{
			SceneManager::ChangeScene("CLEAR");
		}
		break;
	case GAME_STATE::STATE_GAME_OVER:
		SceneManager::ChangeScene("GAMEOVER");
		break;
	default:
		break;
	}
}

void GameManager::Draw()
{
}

GAME_STATE GameManager::Init()//‰Šúİ’è
{
	new FloorMap(1);//‰ŠúƒtƒƒA
	new MainMap(1);//‰Šúƒ}ƒbƒv
	new Player(64 * 5 + 64 * 4, 64 * 3 + 64 * 1);  //‰ŠúƒvƒŒƒCƒ„[¶
	new KeyManager();
	new TextBox();
	//new Enemy(400,400);
	// ()‚Ì’†‚Écsv‚Ì”š“ü‚ê‚ê‚Î“Ç‚İ‚İ‚Ü‚·

	// ˆÈ‰ºMainMap&FloorMap‚Ìcsv‚Ì”š
	//1 = Eˆõº/2 = —‰Èº/3 = }‘º/4 = Z’·º/5 = ‰¹Šyº/6 = ”üpº
	//101 = ‚PŠK‹³º‚P/102 = ‚PŠK‹³º‚Q/201 = ‚QŠK‹³º‚P/202 = ‚QŠK‹³º‚Q
	//1000 = ‚PŠK˜L‰º/2000 = ‚QŠK˜L‰º

	return GAME_STATE::STATE_END;
}

GAME_STATE GameManager::Pro()
{
	TextBox* textBox = FindGameObject<TextBox>();
	textBox->SetPro();
	Common* common = FindGameObject<Common>();
	common->PlayProJingle();
	return GAME_STATE::STATE_END;
}

GAME_STATE GameManager::GameCheck()
{
	switch (SubState)
	{
	case GAME_STATE::STATE_GAME_OVER:
		return GAME_STATE::STATE_GAME_OVER;
		break;
	case GAME_STATE::STATE_LAST_GAME:
		return GAME_STATE::STATE_LAST_GAME;
		break;
	case GAME_STATE::STATE_CONTINUE:
		return GAME_STATE::STATE_CONTINUE;
		break;
	}
}

GAME_STATE GameManager::LastGame()
{
	switch (SubState)
	{
	case GAME_STATE::STATE_GAME_CLEAR:
		return GAME_STATE::STATE_GAME_CLEAR;
		break;
	case GAME_STATE::STATE_CONTINUE:
		return GAME_STATE::STATE_CONTINUE;
		break;
	}
}

GAME_STATE GameManager::gameClear()
{
	return GAME_STATE::STATE_END;
}

GAME_STATE GameManager::gameOver()
{
	SceneManager::ChangeScene("GAMEOVER");
	return GAME_STATE::STATE_END;
}
