#pragma once
#include "../Library/GameObject.h"

class KeyManager : public GameObject
{
public:
	KeyManager() ;
	~KeyManager() ;
	void Update() override;
	void Draw() override;

public://setter
	void SetJpKey() { jpKey = true; }   //‘Œê‚Ì‰ñ“š‚ª³‰ğ
	void SetMtKey() { mtKey = true; }	//Z”‚Ì‰ñ“š‚ª³‰ğ
	void SetSciKey() { sciKey = true; }	//—‰È‚Ì‰ñ“š‚ª³‰ğ
	void SetSocKey() { socKey = true; }	//Ğ‰ï‚Ì‰ñ“š‚ª³‰ğ
	void SetExKey() { exKey = true; }	//“Á•Ê–â‘è‚Ì‰ñ“š‚ª³‰ğ

public://getter
	bool GetJpKey() const{ return jpKey; }
	bool GetMtKey() const{ return mtKey; }
	bool GetSciKey() const{ return sciKey; }
	bool GetSocKey() const{ return socKey; }
	bool GetExKey() const { return exKey; }
	bool GetSbjectKey() const { return subjectKey; }

private:
	bool jpKey;      //‘Œê‚ÌŒ®
	bool mtKey;	     //Z”‚ÌŒ®
	bool sciKey;     //—‰È‚ÌŒ®
	bool socKey;     //Ğ‰ï‚ÌŒ®
	bool exKey;	     //“Á•Ê–â‘è‚ÌŒ®
	bool subjectKey; //4‹³‰È‚ÌŒ®

private:
	const int WINDOW_BOX = LoadGraph("data/image/windowBOX.jpg");
};