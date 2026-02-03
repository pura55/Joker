#include "KeyManager.h"
#include "Player.h"
#include "Common.h"

KeyManager::KeyManager()
{
	SetDrawOrder(-5000);
	//鍵の初期化
	jpKey = false;
	mtKey = false;
	sciKey = false;
	socKey = false;
	exKey = false;
	aboveKey = false;
	subjectKey = false;

	//ウィンドウの初期化
	showWindow = false;
	RGB_JP = GetColor(255, 255, 255);
	RGB_MT = GetColor(255, 255, 255);
	RGB_SOC = GetColor(255, 255, 255);
	RGB_SCI = GetColor(255, 255, 255);
	RGB_EX = GetColor(255, 255, 255);
	RGB_ESC = GetColor(255, 255, 255);
	state = WINDOW::STATE_INIT;
	string = WINDOW::STATE_INIT;
}

KeyManager::~KeyManager()
{
	DeleteGraph(WINDOW_BOX);
}

void KeyManager::Update()
{
	Player* player = FindGameObject<Player>();
	Common* common = FindGameObject<Common>();

	//プレイヤーの動きを止める
	if (showWindow)
	{
		player->SetPlay(false);
	}
	//4教科の回答を手に入れたとき
	if (jpKey && mtKey && sciKey && socKey)
	{
		subjectKey = true;
	}

	//タスクの色を変更
	ChangeColor();

	//ウィンドウの状態
	switch (state)
	{
	case WINDOW::STATE_INIT:
		if (common->GetLagCheck())
		{
			if (player->GetPlay())//これによりウィンドウとテキストの同時生成を防ぐ
			{
				if (CheckHitKey(KEY_INPUT_TAB))
				{
					//	showWindow = true;
					SetFontSize(32);
					state = WINDOW::STATE_ON;
					common->SetLagIn_T();//連続押し込み防止
				}
			}
		}
		break;
	case WINDOW::STATE_OFF:
		if (common->GetLagCheck())
		{
			if (player->GetPlay())//これによりウィンドウとテキストの同時生成を防ぐ
			{
				if (CheckHitKey(KEY_INPUT_TAB))
				{
					//	showWindow = true;
					SetFontSize(32);
					state = WINDOW::STATE_ON;
					common->SetLagIn_T();//連続押し込み防止
				}
			}
		}
		break;
	case WINDOW::STATE_ON:
		if (common->GetLagCheck())
		{
			if (CheckHitKey(KEY_INPUT_TAB))
			{
				SetFontSize(16);
				//	showWindow = false;
				if (exKey && aboveKey)
				{
					state = WINDOW::STATE_TASK_FINISH;
				}
				else
				{
					state = WINDOW::STATE_OFF;
				}
				common->SetLagIn_T();//連続押し込み防止
			}
		}
		break;
	case WINDOW::STATE_TASK_FINISH:
		break;
	}
}

void KeyManager::Draw()
{

	switch (state)
	{
	case WINDOW::STATE_INIT:
		break;
	case WINDOW::STATE_OFF:
		break;
	case WINDOW::STATE_ON:
		switch (string)
		{
		case WINDOW::STATE_INIT:
			DrawRectGraph(415, 60, 0, 0, 450, 600, WINDOW_BOX, TRUE);
			DrawString(taskPosX + 128, taskPosY - taskSpaceY * 1, "タスク", GetColor(255, 255, 255), TRUE);
			DrawString(taskPosX, taskPosY + taskSpaceY * 0, "・国語の回答を盗む", RGB_JP, TRUE);
			DrawString(taskPosX, taskPosY + taskSpaceY * 1, "・算数の回答を盗む", RGB_MT, TRUE);
			DrawString(taskPosX, taskPosY + taskSpaceY * 2, "・理科の回答を盗む", RGB_SCI, TRUE);
			DrawString(taskPosX, taskPosY + taskSpaceY * 3, "・社会の回答を盗む", RGB_SOC, TRUE);
			if (subjectKey)
			{
				DrawString(taskPosX, taskPosY + taskSpaceY * 4, "・屋上の鍵を盗む", RGB_EX, TRUE);
			}
			if (exKey && aboveKey)
			{
				DrawString(taskPosX, taskPosY + taskSpaceY * 5, "・屋上から脱出する", RGB_ESC, TRUE);
			}
			Line();
			break;
		}
		break;
	}
}

