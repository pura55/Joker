#include "Fader.h"
#include "Screen.h"

Fader::Fader()
{
	DontDestroyOnSceneChange(); //シーン変更で消去されない
	SetDrawOrder(-10000); //なるべく最初に描画
	alpha = 0; 
	startAlpha = 0;
	endAlpha = 0;
	time= 0;
	now = 0;
	rgb = 0; // 黒
	rigor = true;
}

Fader::~Fader()
{
}

void Fader::Update()
{
	if (now < time)
	{
		now += Time::DeltaTime();
		float rate = now / time;//割合　
		alpha = (endAlpha - startAlpha) * rate + startAlpha;
		rigor = false;
	}
	else
	{
		rigor = true;
		alpha = endAlpha;
	}
	
}

void Fader::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBox(0, 0, Screen::WIDTH, Screen::HEIGHT, rgb, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Fader::FadeIn(float sec)
{
	startAlpha = 255;
	endAlpha = 0;
	time = sec;
	now = 0;
}
	

void Fader::FadeOut(float sec)
{
	startAlpha = 0;
	endAlpha = 255;
	time = sec;
	now = 0;
}

bool Fader::Finished()
{	
	return now >= time;
}

void Fader::SetColor(int r, int g, int b)
{
	rgb = GetColor(r, g , b);
}
