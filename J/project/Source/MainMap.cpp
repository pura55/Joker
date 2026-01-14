#include "MainMap.h"
#include "Player.h"
#include "Enemy.h"
#include "CsvReader.h"
#include "FloorMap.h"
#include "Fader.h"
#include "Common.h"
#include "TextBox.h"
#include "KeyManager.h"
#include <vector>
#include <iostream>

using namespace std;

vector<vector<int>> maps;

int MainMap::Chasetimer = 0;
int MainMap::Intervaltimer = 0;

enum class EnemyState
{
	Chase, // 追尾
	Idle, // 待機
	Interval //インターバル
};
EnemyState currentState = EnemyState::Idle;

MainMap::MainMap(int stage)
{
	char MAP_FILE_NAME[10000];                                 //csvファイルの読み込み処理
	sprintf_s<10000>(MAP_FILE_NAME, "data/maps/stage%02d.csv", stage);
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

	StageNum = stage;
	ExFlag_Q = false;
	ExFlag_Another = false;

	GoldBoss= LoadGraph("data/image/bigboss.png");//像
	FloorImage = LoadGraph("data/image/artboad.png");//相沢お手製の床壁諸
	ArtImage = LoadGraph("data/image/Artrooms.png");//アート系
	BodyModelImage = LoadGraph("data/image/Bodymodel.png");//人体模型
	ChoiceImage = LoadGraph("data/image/choice.png");//文字出るところ
	MusicImage = LoadGraph("data/image/Msrooms.png");//音楽系
	PianoImage = LoadGraph("data/image/Piano.png");//ピアノ
	Pierrot2 = LoadGraph("data/image/pierrot2.png");//ピアノの椅子とか
	ChairImage = LoadGraph("data/image/schoolchair.png");//よさげな椅子
	SofaImage = LoadGraph("data/image/sofa_school.png");//よさげなソファ
	STImage1 = LoadGraph("data/image/ST-class.png");//教室系
	STImage2 = LoadGraph("data/image/ST-Libry.png");//教室系
	STImage3 = LoadGraph("data/image/ST-Libry-1.png");//教室系
	STImage4 = LoadGraph("data/image/ST-Libry-2.png");//教室系
	STImage5 = LoadGraph("data/image/ST-Libry-3.png");//教室系
	STImage6 = LoadGraph("data/image/ST-Schl-1.png");//教室系
	STImage7 = LoadGraph("data/image/ST-Schl-2.png");//教室系
	STImage8 = LoadGraph("data/image/ST-Schl-3.png");//教室系
	ScienceChairImage = LoadGraph("data/image/ST-Schl-chair.png");
	LockerImage = LoadGraph("data/image/ST-Schl-I01.png");//ロッカー
	ScienceTableImage = LoadGraph("data/image/ST-Schl-I02.png");
	STChairImage = LoadGraph("data/image/student.png");//机椅子
	StaffChairImage = LoadGraph("data/image/TeacherChair.png");
	ExtentionImage = LoadGraph("data/image/ExBg.png");
	NapoImage = LoadGraph("data/image/napo2.png");//ナポ
	//new Enemy();

	srand((unsigned int)time(nullptr));

	int r = rand() % 100;
	if (currentState == EnemyState::Idle)
	{
		switch (StageNum)
		{
		case 1:
		{
			//出現確率
			if (r < 10)
			{
				// 出現候補座標（タイル単位）
				int spawnX[] = { 7, 10, 17, 20, 23 };
				int spawnY[] = { 9, 9, 9, 9, 9 };

				//出現場所候補最大値
				int count = sizeof(spawnX) / sizeof(spawnX[0]);
				int idx = rand() % count;

				float x = spawnX[idx] * 64.0f;
				float y = spawnY[idx] * 64.0f;

				new Enemy(x, y);
				currentState = EnemyState::Chase;
				Chasetimer = 0;
				if (r < 70)
				{
					new Enemy(64 * 7, 64 * 4);
					new Enemy(64 * 7, 64 * 9);
					new Enemy(64 * 7, 64 * 14);
					//new Enemy(64 * 10, 64 * 4);
					new Enemy(64 * 10, 64 * 9);
					new Enemy(64 * 10, 64 * 14);
					//new Enemy(64 * 17, 64 * 4);
					new Enemy(64 * 17, 64 * 9);
					new Enemy(64 * 17, 64 * 14);
					new Enemy(64 * 20, 64 * 4);
					new Enemy(64 * 20, 64 * 9);
					new Enemy(64 * 20, 64 * 14);
					new Enemy(64 * 23, 64 * 4);
					new Enemy(64 * 23, 64 * 9);
					new Enemy(64 * 23, 64 * 14);
					currentState = EnemyState::Chase;
					Chasetimer = 0;
				}
			}

		}
		break;
		case 2:
		{
			//出現確率
			if (r < 10)
			{
				// 出現候補座標（タイル単位）
				int spawnX[] = { 6, 12, 22, 22 };
				int spawnY[] = { 7, 7, 4, 11 };

				//出現場所候補最大値
				int count = sizeof(spawnX) / sizeof(spawnX[0]);
				int idx = rand() % count;

				float x = spawnX[idx] * 64.0f;
				float y = spawnY[idx] * 64.0f;

				new Enemy(x, y);
				currentState = EnemyState::Chase;
				Chasetimer = 0;
			}
		}
		break;
		case 3:
		{
			//出現確率
			if (r < 10)
			{
				// 出現候補座標（タイル単位）
				int spawnX[] = { 6, 14, 17, 23, 25 };
				int spawnY[] = { 11, 10, 10, 6, 14 };

				//出現場所候補最大値
				int count = sizeof(spawnX) / sizeof(spawnX[0]);
				int idx = rand() % count;

				float x = spawnX[idx] * 64.0f;
				float y = spawnY[idx] * 64.0f;

				new Enemy(x, y);
				currentState = EnemyState::Chase;
				Chasetimer = 0;
			}
		}
		break;
		case 4:
		{
			//出現確率
			if (r < 10)
			{
				// 出現候補座標（タイル単位）
				int spawnX[] = { 5, 6, 7, 8 };
				int spawnY[] = { 5, 6, 7, 8 };

				//出現場所候補最大値
				int count = sizeof(spawnX) / sizeof(spawnX[0]);
				int idx = rand() % count;

				float x = spawnX[idx] * 64.0f;
				float y = spawnY[idx] * 64.0f;

				new Enemy(x, y);
				new Enemy(x, y);
				currentState = EnemyState::Chase;
				Chasetimer = 0;
			}
		}
		break;
		case 5:
		{
			//出現確率
			if (r < 10)
			{
				// 出現候補座標（タイル単位）
				int spawnX[] = { 6, 11, 18 };
				int spawnY[] = { 5, 5, 12 };

				//出現場所候補最大値
				int count = sizeof(spawnX) / sizeof(spawnX[0]);
				int idx = rand() % count;

				float x = spawnX[idx] * 64.0f;
				float y = spawnY[idx] * 64.0f;

				new Enemy(x, y);
				currentState = EnemyState::Chase;
				Chasetimer = 0;
			}
		}
		break;
		case 6:
		{
			//出現確率
			if (r < 10)
			{
				// 出現候補座標（タイル単位）
				int spawnX[] = { 6, 19 };
				int spawnY[] = { 8, 12 };

				//出現場所候補最大値
				int count = sizeof(spawnX) / sizeof(spawnX[0]);
				int idx = rand() % count;

				float x = spawnX[idx] * 64.0f;
				float y = spawnY[idx] * 64.0f;

				new Enemy(x, y);
				currentState = EnemyState::Chase;
				Chasetimer = 0;
			}
		}
		break;
		case 101:
		{
			//出現確率
			if (r < 10)
			{
				// 出現候補座標（タイル単位）
				int spawnX[] = { 4, 21 };
				int spawnY[] = { 12,12 };

				//出現場所候補最大値
				int count = sizeof(spawnX) / sizeof(spawnX[0]);
				int idx = rand() % count;

				float x = spawnX[idx] * 64.0f;
				float y = spawnY[idx] * 64.0f;

				new Enemy(x, y);
				currentState = EnemyState::Chase;
				Chasetimer = 0;
			}
		}
		break;
		case 102:
		{
			//出現確率
			if (r < 10)
			{
				// 出現候補座標（タイル単位）
				int spawnX[] = { 4, 21 };
				int spawnY[] = { 12, 12 };

				//出現場所候補最大値
				int count = sizeof(spawnX) / sizeof(spawnX[0]);
				int idx = rand() % count;

				float x = spawnX[idx] * 64.0f;
				float y = spawnY[idx] * 64.0f;

				new Enemy(x, y);
				currentState = EnemyState::Chase;
				Chasetimer = 0;
			}
		}
		break;
		case 201:
		{
			//出現確率
			if (r < 10)
			{
				// 出現候補座標（タイル単位）
				int spawnX[] = { 4 , 21 };
				int spawnY[] = { 12, 12 };

				//出現場所候補最大値
				int count = sizeof(spawnX) / sizeof(spawnX[0]);
				int idx = rand() % count;

				float x = spawnX[idx] * 64.0f;
				float y = spawnY[idx] * 64.0f;

				new Enemy(x, y);
				currentState = EnemyState::Chase;
				Chasetimer = 0;
			}
		}
		break;
		case 202:
		{
			//出現確率
			if (r < 10)
			{
				// 出現候補座標（タイル単位）
				int spawnX[] = { 4,  22 };
				int spawnY[] = { 12, 12 };

				//出現場所候補最大値
				int count = sizeof(spawnX) / sizeof(spawnX[0]);
				int idx = rand() % count;

				float x = spawnX[idx] * 64.0f;
				float y = spawnY[idx] * 64.0f;

				new Enemy(x, y);
				currentState = EnemyState::Chase;
				Chasetimer = 0;
			}
		}
		break;
		case 1000:
		{
			//出現確率
			if (r < 0)
			{
				// 出現候補座標（タイル単位）
				int spawnX[] = { 5, 6, 7, 8 };
				int spawnY[] = { 5, 6, 7, 8 };

				//出現場所候補最大値
				int count = sizeof(spawnX) / sizeof(spawnX[0]);
				int idx = rand() % count;

				float x = spawnX[idx] * 64.0f;
				float y = spawnY[idx] * 64.0f;

				new Enemy(x, y);
				currentState = EnemyState::Chase;
				Chasetimer = 0;
			}
		}
		break;
		case 2000:
		{
			//出現確率
			if (r < 0)
			{
				// 出現候補座標（タイル単位）
				int spawnX[] = { 5, 6, 7, 8 };
				int spawnY[] = { 5, 6, 7, 8 };

				//出現場所候補最大値
				int count = sizeof(spawnX) / sizeof(spawnX[0]);
				int idx = rand() % count;

				float x = spawnX[idx] * 64.0f;
				float y = spawnY[idx] * 64.0f;

				new Enemy(x, y);
				currentState = EnemyState::Chase;
				Chasetimer = 0;
			}
		}
		}
	}
	if (Chasetimer > 30)
	{
		Common* common = FindGameObject<Common>();
		int x = common->GetwarpOutX();
		int y = common->GetwarpOutY();
		if (x > 0 && y > 0)
		{
			new Enemy(x, y, 60);
		}
	}
}

