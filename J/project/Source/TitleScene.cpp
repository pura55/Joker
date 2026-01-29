#include "TitleScene.h"
#include "Fader.h"
#include "Common.h"
#include "MainMap.h"

int TitleScene::Blinkcount = 0;

TitleScene::TitleScene()
{
	new Common();
	Timer = 0.0f;
	changeFlag = false;
	IsChange = false;
	pushKey = true;
	Common* common = FindGameObject<Common>();
	common->StopHeavenMusic();
	common->StopHellMusic();
	common->StopClearMusic();
	MainMap* mainmap = FindGameObject<MainMap>();
	mainmap->ResetEnemyState();
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	Fader* fader = FindGameObject<Fader>();
	Common* common = FindGameObject<Common>();
	if (pushKey)
	{
		if (CheckHitKey(KEY_INPUT_SPACE)) 
		{
			changeFlag = true;
			pushKey = false;
			common->PlayStartSound();
			fader->FadeOut(3.0f);
		}
	}
	if (changeFlag)
	{
		Timer += Time::DeltaTime();
	}
	if (Timer > 3.0f)
	{
		IsChange = true;
	}
	if (IsChange)
	{
		SceneManager::ChangeScene("PLAY");
	}

	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
	Blinkcount++;
	if (Blinkcount > 90)
	{
		Blinkcount = 0;
	}
}


void TitleScene::Draw()
{
	extern const char* Version();
	DrawString(0, 20, Version(), GetColor(255,255,255));
	DrawString(0, 0, "TITLE SCENE", GetColor(255, 255, 255));
	DrawGraph(0, 0, TitleBg, TRUE);
	//DrawFormatString(100, 100, GetColor(255,255,255), "%4.1f", 1.0f / Time::DeltaTime()); //時間経過表してるファイル
	if (Blinkcount < 60)
	{
		SetFontSize(60);
		DrawString(600, 500, "Push [SPACE] To Play ", GetColor(255, 255, 255));
	}
}
