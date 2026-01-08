#include "TitleScene.h"
#include "Common.h"

TitleScene::TitleScene()
{
	new Common();
	TitleBg = LoadGraph("data/image/title.jpg");
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		SceneManager::ChangeScene("PLAY");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}


void TitleScene::Draw()
{
	extern const char* Version();
	DrawString(0, 20, Version(), GetColor(255,255,255));
	DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawGraph(0, 0, TitleBg, TRUE);
	//DrawFormatString(100, 100, GetColor(255,255,255), "%4.1f", 1.0f / Time::DeltaTime()); //時間経過表してるファイル
	DrawString(100, 400, "Push [ENTER]Key To Play", GetColor(255, 255, 255));
}