MainMap::~MainMap()
{
	DeleteGraph(GoldBoss);
	DeleteGraph(FloorImage);
	DeleteGraph(ArtImage);
	DeleteGraph(BodyModelImage);
	DeleteGraph(ChoiceImage);
	DeleteGraph(MusicImage);
	DeleteGraph(PianoImage);
	DeleteGraph(Pierrot2);
	DeleteGraph(ChairImage);
	DeleteGraph(SofaImage);
	DeleteGraph(STImage1);
	DeleteGraph(STImage2);
	DeleteGraph(STImage3);
	DeleteGraph(STImage4);
	DeleteGraph(STImage5);
	DeleteGraph(STImage6);
	DeleteGraph(STImage7);
	DeleteGraph(STImage8);
	DeleteGraph(ScienceChairImage);
	DeleteGraph(LockerImage);
	DeleteGraph(ScienceTableImage);
	DeleteGraph(STChairImage);
	DeleteGraph(StaffChairImage);
	DeleteGraph(ExtentionImage);
	DeleteGraph(NapoImage);
}

void MainMap::Update()
{
	if (currentState == EnemyState::Chase) {
		DrawString(100, 700, "chase", GetColor(255, 255, 255));
		Chasetimer++;                // カウント
		if (Chasetimer > 900) {      // 15秒後 (60FPS想定)
			currentState = EnemyState::Interval;
			Chasetimer = 0;          // タイマーリセット
			DrawString(100, 700, "interval1", GetColor(255, 0, 0));
		}
	}
	if (currentState == EnemyState::Interval) {
		DrawString(100, 700, "interval2", GetColor(255, 255, 255));
		Intervaltimer++;                // カウント
		if (Intervaltimer > 600) {      // 10秒後 (60FPS想定)
			currentState = EnemyState::Idle;
			Intervaltimer = 0;          // タイマーリセット
			DrawString(100, 700, "idle", GetColor(255, 0, 0));
		}
	}

	Player* player = FindGameObject<Player>();
	float px = player->GetPlayerPositionX();
	float py = player->GetPlayerPositionY();

	TextBox* textBox = FindGameObject<TextBox>();
	Common* common = FindGameObject<Common>();
	KeyManager* keyManager = FindGameObject<KeyManager>();

	switch (StageNum)//textboxへの遷移（問題）
	{
	case 1: //職員室 
		MarkX_Q = 64 * 19 + 10;
		MarkY_Q = 64 * 12;
		if (keyManager->GetExKey())
		{
			ExFlag_Q = false;
		}
		else if (keyManager->GetSbjectKey())
		{
			ExFlag_Q = true;
		   if (fabs((px + 32) - (MarkX_Q + 12)) < 80 && fabs((py + 48) - (MarkY_Q + 12)) < 80)
		   {
			   if(common->GetLagCheck())
			   {
				   if (player->GetPlay())//この判定をはさむことで回答中の問題の再生成を防ぐ
				   {
					   if (CheckHitKey(KEY_INPUT_SPACE))
					   {
						   textBox->SetExtra();//特別問題
						   common->SetLagIn_T();//連続押し込み防止
					   }

				   }
			   }
		   }
		}
		else
		{
			ExFlag_Q = false;
		}
		break;

	case 2://理科室
		MarkX_Q = 64 * 22 + 18;
		MarkY_Q = 64 * 6 + 6;
		if (keyManager->GetSciKey())
		{
			ExFlag_Q = false;
		}
		else
		{
			ExFlag_Q = true;
			if (fabs((px + 32) - (MarkX_Q + 12)) < 80 && fabs((py + 48) - (MarkY_Q + 12)) < 80)
			{
				if (common->GetLagCheck())
				{
					if (player->GetPlay())
					{
						if (CheckHitKey(KEY_INPUT_SPACE))
						{
							textBox->SetScience();//理科
							common->SetLagIn_T();//連続押し込み防止
						}
					}
				}
			}
		}
		break;

	case 5://音楽室
		MarkX_Q = 64 * 11 + 19;
		MarkY_Q = 64 * 6;
		if (keyManager->GetJpKey())
		{
			ExFlag_Q = false;
		}
		else
		{
			ExFlag_Q = true;
			if (fabs((px + 32) - (MarkX_Q + 12)) < 80 && fabs((py + 48) - (MarkY_Q + 12)) < 80)
			{
				if (common->GetLagCheck())
				{
					if (player->GetPlay())
					{
						if (CheckHitKey(KEY_INPUT_SPACE))
						{
							textBox->SetJapanese();//国語
							common->SetLagIn_T();//連続押し込み防止
						}
					}

				}
			}
		}
		break;

	case 102://１階教室1
		MarkX_Q = 64 * 22 + 18;
		MarkY_Q = 64 * 10;
		if (keyManager->GetMtKey())
		{
			ExFlag_Q = false;
		}
		else
		{
			ExFlag_Q = true;
			if (fabs((px + 32) - (MarkX_Q + 12)) < 80 && fabs((py + 48) - (MarkY_Q + 12)) < 80)
			{
				if (common->GetLagCheck())
				{
					if (player->GetPlay())
					{
						if (CheckHitKey(KEY_INPUT_SPACE))
						{
							textBox->SetMath();//算数
							common->SetLagIn_T();//連続押し込み防止
						}
					}
				}
			}
		}
		break;

	case 201://2階教室1
		MarkX_Q = 64 * 4 + 18;
		MarkY_Q = 64 * 11 + 15;
		if (keyManager->GetSocKey())
		{
			ExFlag_Q = false;
		}
		else
		{
			ExFlag_Q = true;
			if (fabs((px + 32) - (MarkX_Q + 12)) < 80 && fabs((py + 48) - (MarkY_Q + 12)) < 80)
			{
				if (common->GetLagCheck())
				{
					if (player->GetPlay())
					{
						if (CheckHitKey(KEY_INPUT_SPACE))
						{
							textBox->SetSociety();//社会
							common->SetLagIn_T();//連続押し込み防止
						}
					}
				}
			}
		}
		break;

	default:
		ExFlag_Q = false;
		break;
	}

	switch (StageNum)//textBox（その他）
	{
	case 2://理科室
		
		MarkX_Another = 64 * 3 + 18;
		MarkY_Another = 64 * 14 + 6;
		if (keyManager->GetExKey())
		{
			ExFlag_Another = false;
		}
		else 
		{
			ExFlag_Another = true;
			if (fabs((px + 32) - MarkX_Another + 12) < 80 && fabs((py + 48) - MarkY_Another + 12) < 80)
			{
				if (common->GetLagCheck())
				{
					if (player->GetPlay())
					{
						if (CheckHitKey(KEY_INPUT_SPACE))
						{
							textBox->SetScienceHint();//理科のヒント
							common->SetLagIn_T();//連続押し込み防止
						}
					}
				}
			}
		}
		break;

	case 3://図書室
		
		MarkX_Another = 64 * 5;
		MarkY_Another = 64 * 3;
		if (keyManager->GetExKey())
		{
			ExFlag_Another = false;
		}
		else 
		{
			ExFlag_Another = true;
			if (fabs((px + 32) - (MarkX_Another + 12)) < 80 && fabs((py + 48) - (MarkY_Another + 12)) < 80)
			{
			
				if (common->GetLagCheck())
				{
					if (player->GetPlay())
					{
						if (CheckHitKey(KEY_INPUT_SPACE))
						{
							textBox->SetSocietyHint();//社会のヒント
							common->SetLagIn_T();//連続押し込み防止
						}
					}
				}
			}

			if (fabs((px + 32) - (MarkX_Another + (64 * 21 + 18) + 12)) < 80 && fabs((py + 48) - (MarkY_Another + (64 * 4 + 15) + 12)) < 80)
			{
				if (common->GetLagCheck())
				{
					if (player->GetPlay())
					{
						if (CheckHitKey(KEY_INPUT_SPACE))
						{
							textBox->SetJapaneseHint();//国語のヒント
							common->SetLagIn_T();//連続押し込み防止	
						}
					}
				}
			}
		}
		
		break;

	case 4://校長室
		MarkX_Another = 64 * 8 + 20;
		MarkY_Another = 64 * 13 + 4;
		if (keyManager->GetExKey())
		{
			ExFlag_Another = false;
		}
		else
		{
			ExFlag_Another = true;
			if (fabs((px + 32) - (MarkX_Another + 12)) < 80 && fabs((py + 48) - (MarkY_Another + 12)) < 80)
			{
				if (common->GetLagCheck())
				{
					if (player->GetPlay())
					{
						if (CheckHitKey(KEY_INPUT_SPACE))
						{
							textBox->SetPri();//何もない
							common->SetLagIn_T();//連続押し込み防止
						}
					}
				}
			}
		}
		break;
	case 6:// 美術室
		MarkX_Another = 64 * 12 + 20;
		MarkY_Another = 64 * 11 - 2;
		if (keyManager->GetExKey())
		{
			ExFlag_Another = false;
		}
		else 
		{
			ExFlag_Another = true;
			if (fabs((px + 32) - (MarkX_Another + 12)) < 128 && fabs((py + 48) - (MarkY_Another + 12)) < 192)
			{
				if (common->GetLagCheck())
				{
					if (player->GetPlay())
					{
						if (CheckHitKey(KEY_INPUT_SPACE))
						{
							textBox->SetArt();//何もない
							common->SetLagIn_T();//連続押し込み防止
						}
					}
				}
			}
		}
		break;

	case 101://１階教室1
		ExFlag_Another = true;
		MarkX_Another = 64 * 22 + 18;
		MarkY_Another = 64 * 10;
		if (keyManager->GetExKey())
		{
			ExFlag_Another = false;
		}
		else 
		{
			ExFlag_Another = true;
			if (fabs((px + 32) - (MarkX_Another + 12)) < 80 && fabs((py + 48) - (MarkY_Another + 12)) < 80)
			{
				if (common->GetLagCheck())
				{
					if (player->GetPlay())
					{
						if (CheckHitKey(KEY_INPUT_SPACE))
						{
							textBox->SetMathHint();//算数のヒント
							common->SetLagIn_T();//連続押し込み防止
						}
					}
				}
			}
		}
		break;

	case 202:// ２階教室2
		MarkX_Another = 64 * 7 + 18;
		MarkY_Another = 64 * 17;
		if (keyManager->GetExKey())
		{
			ExFlag_Another = false;
		}
		else 
		{
			ExFlag_Another = true;
			if (fabs((px + 32) - (MarkX_Another + 12)) < 80 && fabs((py + 48) - (MarkY_Another + 12)) < 80)
			{
				if (common->GetLagCheck())
				{
					if (player->GetPlay())
					{
						if (CheckHitKey(KEY_INPUT_SPACE))
						{
							textBox->SetCls();//何もない
							common->SetLagIn_T();//連続押し込み防止
						}
					}
				}
			}
			
		}
		break;

	default:
		ExFlag_Another = false;
		break;
	}
	
}

