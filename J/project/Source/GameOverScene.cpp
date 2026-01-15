#include "GameOverScene.h"
#include "Fader.h"

GameOverScene::GameOverScene()
{
	Fader* fader = FindGameObject<Fader>();
	fader->FadeIn(2.0f);
	GameOverBg = LoadGraph("data/image/gameover.jpg");
}

GameOverScene::~GameOverScene()
{
	DeleteGraph(GameOverBg);
}

void GameOverScene::Update()
{
	if (CheckHitKey(KEY_INPUT_O)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void GameOverScene::Draw()
{
	DrawGraph(0, 0, GameOverBg, TRUE);
	DrawString(0, 0, "GAME OVER SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [O]Key To Title", GetColor(255, 255, 255));
}
