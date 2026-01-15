#include "ClearScene.h"

ClearScene::ClearScene()
{
	ClearBg = LoadGraph("data/image/gameclear.jpg");
}

ClearScene::~ClearScene()
{
	//âÊëúÅEâπê∫ëfçﬁÇÃdelete
	DeleteGraph(ClearBg);
}

void ClearScene::Update()
{
	if (CheckHitKey(KEY_INPUT_O)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void ClearScene::Draw()
{
	DrawGraph(0, 0, ClearBg, TRUE);
	DrawString(0, 0, "CLEAR SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [O]Key To Title", GetColor(255, 255, 255));
}
