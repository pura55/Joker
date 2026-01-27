#pragma once
#include "../Library/SceneBase.h"

/// <summary>
/// タイトルシーン
/// 
/// タイトルを表示して、キーを押したらプレイシーンに移行する。
/// </summary>
class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene();
	void Update() override;
	void Draw() override;
private:
	float Timer;
	bool changeFlag;
	bool IsChange;
	bool pushKey;
	static int Blinkcount;

private:
	//タイトル画像
	const int TitleBg = LoadGraph("data/image/title.jpg");
};
