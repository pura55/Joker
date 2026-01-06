#include "TextBox.h"
#include "Player.h"
#include <assert.h>


TextBox::TextBox()
{
	SetDrawOrder(-5000);
	BoxImage = LoadGraph("Data/image/TextBox.png");
	assert(BoxImage > 0);

	TextJudge = true;
	MainState = TextBox_State::STATE_END;
	time = 0.0f;
}

TextBox::~TextBox()
{

}

void TextBox::Update()
{
	Player* player = FindGameObject<Player>();
	if (MainState != TextBox_State::STATE_END)//tureとfalseの衝突を防ぐ
	{
		player->SetPlay(false);//プレイヤーの動きを止める
	}


	if (!TextJudge)
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

	switch (MainState)
	{
	case TextBox_State::STATE_JAPANESE://国語
		if (TextJudge)
		{
			if (CheckHitKey(KEY_INPUT_1))
			{
				QuestionJapanese();
				TextJudge = false;
			}
			else if (CheckHitKey(KEY_INPUT_2))
			{
				MainState = TextBox_State::STATE_END;
			}
		}
		break;
	case TextBox_State::STATE_MATH://算数
		if (TextJudge)
		{
			if (CheckHitKey(KEY_INPUT_1))
			{
				QuestionMathematics();
				TextJudge = false;
			}
			else if (CheckHitKey(KEY_INPUT_2))
			{
				MainState = TextBox_State::STATE_END;
			}
		}
		break;
	case TextBox_State::STATE_SCIENCE://理科
		if (TextJudge)
		{
			if (CheckHitKey(KEY_INPUT_1))
			{
				QuestionScience();
				TextJudge = false;
			}
			else if (CheckHitKey(KEY_INPUT_2))
			{
				MainState = TextBox_State::STATE_END;
			}
		}
		break;
	case TextBox_State::STATE_SOCIETY://社会
		if (TextJudge)
		{
			if (CheckHitKey(KEY_INPUT_1))
			{
				QuestionSociety();
				TextJudge = false;
			}
			else if (CheckHitKey(KEY_INPUT_2))
			{
				MainState = TextBox_State::STATE_END;
				TextJudge = false;
			}
		}
		break;
	case TextBox_State::STATE_EXTRA://特別問題
		if (TextJudge)
		{
			if (CheckHitKey(KEY_INPUT_1))
			{
				QuestionExtra();
				TextJudge = false;
			}
			else if (CheckHitKey(KEY_INPUT_2))
			{
				MainState = TextBox_State::STATE_END;
				TextJudge = false;
			}
		}
		break;
	case TextBox_State::STATE_DICIDE://yes,no
		if (TextJudge)
		{
			if (CheckHitKey(KEY_INPUT_1))
			{
				switch (Q_AND_A)
				{
				case TextBox_State::STATE_JAPANESE:
					MainState = TextBox_State::STATE_JAPANESE;
					TextJudge = false;
					break;
				case TextBox_State::STATE_MATH:
					MainState = TextBox_State::STATE_MATH;
					TextJudge = false;
					break;
				case TextBox_State::STATE_SCIENCE:
					MainState = TextBox_State::STATE_SCIENCE;
					TextJudge = false;
					break;
				case TextBox_State::STATE_SOCIETY:
					MainState = TextBox_State::STATE_SOCIETY;
					TextJudge = false;
					break;
				case TextBox_State::STATE_EXTRA:
					MainState = TextBox_State::STATE_EXTRA;
					TextJudge = false;
					break;
				}
			}
			else if (CheckHitKey(KEY_INPUT_2))
			{
				MainState = TextBox_State::STATE_END;
				TextJudge = false;
			}
		}
		break;
	case TextBox_State::STATE_JP_HINT://国語のヒント
		if (TextJudge)
		{
			if (CheckHitKey(KEY_INPUT_F))
			{
				MainState = TextBox_State::STATE_END;
				TextJudge = false;
			}
		}
		break;
	case TextBox_State::STATE_MT_HINT://算数のヒントif (TextJudge)
	{
		if (CheckHitKey(KEY_INPUT_F))
		{
			MainState = TextBox_State::STATE_END;
			TextJudge = false;
		}
	}
	break;

	case TextBox_State::STATE_SCI_HINT://理科のヒント
		if (TextJudge)
		{
			if (CheckHitKey(KEY_INPUT_F))
			{
				MainState = TextBox_State::STATE_END;
				TextJudge = false;
			}
		}
		break;
	case TextBox_State::STATE_SOC_HINT://社会のヒント
		if (TextJudge)
		{
			if (CheckHitKey(KEY_INPUT_F))
			{
				MainState = TextBox_State::STATE_END;
				TextJudge = false;
			}
		}
		break;
	case TextBox_State::STATE_BLANK://何もなかった
		if (TextJudge)
		{
			if (CheckHitKey(KEY_INPUT_F))
			{
				MainState = TextBox_State::STATE_END;
				TextJudge = false;
			}
		}
		break;
	case TextBox_State::STATE_TRUE://正解
		if (TextJudge)
		{
			if (CheckHitKey(KEY_INPUT_F))
			{
				MainState = TextBox_State::STATE_END;
				TextJudge = false;
			}
		}
		break;
	case TextBox_State::STATE_FALSE://不正解
		if (TextJudge)
		{
			if (CheckHitKey(KEY_INPUT_F))
			{
				MainState = TextBox_State::STATE_END;
				TextJudge = false;
				/*GameManager* GM = FindGameObject<GameManager>();
				GM->SetGameOver();*/
			}
		}
		break;
	case TextBox_State::STATE_END://STATE終了
		player->SetPlay(true);
		break;
	}
}

