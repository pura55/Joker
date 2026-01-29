#pragma once
#include "../Library/GameObject.h"

class Fader : public GameObject
{
public:
	Fader();
	~Fader();
	void Update() override;
	void Draw() override;

	//フェードイン
	void FadeIn(float sec);
	//フェードアウト
	void FadeOut(float sec);
	void FadeOutToIn(float sec);
	bool Finished();
	void SetColor(int r, int g, int b);

public://getter
	bool GetRigor() const { return rigor;}

private:
	int alpha;
	int startAlpha;
	int endAlpha;
	unsigned int rgb;
	float time;
	float now;
	bool rigor;
	bool OutIn;
};