void MainMap::Draw()
{
	for (int y = 0; y < maps.size(); y++) //maps.size()で範囲を指定する
	{
		for (int x = 0; x < maps[y].size(); x++)
		{
			// ==================================================
			// まだ読み込みの設定をしていないものは×してます
			// ==================================================

			// ==================================================
			// 共通
			// ==================================================
			if (maps[y][x] == 0)//当たり判定あり空白
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 0, BgSize * 7, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 2)//教室用床
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 3, BgSize * 0, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 4)//床
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 2, BgSize * 0, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 20)//壁下
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 1, BgSize * 1, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 30)//壁上
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 0, BgSize * 1, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 8)//ロッカー
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 1, BgSize * 0, BgSize, BgSize * 4, LockerImage, 1);
			}
			if (maps[y][x] == 3)//おそらく花瓶　×
			{

			}
			//画面下部扉用床
			if (maps[y][x] == 1011 || maps[y][x] == 1012 || maps[y][x] == 1013 || maps[y][x] == 1014 ||
				maps[y][x] == 1015 || maps[y][x] == 1016 || maps[y][x] == 1017 || maps[y][x] == 1018 ||
				maps[y][x] == 1019 || maps[y][x] == 1020 || maps[y][x] == 2011 || maps[y][x] == 2012 ||
				maps[y][x] == 2013 || maps[y][x] == 2014 || maps[y][x] == 2015 || maps[y][x] == 2016 ||
				maps[y][x] == 2017 || maps[y][x] == 2018 || maps[y][x] == 2019 || maps[y][x] == 2020 ||
				maps[y][x] == 1105 || maps[y][x] == 1106 || maps[y][x] == 1107 || maps[y][x] == 1108)
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 3, BgSize * 0, BgSize, BgSize, FloorImage, 1);
			}
			//画面下部扉用理科室床
			if (maps[y][x] == 1101 || maps[y][x] == 1102 || maps[y][x] == 1103 || maps[y][x] == 1104)
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 0, BgSize * 0, BgSize, BgSize, FloorImage, 1);
			}
			//画面下部扉用教室床
			if (maps[y][x] == 2101 || maps[y][x] == 2102 || maps[y][x] == 2103 || maps[y][x] == 2104 ||
				maps[y][x] == 2105 || maps[y][x] == 2106 || maps[y][x] == 2107 || maps[y][x] == 2108)
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 3, BgSize * 0, BgSize, BgSize, FloorImage, 1);
			}
			// ==================================================
			// １階廊下 
			// ==================================================
			if (maps[y][x] == 1)//廊下床
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 3, BgSize * 0, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 100001)//上り階段
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y + 8 - scrollY, BgSize * 0, 44, BgSize * 4, BgSize * 2, STImage3, 1);
			}
			if (maps[y][x] == 1001 || maps[y][x] == 1003)//理科室ドア左上
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 6, BgSize * 4, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 10001 || maps[y][x] == 10003)//理科室ドア左下
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 7, BgSize * 4, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 1002 || maps[y][x] == 1004)//理科室ドア右上
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 5, BgSize * 4, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 10002 || maps[y][x] == 10004)//理科室ドア右下
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 4, BgSize * 4, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 1005 || maps[y][x] == 1007)//図書室ドア左上
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 1, BgSize * 4, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 10005 || maps[y][x] == 10007)//図書室ドア左下
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 3, BgSize * 4, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 1006 || maps[y][x] == 1008)//図書室ドア右上
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 0, BgSize * 4, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 10006 || maps[y][x] == 10008)//図書室ドア右下
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 2, BgSize * 4, BgSize, BgSize, FloorImage, 1);
			}
			// ==================================================
			// ２階廊下 
			// ==================================================
			if (maps[y][x] == 200001)//下り階段
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y + 8 - scrollY, BgSize * 3, BgSize * 0, BgSize * 4, BgSize * 2, STImage3, 1);
			}
			// ==================================================
			// 職員室　〇
			// ==================================================
			if (maps[y][x] == 61)//職員室机
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 1, 4, BgSize * 3, BgSize * 2, STImage7, 1);
			}
			if (maps[y][x] == 65)//職員室椅子下向き
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 1, BgSize * 0, BgSize, BgSize, StaffChairImage, 1);
			}
			if (maps[y][x] == 66)//職員室椅子上向き
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 2, BgSize * 0, BgSize, BgSize, StaffChairImage, 1);
			}
			if (maps[y][x] == 1111)//職員室扉左上
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 2, BgSize * 2, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 11011)//職員室扉左下
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 3, BgSize * 2, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 1112)//職員室扉右上
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 4, BgSize * 2, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 11012)//職員室扉右下
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 5, BgSize * 2, BgSize, BgSize, FloorImage, 1);
			}
			// ==================================================
			// 理科室　〇
			// ==================================================
			if (maps[y][x] == 50)//理科室床
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 0, BgSize * 0, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 51)//人体模型上
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 0, BgSize * 0, BgSize, BgSize * 2, BodyModelImage, 1);
			}
			if (maps[y][x] == 53)//理科室椅子
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 1, BgSize * 1, BgSize, BgSize, ScienceChairImage, 1);
			}
			if (maps[y][x] == 54)//理科室机
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 3 + 4, BgSize * 0, 248, BgSize * 2, ScienceTableImage, 1);
			}
			if (maps[y][x] == 55)//理科室教卓
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 7 + 4, 8, BgSize * 1, BgSize * 2, ScienceTableImage, 1);
			}
			// ==================================================
			// 図書室　〇
			// ==================================================
			if (maps[y][x] == 7)//椅子右向き
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 2 + 40, BgSize * 5, BgSize * 1, BgSize * 1, STImage1, 1);
			}
			if (maps[y][x] == 40)//椅子左向き
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 3 + 40, BgSize * 5, BgSize * 1, BgSize * 1, STImage1, 1);
			}
			if (maps[y][x] == 41)//椅子背もたれ
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 4 + 40, BgSize * 5 + 16, BgSize * 1, BgSize * 1, STImage1, 1);
			}
			if (maps[y][x] == 42)//椅子正面
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 2 + 40, BgSize * 4, BgSize * 1, BgSize * 1, STImage1, 1);
			}
			if (maps[y][x] == 43)//机上部
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 5, BgSize * 6 + 28, BgSize * 3, BgSize * 2, STImage3, 1);
			}
			if (maps[y][x] == 44)//机下部
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 5, BgSize * 6 + 32, BgSize * 3, BgSize * 2, STImage3, 1);
			}
			if (maps[y][x] == 45)//本棚（右向き）
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 6 + 62, BgSize * 8 + 8, BgSize, BgSize * 4, STImage5, 1);
			}
			if (maps[y][x] == 46)//本棚（正面
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 3, BgSize * 10, BgSize * 3, BgSize * 2, STImage5, 1);
			}
			if (maps[y][x] == 47)//本棚（左向き)
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 6 + 2, BgSize * 8 + 8, BgSize, BgSize * 4, STImage5, 1);
			}
			if (maps[y][x] == 48)//カウンター（縦）
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 1, BgSize * 0 + 30, BgSize, BgSize * 3, STImage2, 1);
			}
			if (maps[y][x] == 49)//カウンター（横)
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 0, BgSize * 4 + 28, BgSize * 3, BgSize * 2, STImage2, 1);
			}
			// ==================================================
			// 校長室　〇
			// ==================================================
			if (maps[y][x] == 34)//机
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 5 + 32, BgSize * 3 + 32, BgSize * 3, BgSize * 2, STImage8, 1);
			}
			if (maps[y][x] == 35)//椅子
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 2, BgSize * 0, BgSize * 1, BgSize * 1, StaffChairImage, 1);
			}
			if (maps[y][x] == 37)//来客椅子正面
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 1, BgSize * 0, BgSize * 3, BgSize * 2, SofaImage, 1);
			}
			if (maps[y][x] == 38)//来客机
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 1, BgSize * 2, BgSize * 3, BgSize * 1, SofaImage, 1);
			}
			if (maps[y][x] == 39)//来客椅子後ろ
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 1, BgSize * 3, BgSize * 3, BgSize * 2, SofaImage, 1);
			}
			if (maps[y][x] == 2111)//校長室ドア左上
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 1, BgSize * 4, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 21011)//校長室ドア左下
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 3, BgSize * 4, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 2112)//校長室ドア右上
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 0, BgSize * 4, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 21012)//校長室ドア右下
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 2, BgSize * 4, BgSize, BgSize, FloorImage, 1);
			}
			// ==================================================
			// 音楽室　〇
			// ==================================================
			if (maps[y][x] == 85)//机
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 6, BgSize * 0 + 32, BgSize, BgSize, MusicImage, 1);
			}
			if (maps[y][x] == 86)//ピアノ椅子 ピアノとの組み合わせが不格好だからいらないかも
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 4, BgSize * 0, BgSize, BgSize * 2, Pierrot2, 1);
			}
			if (maps[y][x] == 87)//ピアノ
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 0, BgSize * 0, BgSize * 3, BgSize * 3, PianoImage, 1);
			}
			if (maps[y][x] == 89)//指揮台
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 0, BgSize * 0, BgSize, BgSize * 2, MusicImage, 1);
			}
			if (maps[y][x] == 2001 || maps[y][x] == 2003)//音楽室扉左上
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 2, BgSize * 2, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 20001 || maps[y][x] == 20003)//音楽室扉左下
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 3, BgSize * 2, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 2002 || maps[y][x] == 2004)//音楽室扉右上
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 4, BgSize * 2, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 20002 || maps[y][x] == 20004)//音楽室扉右下
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 5, BgSize * 2, BgSize, BgSize, FloorImage, 1);
			}
			// ==================================================
			// 美術室 〇
			// ==================================================
			if (maps[y][x] == 91)//水道
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 3, BgSize * 0 + 16, BgSize, BgSize * 2, ScienceTableImage, 1);
			}
			if (maps[y][x] == 94)//イーゼル後面
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 2, BgSize * 3, BgSize, BgSize * 2, ArtImage, 1);
			}
			if (maps[y][x] == 95)//イーゼル右向き
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 0, BgSize * 5, BgSize, BgSize * 2, ArtImage, 1);
			}
			if (maps[y][x] == 96)//イーゼル左向き
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 1, BgSize * 5, BgSize, BgSize * 2, ArtImage, 1);
			}
			if (maps[y][x] == 97)//イーゼル正面
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 1, BgSize * 3, BgSize, BgSize * 2, ArtImage, 1);
			}
			if (maps[y][x] == 98)//ムキムキ校長像　×
			{
				DrawRectGraph(BgSize* x - scrollX, BgSize * y - 10 - scrollY, 0, 0, 192, 320, GoldBoss, 1);
			}
			if (maps[y][x] == 99)//美術室椅子
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 5, BgSize * 3, BgSize, BgSize, ArtImage, 1);
			}
			if (maps[y][x] == 2005 || maps[y][x] == 2007)//美術室扉左上
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 2, BgSize * 2, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 20005 || maps[y][x] == 20007)//美術室扉左下
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 3, BgSize * 2, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 2006 || maps[y][x] == 2008)//美術室扉右上
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 4, BgSize * 2, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 20006 || maps[y][x] == 20008)//美術室扉右下
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 5, BgSize * 2, BgSize, BgSize, FloorImage, 1);
			}
			// ==================================================
			// 教室
			// ==================================================
			if (maps[y][x] == 5)//教卓
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 4 + 40, BgSize * 0 + 32, BgSize, BgSize * 2, STImage1, 1);
			}
			if (maps[y][x] == 6)//机
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 0 + 8, BgSize * 0, BgSize, BgSize, STChairImage, 1);
			}
			if (maps[y][x] == 1113 || maps[y][x] == 1115 || maps[y][x] == 1117 || maps[y][x] == 1119
				|| maps[y][x] == 2113 || maps[y][x] == 2115 || maps[y][x] == 2117 || maps[y][x] == 2119)//教室扉左上
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 2, BgSize * 2, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 11013 || maps[y][x] == 11015 || maps[y][x] == 11017 || maps[y][x] == 11019
				|| maps[y][x] == 21013 || maps[y][x] == 21015 || maps[y][x] == 21017 || maps[y][x] == 21019)//教室扉左下
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 3, BgSize * 2, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 1114 || maps[y][x] == 1116 || maps[y][x] == 1118 || maps[y][x] == 1120
				|| maps[y][x] == 2114 || maps[y][x] == 2116 || maps[y][x] == 2118 || maps[y][x] == 2120)//教室扉右上
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 4, BgSize * 2, BgSize, BgSize, FloorImage, 1);
			}
			if (maps[y][x] == 11014 || maps[y][x] == 11016 || maps[y][x] == 11018 || maps[y][x] == 11020
				|| maps[y][x] == 21014 || maps[y][x] == 21016 || maps[y][x] == 21018 || maps[y][x] == 21020)//教室扉右下
			{
				DrawRectGraph(BgSize * x - scrollX, BgSize * y - scrollY, BgSize * 5, BgSize * 2, BgSize, BgSize, FloorImage, 1);
			}
		}
	}

	if (StageNum == 4)
	{
		DrawRectGraph(BgSize * 8 - scrollX, BgSize * 13 - scrollY, 0, 0, 64, 64, NapoImage, TRUE);
	}

	if (ExFlag_Q)
	{
		DrawRectGraph(MarkX_Q - scrollX, MarkY_Q - scrollY, 0, 0, 24, 24, ExtentionImage, TRUE);
	}
	if (ExFlag_Another)
	{
		DrawRectGraph(MarkX_Another - scrollX, MarkY_Another - scrollY, 0, 0, 24, 24, ExtentionImage, TRUE);
	
		if (StageNum == 3)
		{
			DrawRectGraph(MarkX_Another - scrollX + (64 * 21) + 18, MarkY_Another - scrollY + (64 * 4) + 15, 0, 0, 24, 24, ExtentionImage, TRUE);
		}
		/*if (StageNum == 6)
		{
			DrawRectGraph(MarkX_Another - scrollX + (64 * 21) + 18, MarkY_Another - scrollY + (64 * 4) + 15, 0, 0, 24, 24, ExtentionImage, TRUE);
		}*/
	}
}

