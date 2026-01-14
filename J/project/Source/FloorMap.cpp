#include "MainMap.h"
#include "Player.h"
#include "Enemy.h"
#include "CsvReader.h"
#include "FloorMap.h"
#include <vector>
#include <iostream>

using namespace std;

vector<vector<int>> floormaps;

FloorMap::FloorMap(int floor)
{
	char MAP_FILE_NAME[10000];                                 //csvファイルの読み込み処理
	sprintf_s<10000>(MAP_FILE_NAME, "data/floor/floor%02d.csv", floor);
	// CSVから呼んで、mapsを作る
	CsvReader* csv = new CsvReader(MAP_FILE_NAME);
	int lines = csv->GetLines();//縦の行数
	floormaps.resize(lines);//mapsの行数をcsvに合わせる
	for (int y = 0; y < lines; y++)
	{
		int cols = csv->GetColumns(y);//その行の横の数
		floormaps[y].resize(cols);//maps[y]の列数をcsvに合わせる
		for (int x = 0; x < cols; x++)
		{
			int num = csv->GetInt(y, x);
			floormaps[y][x] = num;
		}
	}
	delete csv;

	FloorImage = LoadGraph("data/image/artboad.png");//相沢お手製の床壁諸々
	BgSize = 64;



}

FloorMap::~FloorMap()
{
	DeleteGraph(FloorImage);
}

void FloorMap::Update()
{

}

void FloorMap::Draw()
{
	for (int y = 0; y < floormaps.size(); y++) //floormaps.size()で範囲を指定する
	{
		for (int x = 0; x < floormaps[y].size(); x++)
		{
			// ==================================================
			// まだ読み込みの設定をしていないものは×してます
			// ==================================================

			// ==================================================
			// 共通
			// ==================================================
			if (floormaps[y][x] == 0)//当たり判定あり空白
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 0, BgSize * 7, BgSize, BgSize, FloorImage, 1);
			}
			if (floormaps[y][x] == 4)//床
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 2, BgSize * 0, BgSize, BgSize, FloorImage, 1);
			}
			if (floormaps[y][x] == 50)//理科室床
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 0, BgSize * 0, BgSize, BgSize, FloorImage, 1);
			}
			if (floormaps[y][x] == 1)//廊下床
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 3, BgSize * 0, BgSize, BgSize, FloorImage, 1);
			}
			if (floormaps[y][x] == 0)//当たり判定あり空白
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 0, BgSize * 7, BgSize, BgSize, FloorImage, 1);
			}
			if (floormaps[y][x] == 2)//教室用床
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 3, BgSize * 0, BgSize, BgSize, FloorImage, 1);
			}
		}
	}
}

int FloorMap::HitCheckRight(int Px, int Py) //右の当たり判定
{
	return 0;
}

int FloorMap::HitCheckLeft(int Px, int Py)//右の当たり判定
{
	return 0;
}

int FloorMap::HitCheckUp(int Px, int Py) //上の当たり判定
{
	return 0;
}

int FloorMap::HitCheckDown(int Px, int Py) //下の当たり判定
{
	return 0;
}

void FloorMap::DrawMapArts(int MapsNum, int MapsX, int MapsY)
{

}

bool FloorMap::Warp(int Px, int Py)
{
	if (Py < 0)
	{
		return 0;
	}
	int x = Px / 64;
	int y = Py / 64;

	if (y < 0 || y >= floormaps.size()) return 0;
	if (x < 0 || x >= floormaps[y].size()) return 0;

	int tile = floormaps[y][x];
	if (tile >= 100 && tile < 200)
	{
		targetWarpFloor = tile - 100;

		warpOutX = x * 64;
		warpOutY = y * 64;

		return true;
	}

	return 0;
}