#include "Warp.h"
#include "CsvReader.h"
#include "Player.h"
#include "MainMap.h"
#include "FloorMap.h"
#include "Enemy.h"
#include <vector>

using namespace std;

Warp::Warp(int mainMapStage, int floorMapFloor, int playerX, int playerY)
{
    // 既存のMainMapとFloorMapとキャラクターを破棄
    MainMap* mainmap = FindGameObject<MainMap>();
    if(mainmap) mainmap->DestroyMe();

    FloorMap* floormap = FindGameObject<FloorMap>();
    if(floormap) floormap->DestroyMe();

    Player* player = FindGameObject<Player>();
    if (player) player->DestroyMe();

    Enemy* enemy = FindGameObject<Enemy>();
    if (enemy) enemy->DestroyMe();

    // 新しく生成
    new FloorMap(floorMapFloor);
    new MainMap(mainMapStage);
    new Player(playerX, playerY);
}

Warp::~Warp()
{
}

void Warp::Update()
{
    // Warp自体は特に動かさないので空でOK
}

void Warp::Draw()
{
    // Warp自体は描画不要
}