int MainMap::HitCheckRight(int Px, int Py) //右の当たり判定
{
	if (Py < 0)
	{
		return 0;
	}
	int x = Px / 64;
	int y = Py / 64;
	if (x >= maps[y].size())
		return 0;
	else if (maps[y][x] == 0 || maps[y][x] == 20 || maps[y][x] == 8
		|| maps[y][x] == 7 || maps[y][x] == 40 || maps[y][x] == 41 || maps[y][x] == 42 || maps[y][x] == 43 || maps[y][x] == 44
		|| maps[y][x] == 45 || maps[y][x] == 46 || maps[y][x] == 47 || maps[y][x] == 48 || maps[y][x] == 49
		|| maps[y][x] == 61 || maps[y][x] == 65 || maps[y][x] == 66
		|| maps[y][x] == 51 || maps[y][x] == 53 || maps[y][x] == 54 || maps[y][x] == 55
		|| maps[y][x] == 34 || maps[y][x] == 35 || maps[y][x] == 37 || maps[y][x] == 38 || maps[y][x] == 39
		|| maps[y][x] == 85 || maps[y][x] == 87 || maps[y][x] == 89
		|| maps[y][x] == 91 || maps[y][x] == 94 || maps[y][x] == 95 || maps[y][x] == 96 || maps[y][x] == 97 || maps[y][x] == 98||maps[y][x] == 99
		|| maps[y][x] == 5 || maps[y][x] == 6
		|| maps[y][x] == 10001 || maps[y][x] == 10002 || maps[y][x] == 10003 || maps[y][x] == 10004
		|| maps[y][x] == 10005 || maps[y][x] == 10006 || maps[y][x] == 10007 || maps[y][x] == 10008
		|| maps[y][x] == 20001 || maps[y][x] == 20002 || maps[y][x] == 20003 || maps[y][x] == 20004
		|| maps[y][x] == 20005 || maps[y][x] == 20006 || maps[y][x] == 20007 || maps[y][x] == 20008
		|| maps[y][x] == 11011 || maps[y][x] == 11012 || maps[y][x] == 21011 || maps[y][x] == 21012
		|| maps[y][x] == 11013 || maps[y][x] == 11014 || maps[y][x] == 11015 || maps[y][x] == 11016
		|| maps[y][x] == 11017 || maps[y][x] == 11018 || maps[y][x] == 11019 || maps[y][x] == 11020
		|| maps[y][x] == 21013 || maps[y][x] == 21014 || maps[y][x] == 21015 || maps[y][x] == 21016
		|| maps[y][x] == 21017 || maps[y][x] == 21018 || maps[y][x] == 21019 || maps[y][x] == 21020
		|| maps[y][x] == 100001 || maps[y][x] == 200001)
	{
		return Px % 64 + 1;
	}
	return 0;
}

