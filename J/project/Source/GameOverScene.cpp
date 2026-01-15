#include "GameOverScene.h"

GameOverScene::GameOverScene()
{
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
