#include "MainMap.h"
#include "Player.h"
#include "Enemy.h"
#include "CsvReader.h"
#include <vector>

using namespace std;

vector<vector<int>> maps;

MainMap::MainMap()
{
	char MAP_FILE_NAME[60];                                 //csvファイルの読み込み処理
	sprintf_s<60>(MAP_FILE_NAME, "Document/stage%02d.csv", StageNum);
	// CSVから呼んで、mapsを作る
	CsvReader* csv = new CsvReader(MAP_FILE_NAME);
	int lines = csv->GetLines();//縦の行数
	maps.resize(lines);//mapsの行数をcsvに合わせる
	for (int y = 0; y < lines; y++)
	{
		int cols = csv->GetColumns(y);//その行の横の数
		maps[y].resize(cols);//maps[y]の列数をcsvに合わせる
		for (int x = 0; x < cols; x++)
		{
			int num = csv->GetInt(y, x);
			maps[y][x] = num;
		}
	}
	delete csv;

	MapImage = LoadGraph("data/image/SchoolBg.png"); //mapの画像読み込み
	BgSize = 64;
	new Player(BgSize * 5 + BgSize * 4, BgSize * 3 + BgSize * 2);  //プレイヤー生成
	

}

MainMap::~MainMap()
{

}

void MainMap::Update()
{

}

void MainMap::Draw()
{
	for (int y = 0; y < maps.size(); y++) //maps.size()で範囲を指定する
	{
		for (int x = 0; x < maps[y].size(); x++)
		{
			DrawMapArts(maps[x][y], x, y);
		}
	}
}

int MainMap::HitCheckRight(int Px, int Py) //右の当たり判定
{
	if (Py < 64 * 2)
	{
		return 0;
	}
	int x = (Px - 64 * 4) / 64;
	int y = (Py - 64 * 2) / 64;
	if (y >= maps.size())//範囲外を表す
		return 0;
	if (maps[y][x] == 4)
	{
		return (Px - 64 * 4) % 64 + 1;
	}
	return 0;
}

int MainMap::HitCheckLeft(int Px, int Py) //左の当たり判定
{
	if (Py < 64 * 2)
	{
		return 0;
	}
	int x = (Px - 64 * 4) / 64;
	int y = (Py - 64 * 2) / 64;
	if (y >= maps.size())
		return 0;
	else if (maps[y][x] == 4)
	{
		return 64 - (Px - 64 * 4) % 64;
	}
	return 0;
}

int MainMap::HitCheckUp(int Px, int Py) //上の当たり判定
{
	if (Py < 64 * 2)
	{
		return 0;
	}
	int x = (Px - 64 * 4) / 64;
	int y = (Py - 64 * 2) / 64;
	if (y >= maps.size())
		return 0;
	else if (maps[y][x] == 4)
	{
		return 64 - (Py - 64 * 2) % 64;
	}
	return 0;
}

int MainMap::HitCheckDown(int Px, int Py) //下の当たり判定
{
	int x = (Px - 64 * 4) / 64;
	int y = (Py - 64 * 2) / 64;
	if (y >= maps.size())
		return 0;
	else if (maps[y][x] == 4)
	{
		return (Py - 64 * 2) % 64 + 1;
	}
	return 0;
}

void MainMap::DrawMapArts(int MapsNum, int MapsX, int MapsY)
{
	switch (MapsNum)
	{
	case 1://1階の床
		DrawRectGraph(MapsX * BgSize + BgSize * 4, MapsY * BgSize + BgSize * 2, BgSize * 0, BgSize * 3, BgSize, BgSize, MapImage, 1);
		break;
	case 2://教室の床			
		DrawRectGraph(MapsX * BgSize + BgSize * 4, MapsY * BgSize + BgSize * 2, BgSize * 4, BgSize * 0, BgSize, BgSize, MapImage, 1);
		break;
	case 4://床
		DrawRectGraph(MapsX * BgSize + BgSize * 4, MapsY * BgSize + BgSize * 2, BgSize * 2, BgSize * 0, BgSize, BgSize, MapImage, 1);
		break;
	case 20://壁下
		DrawRectGraph(MapsX * BgSize + BgSize * 4, MapsY * BgSize + BgSize * 2, BgSize * 1, BgSize * 1, BgSize, BgSize, MapImage, 1);
		break;
	case 30://壁上
		DrawRectGraph(MapsX * BgSize + BgSize * 4, MapsY * BgSize + BgSize * 2, BgSize * 0, BgSize * 1, BgSize, BgSize, MapImage, 1);
		break;
	}
}