int MainMap::HitCheckLeft(int Px, int Py)//右の当たり判定
{
	if (Py < 0)
	{
		return 0;
	}
	int x = Px / 64;
	int y = Py / 64;
	if (x >= maps[y].size())
		return 0;
	else if (maps[y][x] == 0 || maps[y][x] == 20 || maps[y][x] == 8
		|| maps[y][x] == 7 || maps[y][x] == 40 || maps[y][x] == 41 || maps[y][x] == 42 || maps[y][x] == 43 || maps[y][x] == 44
		|| maps[y][x] == 45 || maps[y][x] == 46 || maps[y][x] == 47 || maps[y][x] == 48 || maps[y][x] == 49
		|| maps[y][x] == 61 || maps[y][x] == 65 || maps[y][x] == 66
		|| maps[y][x] == 51 || maps[y][x] == 53 || maps[y][x] == 54 || maps[y][x] == 55
		|| maps[y][x] == 34 || maps[y][x] == 35 || maps[y][x] == 37 || maps[y][x] == 38 || maps[y][x] == 39
		|| maps[y][x] == 85 || maps[y][x] == 87 || maps[y][x] == 89
		|| maps[y][x] == 91 || maps[y][x] == 94 || maps[y][x] == 95 || maps[y][x] == 96 || maps[y][x] == 97 || maps[y][x] == 98 || maps[y][x] == 99
		|| maps[y][x] == 5 || maps[y][x] == 6
		|| maps[y][x] == 10001 || maps[y][x] == 10002 || maps[y][x] == 10003 || maps[y][x] == 10004
		|| maps[y][x] == 10005 || maps[y][x] == 10006 || maps[y][x] == 10007 || maps[y][x] == 10008
		|| maps[y][x] == 20001 || maps[y][x] == 20002 || maps[y][x] == 20003 || maps[y][x] == 20004
		|| maps[y][x] == 20005 || maps[y][x] == 20006 || maps[y][x] == 20007 || maps[y][x] == 20008
		|| maps[y][x] == 11011 || maps[y][x] == 11012 || maps[y][x] == 21011 || maps[y][x] == 21012
		|| maps[y][x] == 11013 || maps[y][x] == 11014 || maps[y][x] == 11015 || maps[y][x] == 11016
		|| maps[y][x] == 11017 || maps[y][x] == 11018 || maps[y][x] == 11019 || maps[y][x] == 11020
		|| maps[y][x] == 21013 || maps[y][x] == 21014 || maps[y][x] == 21015 || maps[y][x] == 21016
		|| maps[y][x] == 21017 || maps[y][x] == 21018 || maps[y][x] == 21019 || maps[y][x] == 21020
		|| maps[y][x] == 100001 || maps[y][x] == 200001)
	{
		return 64 - Px % 64;
	}
	return 0;
}

