#include "TextBox.h"
#include "Player.h"
#include <assert.h>


TextBox::TextBox()
{
	BoxImage = LoadGraph("Data/image/TextBox.png");
	assert(BoxImage > 0);
	
	TextJudge = true;;
	QuestionCount = 0;
	time = 0.0f;
}

TextBox::~TextBox()
{
	
}

void TextBox::Update()
{
	Player* player = FindGameObject<Player>();
	player->SetPlay(false);

	if (TextJudge)
	{
		
			if (CheckHitKey(KEY_INPUT_N))
			{
				QuestionCount += 1;
				TextJudge = false;
			}

	}
	else
	{
		time += Time::DeltaTime();
		if (time >= 1.0f)
		{
			TextJudge = true;
		}

	}

	if (TextJudge)
	{
		if (QuestionCount == 5)
		{
			if(CheckHitKey(KEY_INPUT_F))
			{

				TextJudge = false;
			}
		}
		
	}
	else
	{
		time += Time::DeltaTime();
		if (time >= 1.0f)
		{
			TextJudge = true;
		}
		
	}

	if (time > 1.0f)
	{
		time = 0.0f;
	}
	
	switch (QuestionCount)
	{
	case 1://国語
		QuestionJapanese();
		break;
	case 2://算数
		QuestionMathematics();
		break;
	case 3://理科
		QuestionScience();
		break;
	case 4://社会
		QuestionSociety();
		break;
	case 5://特別問題
		QuestionExtra();
		break;
	case 6://正解

		break;
	case 7://不正解

		break;
	case 8:
		player->SetPlay(true);
		DestroyMe();
	}

}

void TextBox::Draw()
{

	int BoxPosX = 350;
	int BoxPosY = 500;

	//問題の出力判定
	switch (QuestionCount)
	{
	case 1://国語
		    DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
			DrawString(500, 570, "この中で芥川龍之介が描いた本は？", GetColor(255, 255, 255), 1);
			DrawString(550, 570 + 16 * 1, "１．人間失格", GetColor(255, 255, 255), 1);
			DrawString(550, 570 + 16 * 2, "２．こころ", GetColor(255, 255, 255), 1);
			DrawString(550, 570 + 16 * 3, "３．羅生門", GetColor(255, 255, 255), 1);
			DrawString(550, 570 + 16 * 4, "４．雨にも負けず", GetColor(255, 255, 255), 1);
			break;
	case 2://算数
		    DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
			DrawString(500, 570, "３＊４ー２＝？", GetColor(255, 255, 255), 1);
			DrawString(550, 570 + 16 * 1, "１．６", GetColor(255, 255, 255), 1);
			DrawString(550, 570 + 16 * 2, "２．１０", GetColor(255, 255, 255), 1);
			DrawString(550, 570 + 16 * 3, "３．１４", GetColor(255, 255, 255), 1);
			DrawString(550, 570 + 16 * 4, "４．５", GetColor(255, 255, 255), 1);
			break;
	case 3://理科
		    DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
			DrawString(500, 570, "火が燃えるのに必要な物質は？", GetColor(255, 255, 255), 1);
			DrawString(550, 570 + 16 * 1, "１．二酸化炭素", GetColor(255, 255, 255), 1);
			DrawString(550, 570 + 16 * 2, "２．水素", GetColor(255, 255, 255), 1);
			DrawString(550, 570 + 16 * 3, "３．酸素", GetColor(255, 255, 255), 1);
			DrawString(550, 570 + 16 * 4, "４．炭素", GetColor(255, 255, 255), 1);
			break;
	case 4://社会
		    DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
			DrawString(500, 570, "邪馬台国を治めた人物は？", GetColor(255, 255, 255), 1);
			DrawString(550, 570 + 16 * 1, "１．聖徳太子", GetColor(255, 255, 255), 1);
			DrawString(550, 570 + 16 * 2, "２．紫式部", GetColor(255, 255, 255), 1);
			DrawString(550, 570 + 16 * 3, "３．両面宿儺", GetColor(255, 255, 255), 1);
			DrawString(550, 570 + 16 * 4, "４．卑弥呼", GetColor(255, 255, 255), 1);
		    break;
	case 5://社会
		    DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		    DrawString(500, 570, "校長先生の好物は？", GetColor(255, 255, 255), 1);
		    DrawString(550, 570 + 16 * 1, "１．ちくわ", GetColor(255, 255, 255), 1);
		    DrawString(550, 570 + 16 * 2, "２．ユッケ", GetColor(255, 255, 255), 1);
		    DrawString(550, 570 + 16 * 3, "３．ナポリタン", GetColor(255, 255, 255), 1);
		    DrawString(550, 570 + 16 * 4, "４．赤飯", GetColor(255, 255, 255), 1);
		    break;
	case 6://正解
		    DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
			DrawString(500, 570, "正解！", GetColor(255, 255, 255), 1);
		break;
	case 7://不正解
		    DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		    DrawString(500, 570, "不正解...", GetColor(255, 255, 255), 1);
		break;
	}
	
}

void TextBox::QuestionJapanese()
{
	if (CheckHitKey(KEY_INPUT_1))//不正解
	{
		QuestionCount = 7;
	}
	if (CheckHitKey(KEY_INPUT_2))//不正解
	{
		QuestionCount = 7;
	}
	if (CheckHitKey(KEY_INPUT_3))//正解
	{
		QuestionCount = 6;
	}
	if (CheckHitKey(KEY_INPUT_4))//不正解
	{
		QuestionCount = 7;
	}
}

void TextBox::QuestionMathematics()
{
	if (CheckHitKey(KEY_INPUT_1))//不正解
	{
		QuestionCount = 7;
	}
	if (CheckHitKey(KEY_INPUT_2))//正解
	{
		QuestionCount = 6;
	}
	if (CheckHitKey(KEY_INPUT_3))//不正解
	{
		QuestionCount = 7;
	}
	if (CheckHitKey(KEY_INPUT_4))//不正解
	{
		QuestionCount = 7;
	}
}

void TextBox::QuestionScience()
{
	if (CheckHitKey(KEY_INPUT_1))//不正解
	{
		QuestionCount = 7;
	}
	if (CheckHitKey(KEY_INPUT_2))//不正解
	{
		QuestionCount = 7;
	}
	if (CheckHitKey(KEY_INPUT_3))//正解
	{
		QuestionCount = 6;
	}
	if (CheckHitKey(KEY_INPUT_4))//不正解
	{
		QuestionCount = 7;
	}
}

void TextBox::QuestionSociety()
{
	if (CheckHitKey(KEY_INPUT_1))//不正解
	{
		QuestionCount = 7;
	}
	if (CheckHitKey(KEY_INPUT_2))//不正解
	{
		QuestionCount = 7;
	}
	if (CheckHitKey(KEY_INPUT_3))//不正解
	{
		QuestionCount = 7;
	}
	if (CheckHitKey(KEY_INPUT_4))//正解
	{
		QuestionCount = 6;
	}
}

void TextBox::QuestionExtra()
{
	if (CheckHitKey(KEY_INPUT_1))//不正解
	{
		QuestionCount = 7;
	}
	if (CheckHitKey(KEY_INPUT_2))//不正解
	{
		QuestionCount = 7;
	}
	if (CheckHitKey(KEY_INPUT_3))//正解
	{
		QuestionCount = 6;
	}
	if (CheckHitKey(KEY_INPUT_4))//不正解
	{
		QuestionCount = 7;
	}
}