void TextBox::Draw()
{
	//問題の出力判定
	switch (MainState)
	{
	case TextBox_State::STATE_JAPANESE://国語
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(500, 570, "この中で芥川龍之介が描いた本は？", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 1, "１．人間失格", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 2, "２．こころ", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 3, "３．羅生門", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 4, "４．雨にも負けず", GetColor(255, 255, 255), 1);

		break;
	case TextBox_State::STATE_MATH://算数
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(500, 570, "３＊４ー２＝？", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 1, "１．６", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 2, "２．１０", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 3, "３．１４", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 4, "４．５", GetColor(255, 255, 255), 1);

		break;
	case TextBox_State::STATE_SCIENCE://理科
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(500, 570, "火が燃えるのに必要な物質は？", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 1, "１．二酸化炭素", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 2, "２．水素", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 3, "３．酸素", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 4, "４．炭素", GetColor(255, 255, 255), 1);

		break;
	case TextBox_State::STATE_SOCIETY://社会
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(500, 570, "邪馬台国を治めた人物は？", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 1, "１．聖徳太子", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 2, "２．紫式部", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 3, "３．両面宿儺", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 4, "４．卑弥呼", GetColor(255, 255, 255), 1);

		break;
	case TextBox_State::STATE_EXTRA://特別問題
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(500, 570, "校長先生の好物は？", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 1, "１．ちくわ", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 2, "２．ユッケ", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 3, "３．ナポリタン", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 4, "４．赤飯", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_DICIDE://はい・いいえ
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(550, 570, "問題に挑戦しますか？", GetColor(255, 255, 255), 1);
		DrawString(600, 570 + 16 * 1, "１．はい", GetColor(255, 255, 255), 1);
		DrawString(600, 570 + 16 * 2, "２．いいえ", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_JP_HINT://国語のヒント
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(490, HintX, "「芥川龍之介　代表作：羅生門・鼻1」", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_MT_HINT://算数のヒント
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(430, HintX, "「掛け算と割り算は足し算引き算よりも先に計算しよう！」", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_SCI_HINT://理科のヒント
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(450, HintX, "「火が燃えるには酸素が必要不可欠！覚えておこう！」", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_SOC_HINT://社会のヒント
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(480, HintX, "「邪馬台国を治めた倭国の女王「卑弥呼」」", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_BLANK://何もないとき
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(500, 570, "何もなかった...", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_TRUE://正解
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(500, 570, "正解！", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_FALSE://不正解
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(500, 570, "不正解...", GetColor(255, 255, 255), 1);
		break;
	}
}

void TextBox::QuestionJapanese()
{
	if (TextJudge)
	{
		if (CheckHitKey(KEY_INPUT_1))//不正解
		{
			MainState = TextBox_State::STATE_FALSE;
			TextJudge = false;
		}
		if (CheckHitKey(KEY_INPUT_2))//不正解
		{
			MainState = TextBox_State::STATE_FALSE;
			TextJudge = false;
		}
		if (CheckHitKey(KEY_INPUT_3))//正解
		{
			MainState = TextBox_State::STATE_TRUE;
			TextJudge = false;
		}
		if (CheckHitKey(KEY_INPUT_4))//不正解
		{
			MainState = TextBox_State::STATE_FALSE;
			TextJudge = false;
		}
	}
}

void TextBox::QuestionMathematics()
{
	if (TextJudge)
	{
		if (CheckHitKey(KEY_INPUT_1))//不正解
		{
			MainState = TextBox_State::STATE_FALSE;
			TextJudge = false;
		}
		if (CheckHitKey(KEY_INPUT_2))//正解
		{
			MainState = TextBox_State::STATE_TRUE;
			TextJudge = false;
		}
		if (CheckHitKey(KEY_INPUT_3))//不正解
		{
			MainState = TextBox_State::STATE_FALSE;
			TextJudge = false;
		}
		if (CheckHitKey(KEY_INPUT_4))//不正解
		{
			MainState = TextBox_State::STATE_FALSE;
			TextJudge = false;
		}
	}
}

void TextBox::QuestionScience()
{
	if (TextJudge)
	{
		if (CheckHitKey(KEY_INPUT_1))//不正解
		{
			MainState = TextBox_State::STATE_FALSE;
			TextJudge = false;
		}
		if (CheckHitKey(KEY_INPUT_2))//不正解
		{
			MainState = TextBox_State::STATE_FALSE;
			TextJudge = false;
		}
		if (CheckHitKey(KEY_INPUT_3))//正解
		{
			MainState = TextBox_State::STATE_TRUE;
			TextJudge = false;
		}
		if (CheckHitKey(KEY_INPUT_4))//不正解
		{
			MainState = TextBox_State::STATE_FALSE;
			TextJudge = false;
		}
	}
}

void TextBox::QuestionSociety()
{
	if (TextJudge)
	{
		if (CheckHitKey(KEY_INPUT_1))//不正解
		{
			MainState = TextBox_State::STATE_FALSE;
			TextJudge = false;
		}
		if (CheckHitKey(KEY_INPUT_2))//不正解
		{
			MainState = TextBox_State::STATE_FALSE;
			TextJudge = false;
		}
		if (CheckHitKey(KEY_INPUT_3))//不正解
		{
			MainState = TextBox_State::STATE_FALSE;
			TextJudge = false;
		}
		if (CheckHitKey(KEY_INPUT_4))//正解
		{
			MainState = TextBox_State::STATE_TRUE;
			TextJudge = false;
		}
	}
}

void TextBox::QuestionExtra()
{
	if (TextJudge)
	{
		if (CheckHitKey(KEY_INPUT_1))//不正解
		{
			MainState = TextBox_State::STATE_FALSE;
			TextJudge = false;
		}
		if (CheckHitKey(KEY_INPUT_2))//不正解
		{
			MainState = TextBox_State::STATE_FALSE;
			TextJudge = false;
		}
		if (CheckHitKey(KEY_INPUT_3))//正解
		{
			MainState = TextBox_State::STATE_TRUE;
			TextJudge = false;
		}
		if (CheckHitKey(KEY_INPUT_4))//不正解
		{
			MainState = TextBox_State::STATE_FALSE;
			TextJudge = false;
		}
	}
}