int MainMap::HitCheckUp(int Px, int Py) //上の当たり判定
{
	if (Py < 0)
	{
		return 0;
	}
	int x = Px / 64;
	int y = Py / 64;
	if (y >= maps.size())
		return 0;
	else if (maps[y][x] == 0 || maps[y][x] == 20 || maps[y][x] == 8
		|| maps[y][x] == 7 || maps[y][x] == 40 || maps[y][x] == 41 || maps[y][x] == 42 || maps[y][x] == 43 || maps[y][x] == 44
		|| maps[y][x] == 45 || maps[y][x] == 46 || maps[y][x] == 47 || maps[y][x] == 48 || maps[y][x] == 49
		|| maps[y][x] == 61 || maps[y][x] == 65 || maps[y][x] == 66
		|| maps[y][x] == 51 || maps[y][x] == 53 || maps[y][x] == 54 || maps[y][x] == 55
		|| maps[y][x] == 34 || maps[y][x] == 35 || maps[y][x] == 37 || maps[y][x] == 38 || maps[y][x] == 39
		|| maps[y][x] == 85 || maps[y][x] == 87 || maps[y][x] == 89
		|| maps[y][x] == 91 || maps[y][x] == 94 || maps[y][x] == 95 || maps[y][x] == 96 || maps[y][x] == 97 || maps[y][x] == 98 || maps[y][x] == 99
		|| maps[y][x] == 5 || maps[y][x] == 6
		|| maps[y][x] == 10001 || maps[y][x] == 10002 || maps[y][x] == 10003 || maps[y][x] == 10004
		|| maps[y][x] == 10005 || maps[y][x] == 10006 || maps[y][x] == 10007 || maps[y][x] == 10008
		|| maps[y][x] == 20001 || maps[y][x] == 20002 || maps[y][x] == 20003 || maps[y][x] == 20004
		|| maps[y][x] == 20005 || maps[y][x] == 20006 || maps[y][x] == 20007 || maps[y][x] == 20008
		|| maps[y][x] == 11011 || maps[y][x] == 11012 || maps[y][x] == 21011 || maps[y][x] == 21012
		|| maps[y][x] == 11013 || maps[y][x] == 11014 || maps[y][x] == 11015 || maps[y][x] == 11016
		|| maps[y][x] == 11017 || maps[y][x] == 11018 || maps[y][x] == 11019 || maps[y][x] == 11020
		|| maps[y][x] == 21013 || maps[y][x] == 21014 || maps[y][x] == 21015 || maps[y][x] == 21016
		|| maps[y][x] == 21017 || maps[y][x] == 21018 || maps[y][x] == 21019 || maps[y][x] == 21020
		|| maps[y][x] == 100001 || maps[y][x] == 200001)
	{
		return 64 - Py % 64;
	}
	return 0;
}

int MainMap::HitCheckDown(int Px, int Py) //下の当たり判定
{
	if (Py < 0)
	{
		return 0;
	}
	int x = Px / 64;
	int y = Py / 64;
	if (y >= maps.size())
		return 0;
	else if (maps[y][x] == 0 || maps[y][x] == 20 || maps[y][x] == 8
		|| maps[y][x] == 7 || maps[y][x] == 40 || maps[y][x] == 41 || maps[y][x] == 42 || maps[y][x] == 43 || maps[y][x] == 44
		|| maps[y][x] == 45 || maps[y][x] == 46 || maps[y][x] == 47 || maps[y][x] == 48 || maps[y][x] == 49
		|| maps[y][x] == 61 || maps[y][x] == 65 || maps[y][x] == 66
		|| maps[y][x] == 51 || maps[y][x] == 53 || maps[y][x] == 54 || maps[y][x] == 55
		|| maps[y][x] == 34 || maps[y][x] == 35 || maps[y][x] == 37 || maps[y][x] == 38 || maps[y][x] == 39
		|| maps[y][x] == 85 || maps[y][x] == 87 || maps[y][x] == 89
		|| maps[y][x] == 91 || maps[y][x] == 94 || maps[y][x] == 95 || maps[y][x] == 96 || maps[y][x] == 97 || maps[y][x] == 98 || maps[y][x] == 99
		|| maps[y][x] == 5 || maps[y][x] == 6
		|| maps[y][x] == 10001 || maps[y][x] == 10002 || maps[y][x] == 10003 || maps[y][x] == 10004
		|| maps[y][x] == 10005 || maps[y][x] == 10006 || maps[y][x] == 10007 || maps[y][x] == 10008
		|| maps[y][x] == 20001 || maps[y][x] == 20002 || maps[y][x] == 20003 || maps[y][x] == 20004
		|| maps[y][x] == 20005 || maps[y][x] == 20006 || maps[y][x] == 20007 || maps[y][x] == 20008
		|| maps[y][x] == 11011 || maps[y][x] == 11012 || maps[y][x] == 21011 || maps[y][x] == 21012
		|| maps[y][x] == 11013 || maps[y][x] == 11014 || maps[y][x] == 11015 || maps[y][x] == 11016
		|| maps[y][x] == 11017 || maps[y][x] == 11018 || maps[y][x] == 11019 || maps[y][x] == 11020
		|| maps[y][x] == 21013 || maps[y][x] == 21014 || maps[y][x] == 21015 || maps[y][x] == 21016
		|| maps[y][x] == 21017 || maps[y][x] == 21018 || maps[y][x] == 21019 || maps[y][x] == 21020
		|| maps[y][x] == 100001 || maps[y][x] == 200001)
	{
		return Py % 64 + 1;
	}
	return 0;
}

