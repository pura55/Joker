#include "PlayScene.h"
#include "Player.h"
#include "MainMap.h"
#include "FloorMap.h"
#include "TextBox.h"
#include "KeyManager.h"
#include "StartScene.h"
#include "common.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

void StartScene::Update()
{
	SetFontSize(20);
	if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::ChangeScene("PLAY");
	}
	if (CheckHitKey(KEY_INPUT_O)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void StartScene::Draw()
{
	DrawString(0, 0, "START SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
}
