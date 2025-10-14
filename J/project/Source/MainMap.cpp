#include "MainMap.h"
#include "Player.h"
#include "Enemy.h"

MainMap::MainMap()
{
	MapImage = LoadGraph("");
	new Player;  //ƒvƒŒƒCƒ„[¶¬
	new Enemy;

}

MainMap::~MainMap()
{

}

void MainMap::Update()
{

}

void MainMap::Draw()
{
	DrawRectGraph(0, 0, 0, 0, 0, 0, MapImage, TRUE);
}