bool MainMap::Warp(int Px, int Py)
{

	if (Py < 0)
	{
		return 0;
	}
	int x = (Px + BgSize / 2) / 64;
	int y = (Py + (BgSize + 32) / 2) / 64;

	if (y < 0 || y >= maps.size()) return 0;
	if (x < 0 || x >= maps[y].size()) return 0;

	int tile = maps[y][x];
	if (tile >= 100 && tile < 200)
	{
		targetWarpStage = tile - 100;

		warpOutX = x * 64;
		warpOutY = y * 64;

		return true;
	}

	Fader* fader = FindGameObject<Fader>();
	Common* common = FindGameObject<Common>();
	common->SetWarpOut(-1, -1);
	//maps[y][x]においてxは+をすると左側に寄り、-をすると右側による。yは+をすると上に寄り、-をすると下に寄る
	// ==================================================
	// １階から２階への階段
	// ==================================================
	//左
	if (common->GetLagCheck())
	{
		if (maps[y][x] == 100001)
		{
			DrawString(600, 5, "２階に上がる", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 2000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(2000);//行先
				warpOutX = BgSize * 5;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//中央
		if (maps[y][x - 1] == 100001)
		{
			DrawString(600, 5, "２階に上がる", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 2000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(2000);//行先
				warpOutX = BgSize * 6;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右
		if (maps[y][x - 2] == 100001)
		{
			DrawString(600, 5, "２階に上がる", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 2000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(2000);//行先
				warpOutX = BgSize * 7;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		// ==================================================
		// 2階から１階への階段
		// ==================================================
		//左
		if (maps[y][x] == 200001)
		{
			DrawString(600, 5, "１階に下がる", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 1000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(1000);//行先
				warpOutX = BgSize * 5;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//中央
		if (maps[y][x - 1] == 200001)
		{
			DrawString(600, 5, "１階に下がる", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 1000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(1000);//行先
				warpOutX = BgSize * 6;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右
		if (maps[y][x - 2] == 200001)
		{
			DrawString(600, 5, "１階に下がる", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 1000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(1000);//行先
				warpOutX = BgSize * 7;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		// ==================================================
		// 廊下から職員室
		// ==================================================
		//左扉
		if (maps[y][x] == 1011)
		{
			DrawString(600, 700, "職員室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 1;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(1);//行先
				warpOutX = BgSize * 13;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右扉
		if (maps[y][x] == 1012)
		{
			DrawString(600, 700, "職員室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 1;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(1);//行先
				warpOutX = BgSize * 14;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		// ==================================================
		// 職員室から廊下
		// ==================================================
		//左扉
		if (maps[y][x] == 11011)
		{
			DrawString(600, 5, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 1000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(1000);//行先
				warpOutX = BgSize * 5;//X軸のワープ後の出現座標
				warpOutY = BgSize * 8;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右扉
		if (maps[y][x] == 11012)
		{
			DrawString(600, 5, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 1000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(1000);//行先
				warpOutX = BgSize * 6;//X軸のワープ後の出現座標
				warpOutY = BgSize * 8;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		// ==================================================
		// 廊下から理科室
		// ==================================================
		//左　左扉
		if (maps[y][x] == 10001)
		{
			DrawString(600, 5, "理科室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 2;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(2);//行先
				warpOutX = BgSize * 5;//X軸のワープ後の出現座標
				warpOutY = BgSize * 18;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//左　右扉
		if (maps[y][x] == 10002)
		{
			DrawString(600, 5, "理科室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 2;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(2);//行先
				warpOutX = BgSize * 6;//X軸のワープ後の出現座標
				warpOutY = BgSize * 18;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　左扉
		if (maps[y][x] == 10003)
		{
			DrawString(600, 5, "理科室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 2;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(2);//行先
				warpOutX = BgSize * 19;//X軸のワープ後の出現座標
				warpOutY = BgSize * 18;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　右扉
		if (maps[y][x] == 10004)
		{
			DrawString(600, 5, "理科室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 2;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(2);//行先
				warpOutX = BgSize * 20;//X軸のワープ後の出現座標
				warpOutY = BgSize * 18;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		// ==================================================
		// 理科室から廊下
		// ==================================================
		//左　左扉
		if (maps[y][x] == 1101)
		{
			DrawString(600, 700, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 1000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(1000);//行先
				warpOutX = BgSize * 13;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//左　右扉
		if (maps[y][x] == 1102)
		{
			DrawString(600, 700, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 1000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(1000);//行先
				warpOutX = BgSize * 14;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　左扉
		if (maps[y][x] == 1103)
		{
			DrawString(600, 700, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 1000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(1000);//行先
				warpOutX = BgSize * 25;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　右扉
		if (maps[y][x] == 1104)
		{
			DrawString(600, 700, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 1000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(1000);//行先
				warpOutX = BgSize * 26;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		// ==================================================
		// 廊下から図書室
		// ==================================================
		//左　左扉
		if (maps[y][x] == 10005)
		{
			DrawString(600, 5, "図書室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 3;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(3);//行先
				warpOutX = BgSize * 7;//X軸のワープ後の出現座標
				warpOutY = BgSize * 18;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//左　右扉
		if (maps[y][x] == 10006)
		{
			DrawString(600, 5, "図書室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 3;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(3);//行先
				warpOutX = BgSize * 8;//X軸のワープ後の出現座標
				warpOutY = BgSize * 18;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　左扉
		if (maps[y][x] == 10007)
		{
			DrawString(600, 5, "図書室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 3;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(3);//行先
				warpOutX = BgSize * 21;//X軸のワープ後の出現座標
				warpOutY = BgSize * 18;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　右扉
		if (maps[y][x] == 10008)
		{
			DrawString(600, 5, "図書室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 3;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(3);//行先
				warpOutX = BgSize * 22;//X軸のワープ後の出現座標
				warpOutY = BgSize * 18;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		// ==================================================
		// 図書室から廊下
		// ==================================================
		//左　左扉
		if (maps[y][x] == 1105)
		{
			DrawString(600, 700, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 1000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(1000);//行先
				warpOutX = BgSize * 36;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//左　右扉
		if (maps[y][x] == 1106)
		{
			DrawString(600, 700, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 1000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(1000);//行先
				warpOutX = BgSize * 37;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　左扉
		if (maps[y][x] == 1107)
		{
			DrawString(600, 700, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 1000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(1000);//行先
				warpOutX = BgSize * 48;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　右扉
		if (maps[y][x] == 1108)
		{
			DrawString(600, 700, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 1000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(1000);//行先
				warpOutX = BgSize * 49;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		// ==================================================
		// 廊下から校長室
		// ==================================================
		//左扉
		if (maps[y][x] == 2011)
		{
			DrawString(600, 700, "校長室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 4;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(4);//行先
				warpOutX = BgSize * 8;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右扉
		if (maps[y][x] == 2012)
		{
			DrawString(600, 700, "校長室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 4;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(4);//行先
				warpOutX = BgSize * 9;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		// ==================================================
		// 校長室から廊下
		// ==================================================
		//左扉
		if (maps[y][x] == 21011)
		{
			DrawString(600, 5, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 2000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(2000);//行先
				warpOutX = BgSize * 5;//X軸のワープ後の出現座標
				warpOutY = BgSize * 8;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右扉
		if (maps[y][x] == 21012)
		{
			DrawString(600, 5, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 2000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(2000);//行先
				warpOutX = BgSize * 6;//X軸のワープ後の出現座標
				warpOutY = BgSize * 8;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		// ==================================================
		// 廊下から音楽室
		// ==================================================
		//左　左扉
		if (maps[y][x] == 20001)
		{
			DrawString(600, 5, "音楽室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 5;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(5);//行先
				warpOutX = BgSize * 4;//X軸のワープ後の出現座標
				warpOutY = BgSize * 18;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//左　右扉
		if (maps[y][x] == 20002)
		{
			DrawString(600, 5, "音楽室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 5;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(5);//行先
				warpOutX = BgSize * 5;//X軸のワープ後の出現座標
				warpOutY = BgSize * 18;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　左扉
		if (maps[y][x] == 20003)
		{
			DrawString(600, 5, "音楽室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 5;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(5);//行先
				warpOutX = BgSize * 16;//X軸のワープ後の出現座標
				warpOutY = BgSize * 18;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　右扉
		if (maps[y][x] == 20004)
		{
			DrawString(600, 5, "音楽室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 5;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(5);//行先
				warpOutX = BgSize * 17;//X軸のワープ後の出現座標
				warpOutY = BgSize * 18;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		// ==================================================
		// 音楽室から廊下
		// ==================================================
		/*if (CheckHitKey(KEY_INPUT_SPACE))
		{
			switch()
		}*/
		//左　左扉
		if (maps[y][x] == 2101)
		{
			DrawString(600, 700, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 2000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(2000);//行先
				warpOutX = BgSize * 13;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//左　右扉
		if (maps[y][x] == 2102)
		{
			DrawString(600, 700, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 2000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(2000);//行先
				warpOutX = BgSize * 14;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　左扉
		if (maps[y][x] == 2103)
		{
			DrawString(600, 700, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 2000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(2000);//行先
				warpOutX = BgSize * 25;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　右扉
		if (maps[y][x] == 2104)
		{
			DrawString(600, 700, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 2000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(2000);//行先
				warpOutX = BgSize * 26;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		// ==================================================
		// 廊下から美術室
		// ==================================================
		//左　左扉
		if (maps[y][x] == 20005)
		{
			DrawString(600, 5, "美術室に入る", GetColor(255, 255, 255));


			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 6;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(6);	//行先
				warpOutX = BgSize * 6;//X軸のワープ後の出現座標
				warpOutY = BgSize * 18;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}

		}
		//左　右扉
		if (maps[y][x] == 20006)
		{
			DrawString(600, 5, "美術室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 6;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(6);	//行先
				warpOutX = BgSize * 7;//X軸のワープ後の出現座標
				warpOutY = BgSize * 18;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　左扉
		if (maps[y][x] == 20007)
		{
			DrawString(600, 5, "美術室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 6;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(6);	//行先
				warpOutX = BgSize * 18;//X軸のワープ後の出現座標
				warpOutY = BgSize * 18;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　右扉
		if (maps[y][x] == 20008)
		{
			DrawString(600, 5, "美術室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 6;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(6);	//行先
				warpOutX = BgSize * 19;//X軸のワープ後の出現座標
				warpOutY = BgSize * 18;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		// ==================================================
		// 美術室から廊下
		// ==================================================
		//左　左扉
		if (maps[y][x] == 2105)
		{
			DrawString(600, 700, "廊下に出る", GetColor(255, 255, 255));


			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 2000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(2000);//行先
				warpOutX = BgSize * 36;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//左　右扉
		if (maps[y][x] == 2106)
		{
			DrawString(600, 700, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 2000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(2000);//行先
				warpOutX = BgSize * 37;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　左扉
		if (maps[y][x] == 2107)
		{
			DrawString(600, 700, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 2000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(2000);//行先
				warpOutX = BgSize * 48;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　右扉
		if (maps[y][x] == 2108)
		{
			DrawString(600, 700, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 2000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(2000);//行先
				warpOutX = BgSize * 49;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		// ==================================================
		// 廊下から教室　１ー１
		// ==================================================
		//左　左扉
		if (maps[y][x] == 1013)
		{
			DrawString(600, 700, "教室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 101;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(101);//行先
				warpOutX = BgSize * 5;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//左　右扉
		if (maps[y][x] == 1014)
		{
			DrawString(600, 700, "教室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 101;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(101);//行先
				warpOutX = BgSize * 6;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　左扉
		if (maps[y][x] == 1015)
		{
			DrawString(600, 700, "教室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 101;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(101);//行先
				warpOutX = BgSize * 19;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　右扉
		if (maps[y][x] == 1016)
		{
			DrawString(600, 700, "教室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 101;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(101);//行先
				warpOutX = BgSize * 20;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		// ==================================================
		// 教室から廊下　１－１
		// ==================================================
		//左　左扉
		if (maps[y][x] == 11013)
		{
			DrawString(600, 5, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 1000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(1000);//行先
				warpOutX = BgSize * 16;//X軸のワープ後の出現座標
				warpOutY = BgSize * 8;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//左　右扉
		if (maps[y][x] == 11014)
		{
			DrawString(600, 5, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 1000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(1000);//行先
				warpOutX = BgSize * 17;//X軸のワープ後の出現座標
				warpOutY = BgSize * 8;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　左扉
		if (maps[y][x] == 11015)
		{
			DrawString(600, 5, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 1000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(1000);//行先
				warpOutX = BgSize * 28;//X軸のワープ後の出現座標
				warpOutY = BgSize * 8;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　右扉
		if (maps[y][x] == 11016)
		{
			DrawString(600, 5, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 1000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(1000);//行先
				warpOutX = BgSize * 29;//X軸のワープ後の出現座標
				warpOutY = BgSize * 8;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		// ==================================================
		// 廊下から教室　１ー２
		// ==================================================
		//左　左扉
		if (maps[y][x] == 1017)
		{
			DrawString(600, 700, "教室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 102;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(102);//行先
				warpOutX = BgSize * 5;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//左　右扉
		if (maps[y][x] == 1018)
		{
			DrawString(600, 700, "教室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 102;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(102);//行先
				warpOutX = BgSize * 6;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　左扉
		if (maps[y][x] == 1019)
		{
			DrawString(600, 700, "教室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 102;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(102);//行先
				warpOutX = BgSize * 19;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　右扉
		if (maps[y][x] == 1020)
		{
			DrawString(600, 700, "教室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 102;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(102);//行先
				warpOutX = BgSize * 20;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		// ==================================================
		// 教室から廊下　１－２
		// ==================================================
		//左　左扉
		if (maps[y][x] == 11017)
		{
			DrawString(600, 5, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 1000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(1000);//行先
				warpOutX = BgSize * 40;//X軸のワープ後の出現座標
				warpOutY = BgSize * 8;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//左　右扉
		if (maps[y][x] == 11018)
		{
			DrawString(600, 5, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 1000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(1000);//行先
				warpOutX = BgSize * 41;//X軸のワープ後の出現座標
				warpOutY = BgSize * 8;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　左扉
		if (maps[y][x] == 11019)
		{
			DrawString(600, 5, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 1000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(1000);//行先
				warpOutX = BgSize * 52;//X軸のワープ後の出現座標
				warpOutY = BgSize * 8;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　右扉
		if (maps[y][x] == 11020)
		{
			DrawString(600, 5, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 1000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(1000);//行先
				warpOutX = BgSize * 53;//X軸のワープ後の出現座標
				warpOutY = BgSize * 8;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		// ==================================================
		// 廊下から教室　２ー１
		// ==================================================
		//左　左扉
		if (maps[y][x] == 2013)
		{
			DrawString(600, 700, "教室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 201;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(201);//行先
				warpOutX = BgSize * 5;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//左　右扉
		if (maps[y][x] == 2014)
		{
			DrawString(600, 700, "教室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 201;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(201);//行先
				warpOutX = BgSize * 6;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　左扉
		if (maps[y][x] == 2015)
		{
			DrawString(600, 700, "教室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 201;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(201);//行先
				warpOutX = BgSize * 19;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　右扉
		if (maps[y][x] == 2016)
		{
			DrawString(600, 700, "教室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 201;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(201);//行先
				warpOutX = BgSize * 20;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		// ==================================================
		// 教室から廊下　２－１
		// ==================================================
		//左　左扉
		if (maps[y][x] == 21013)
		{
			DrawString(600, 5, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 2000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(2000);//行先
				warpOutX = BgSize * 16;//X軸のワープ後の出現座標
				warpOutY = BgSize * 8;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//左　右扉
		if (maps[y][x] == 21014)
		{
			DrawString(600, 5, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 2000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(2000);//行先
				warpOutX = BgSize * 17;//X軸のワープ後の出現座標
				warpOutY = BgSize * 8;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　左扉
		if (maps[y][x] == 21015)
		{
			DrawString(600, 5, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 2000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(2000);//行先
				warpOutX = BgSize * 28;//X軸のワープ後の出現座標
				warpOutY = BgSize * 8;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　右扉
		if (maps[y][x] == 21016)
		{
			DrawString(600, 5, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 2000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(2000);//行先
				warpOutX = BgSize * 29;//X軸のワープ後の出現座標
				warpOutY = BgSize * 8;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		// ==================================================
		// 廊下から教室　２ー２
		// ==================================================
		//左　左扉
		if (maps[y][x] == 2017)
		{
			DrawString(600, 700, "教室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 202;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(202);//行先
				warpOutX = BgSize * 5;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//左　右扉
		if (maps[y][x] == 2018)
		{
			DrawString(600, 700, "教室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 202;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(202);//行先
				warpOutX = BgSize * 6;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　左扉
		if (maps[y][x] == 2019)
		{
			DrawString(600, 700, "教室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 202;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(202);//行先
				warpOutX = BgSize * 19;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　右扉
		if (maps[y][x] == 2020)
		{
			DrawString(600, 700, "教室に入る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 202;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(202);//行先
				warpOutX = BgSize * 20;//X軸のワープ後の出現座標
				warpOutY = BgSize * 3 + 16;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		// ==================================================
		// 教室から廊下　２－２
		// ==================================================
		//左　左扉
		if (maps[y][x] == 21017)
		{
			DrawString(600, 5, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 2000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(2000);//行先
				warpOutX = BgSize * 40;//X軸のワープ後の出現座標
				warpOutY = BgSize * 8;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//左　右扉
		if (maps[y][x] == 21018)
		{
			DrawString(600, 5, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 2000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(2000);//行先
				warpOutX = BgSize * 41;//X軸のワープ後の出現座標
				warpOutY = BgSize * 8;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　左扉
		if (maps[y][x] == 21019)
		{
			DrawString(600, 5, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 2000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(2000);//行先
				warpOutX = BgSize * 52;//X軸のワープ後の出現座標
				warpOutY = BgSize * 8;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		//右　右扉
		if (maps[y][x] == 21020)
		{
			DrawString(600, 5, "廊下に出る", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				fader->FadeIn(inTime);
				targetWarpStage = 2000;//行先
				FloorMap* floor = ObjectManager::FindGameObject<FloorMap>();
				floor->SetTargerWarpFloor(2000);//行先
				warpOutX = BgSize * 53;//X軸のワープ後の出現座標
				warpOutY = BgSize * 8;//Y軸のワープ後の出現座標
				Enemy::killAll();
				common->SetLagIn_W();
				common->SetWarpOut(warpOutX, warpOutY);
				return true;
			}
		}
		return false;
	}


}
	