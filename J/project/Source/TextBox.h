#pragma once
#include "../Library/GameObject.h"

class TextBox : public GameObject
{
public:
	TextBox();
	~TextBox();
	void Update()override;
	void Draw()override;
	//–â‘è‚Ì³Œë”»’èŠÖ”
	void QuestionJapanese();    //‘Œê‚Ì–â‘è”»’è
	void QuestionMathematics(); //Z”‚Ì–â‘è”»’è
	void QuestionScience();     //—‰È‚Ì–â‘è”»’è
	void QuestionSociety();     //Ğ‰ï‚Ì–â‘è”»’è
	void QuestionExtra();
	
private:
	int BoxImage;//map‚Ì•`‰æ•Ï”
	int QuestionCount;
	int QuestionNum;
	bool TextJudge;
	float time;
};