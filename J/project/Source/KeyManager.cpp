#include "KeyManager.h"

KeyManager::KeyManager()
{
	jpKey = false;
	mtKey = false;
	sciKey = false;
	socKey = false;
	exKey = false;
	subjectKey = false;
}

KeyManager::~KeyManager()
{
	DeleteGraph(WINDOW_BOX);
}

void KeyManager::Update()
{
	if (jpKey && mtKey && sciKey && socKey)//4‹³‰È‚Ì‰ñ“š‚ðŽè‚É“ü‚ê‚½‚Æ‚«
	{
		subjectKey = true;
	}
}

void KeyManager::Draw()
{
	if (CheckHitKey(KEY_INPUT_TAB))
	{
		DrawRectGraph(415, 60, 0, 0, 450, 600, WINDOW_BOX, TRUE);
        
	}
}
