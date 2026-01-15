#include "GameManager.h"
#include "MainMap.h"
#include "FloorMap.h"
#include "Common.h"
#include "Fader.h"
#include "Player.h"
#include "TextBox.h"
#include "KeyManager.h"

GameManager::GameManager()
{
	MainState = GAME_STATE::STATE_INIT;
	SubState = GAME_STATE::STATE_CONTINUE;
	textBox = FindGameObject<TextBox>();
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
		switch (GameCheck())
		{
	    case GAME_STATE::STATE_GAME_OVER:
		     MainState = GAME_STATE::STATE_GAME_OVER;
		     break;
	}
	break;

	case GAME_STATE::STATE_GAME_OVER:
		if (GameManager::gameOver() == GAME_STATE::STATE_END)
		{
			MainState = GAME_STATE::STATE_END;
		}
		break;
	default:
		break;
	}
}

void GameManager::Draw()
{
	switch (MainState)
	{
	case GAME_STATE::STATE_INIT:
		DrawString(0, 100, "STATE INIT", TRUE);
		break;
	case GAME_STATE::STATE_PRO:
		DrawString(0, 100, "STATE PRO", TRUE);
		break;
	case GAME_STATE::STATE_GAME_CHECK:
		DrawString(0, 100, "STATE CHECK", TRUE);
		break;

	case GAME_STATE::STATE_GAME_OVER:
		DrawString(0, 100, "STATE GAMEOVER", TRUE);
		break;
	case GAME_STATE::STATE_GAME_CLEAR:
		DrawString(0, 100, "STATE GAMECLEAR", TRUE);
		break;
	default:
		break;
	}
}

GAME_STATE GameManager::Init()//èâä˙ê›íË
{
	new FloorMap(1);//èâä˙ÉtÉçÉA
	new MainMap(1);//èâä˙É}ÉbÉv
	new Player(64 * 5 + 64 * 4, 64 * 3 + 64 * 1);  //èâä˙ÉvÉåÉCÉÑÅ[ê∂
	new KeyManager();
	new TextBox();

	// ()ÇÃíÜÇ…csvÇÃêîéöì¸ÇÍÇÍÇŒì«Ç›çûÇ›Ç‹Ç∑

	// à»â∫MainMap&FloorMapÇÃcsvÇÃêîéö
	//1 = êEàıé∫/2 = óùâ»é∫/3 = ê}èëé∫/4 = çZí∑é∫/5 = âπäyé∫/6 = î¸èpé∫
	//101 = ÇPäKã≥é∫ÇP/102 = ÇPäKã≥é∫ÇQ/201 = ÇQäKã≥é∫ÇP/202 = ÇQäKã≥é∫ÇQ
	//1000 = ÇPäKòLâ∫/2000 = ÇQäKòLâ∫

	return GAME_STATE::STATE_END;
}

GAME_STATE GameManager::Pro()
{
	switch (SubState)
	{
	case GAME_STATE::STATE_END:
		return GAME_STATE::STATE_END;
		break;
	case GAME_STATE::STATE_CONTINUE:
		return GAME_STATE::STATE_CONTINUE;
		break;
	}
}

GAME_STATE GameManager::GameCheck()
{
	switch (SubState)
	{
	case GAME_STATE::STATE_GAME_OVER:
		return GAME_STATE::STATE_GAME_OVER;
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
