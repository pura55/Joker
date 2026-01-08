#pragma once
#include "../Library/GameObject.h"

enum class GAME_STATE
{
	STATE_INIT = 0,//‰Šú‰»(initialize)
	STATE_PRO,
	STATE_GAMESTART,
	STATE_GAMEOVER,
	STATE_GAMECLERE,
	STATE_END

};

class GameManager : public GameObject
{
public:
	GameManager();
	~GameManager();
	void Update() override;
	void Draw() override;

	//‰ñ“škey‚Ìsetter
	void SetJp(bool jp) { japaneseKey = jp; }         //‘Œê‚Ì‰ñ“š‚ª³‰ğ
	void SetKeyMath(bool math) { mathKey = math; }    //Z”‚Ì‰ñ“š‚ª³‰ğ
	void SetKeyScience(bool sci) { scienceKey = sci; }//—‰È‚Ì‰ñ“š‚ª³‰ğ
	void SetKeySociety(bool soc) { societyKey = soc; }//Ğ‰ï‚Ì‰ñ“š‚ª³‰ğ
	void SetKeyExtra(bool ex) { extraKey = ex; }      //“Á•Ê–â‘è‚Ì‰ñ“š‚ª³‰ğ
	void SetGameOver() { state = GAME_STATE::STATE_GAMEOVER; }

public:
	GAME_STATE Init();
	GAME_STATE Pro();
	GAME_STATE GameStart();
	GAME_STATE gameClear();
	GAME_STATE gameOver();
	

public:
	bool GetKeyAll() const { return ALL_KEY_IS_TRUE; }
private:
	GAME_STATE state;

	//Œ®‚ğtrue‚É‚·‚é‚Æ‰ğ“š‚ğŠ‚µ‚Ä‚¢‚é”»’è‚É‚È‚é
	bool japaneseKey;  //‘Œê‚Ì³‰ğ—p‚ÌŒ®
	bool mathKey;      //Z”‚Ì³‰ğ—p‚ÌŒ®
	bool scienceKey;   //—‰È‚ÌŒ®
	bool societyKey;   //Ğ‰ï‚ÌŒ®
	bool extraKey;     //“Á•Ê–â‘è‚ÌŒ®
	bool ALL_KEY_IS_TRUE; //‚·‚×‚Ä‚ÌŒ®‚ğŠ‚·‚é‚Æture

	
	
	
};