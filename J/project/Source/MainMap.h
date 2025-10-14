#pragma once
#include "../Library/GameObject.h"

class MainMap : public GameObject 
{
public:
	MainMap();
	~MainMap();
	void Update()override;
	void Draw()override;
private:
	int MapImage;//map‚Ì•`‰æ•Ï”
	

};