void KeyManager::ChangeColor()
{
	//国語の回答を回収済みの場合タスクを緑にする
	if (jpKey)
	{
		RGB_JP = GetColor(0, 255, 0);
	}

	//算数の回答を回収済みの場合タスクを緑にする
	if (mtKey)
	{
		RGB_MT = GetColor(0, 255, 0);
	}

	//理科の回答を回収済みの場合タスクを緑にする
	if (sciKey)
	{
		RGB_SCI = GetColor(0, 255, 0);
	}

	//社会の回答を回収済みの場合タスクを緑にする
	if (socKey)
	{
		RGB_SOC = GetColor(0, 255, 0);
	}

	//屋上の鍵を回収済みの場合タスクを緑にする
	if (exKey && aboveKey)
	{
		RGB_EX = GetColor(0, 255, 0);
	}
}

void KeyManager::Line()
{
	//国語の回答を回収済みの場合タスクに線を引く
	if (jpKey)
	{
		DrawLine(taskPosX + lineFront, taskPosY + taskSpaceY * 0 + lineSpaceY * 1, taskPosX + 32 * 10 - lineBack, taskPosY + taskSpaceY * 0 + lineSpaceY * 1, RGB_JP);
		DrawLine(taskPosX + lineFront, taskPosY + taskSpaceY * 0 + lineSpaceY * 3, taskPosX + 32 * 10 - lineBack, taskPosY + taskSpaceY * 0 + lineSpaceY * 3, RGB_JP);
	}

	//算数の回答を回収済みの場合タスクを緑にする
	if (mtKey)
	{
		DrawLine(taskPosX + lineFront, taskPosY + taskSpaceY * 1 + lineSpaceY * 1, taskPosX + 32 * 10 - lineBack, taskPosY + taskSpaceY * 1 + lineSpaceY * 1, RGB_MT);
		DrawLine(taskPosX + lineFront, taskPosY + taskSpaceY * 1 + lineSpaceY * 3, taskPosX + 32 * 10 - lineBack, taskPosY + taskSpaceY * 1 + lineSpaceY * 3, RGB_MT);
	}

	//理科の回答を回収済みの場合タスクを緑にする
	if (sciKey)
	{
		DrawLine(taskPosX + lineFront, taskPosY + taskSpaceY * 2 + lineSpaceY * 1, taskPosX + 32 * 10 - lineBack, taskPosY + taskSpaceY * 2 + lineSpaceY * 1, RGB_SCI);
		DrawLine(taskPosX + lineFront, taskPosY + taskSpaceY * 2 + lineSpaceY * 3, taskPosX + 32 * 10 - lineBack, taskPosY + taskSpaceY * 2 + lineSpaceY * 3, RGB_SCI);
	}

	//社会の回答を回収済みの場合タスクを緑にする
	if (socKey)
	{
		DrawLine(taskPosX + lineFront, taskPosY + taskSpaceY * 3 + lineSpaceY * 1, taskPosX + 32 * 10 - lineBack, taskPosY + taskSpaceY * 3 + lineSpaceY * 1, RGB_SOC);
		DrawLine(taskPosX + lineFront, taskPosY + taskSpaceY * 3 + lineSpaceY * 3, taskPosX + 32 * 10 - lineBack, taskPosY + taskSpaceY * 3 + lineSpaceY * 3, RGB_SOC);
	}

	//屋上の鍵を回収済みの場合タスクを緑にする
	if (exKey)
	{
		DrawLine(taskPosX + lineFront, taskPosY + taskSpaceY * 4 + lineSpaceY * 1, taskPosX + 32 * 10 - lineBack, taskPosY + taskSpaceY * 4 + lineSpaceY * 1, RGB_EX);
		DrawLine(taskPosX + lineFront, taskPosY + taskSpaceY * 4 + lineSpaceY * 3, taskPosX + 32 * 10 - lineBack, taskPosY + taskSpaceY * 4 + lineSpaceY * 3, RGB_EX);
	}
}
