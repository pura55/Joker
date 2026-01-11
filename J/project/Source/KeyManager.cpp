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
}
