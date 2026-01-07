#include "TextBox.h"
#include "Player.h"
#include <assert.h>


TextBox::TextBox()
{
	SetDrawOrder(-5000);
	//‰æ‘œ“Ç‚İ‚İ
	BoxImage = LoadGraph("Data/image/TextBox.png");
	assert(BoxImage > 0);

	//•Ï”‰Šú‰»
	MainState = TextBox_State::STATE_END;
	jpKey = false;
	mtKey = false;
	sciKey = false;
	socKey = false;

	//FindGameObject
	common = FindGameObject<Common>();
	
}

TextBox::~TextBox()
{

}

void TextBox::Update()
{
	Player* player = FindGameObject<Player>();
	//mainState‚ªENDˆÈŠO‚¾‚Á‚½‚çƒvƒŒƒCƒ„[‚Ì“®‚«‚ğ~‚ß‚é
	if (MainState != TextBox_State::STATE_END)//true‚Æfalse‚ÌÕ“Ë‚ğ–h‚®
	{
		player->SetPlay(false);//ƒvƒŒƒCƒ„[‚Ì“®‚«‚ğ~‚ß‚é
	}

	Common* common = FindGameObject<Common>();
	//ƒƒCƒ“‚Ìó‘Ô
	switch (MainState)
	{
	case TextBox_State::STATE_JAPANESE://‘Œê
		if (common->GetLagCheck())
		{
			QuestionJapanese();
		}
		break;
	case TextBox_State::STATE_MATH://Z”
		if (common->GetLagCheck())
		{
			QuestionMathematics();
		}
		break;
	case TextBox_State::STATE_SCIENCE://—‰È
		if (common->GetLagCheck())
		{
			QuestionScience();
		}
		break;
	case TextBox_State::STATE_SOCIETY://Ğ‰ï
		if (common->GetLagCheck())
		{
			QuestionSociety();
		}
		break;
	case TextBox_State::STATE_EXTRA://“Á•Ê–â‘è
		if (common->GetLagCheck())
		{
			QuestionExtra();
		}
		break;
	case TextBox_State::STATE_DICIDE://yes,no
		if (common->GetLagCheck())
		{
			if (CheckHitKey(KEY_INPUT_1))
			{
				switch (Q_AND_A)
				{
				case TextBox_State::STATE_JAPANESE:
					MainState = TextBox_State::STATE_JAPANESE;
					common->SetLagIn_T();
					break;
				case TextBox_State::STATE_MATH:
					MainState = TextBox_State::STATE_MATH;
					common->SetLagIn_T();
					break;
				case TextBox_State::STATE_SCIENCE:
					MainState = TextBox_State::STATE_SCIENCE;
					common->SetLagIn_T();
					break;
				case TextBox_State::STATE_SOCIETY:
					MainState = TextBox_State::STATE_SOCIETY;
					common->SetLagIn_T();
					break;
				case TextBox_State::STATE_EXTRA:
					MainState = TextBox_State::STATE_EXTRA;
					common->SetLagIn_T();
					break;
				}
			}
			else if (CheckHitKey(KEY_INPUT_2))
			{
				MainState = TextBox_State::STATE_END;
				common->SetLagIn_T();
			}
		}
		break;
	case TextBox_State::STATE_JP_HINT://‘Œê‚Ìƒqƒ“ƒg
		if (common->GetLagCheck())
		{
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				MainState = TextBox_State::STATE_END;
				common->SetLagIn_T();
			}
		}
		break;
	case TextBox_State::STATE_MT_HINT://Z”‚Ìƒqƒ“ƒg
		if (common->GetLagCheck())
		{
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				MainState = TextBox_State::STATE_END;
				common->SetLagIn_T();
			}
		}
		break;

	case TextBox_State::STATE_SCI_HINT://—‰È‚Ìƒqƒ“ƒg
		if (common->GetLagCheck())
		{
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				MainState = TextBox_State::STATE_END;
				common->SetLagIn_T();
			}
		}
		break;
	case TextBox_State::STATE_SOC_HINT://Ğ‰ï‚Ìƒqƒ“ƒg
		if (common->GetLagCheck())
		{
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				MainState = TextBox_State::STATE_END;
				common->SetLagIn_T();
			}
		}
		break;
	case TextBox_State::STATE_BLANK://‰½‚à‚È‚©‚Á‚½
		if (common->GetLagCheck())
		{
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				MainState = TextBox_State::STATE_END;
				common->SetLagIn_T();
			}
		}
		break;
	case TextBox_State::STATE_TRUE://³‰ğ
		if (common->GetLagCheck())
		{
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				MainState = TextBox_State::STATE_END;
				common->SetLagIn_T();
			}
		}
		break;
	case TextBox_State::STATE_FALSE://•s³‰ğ
		if (common->GetLagCheck())
		{
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				MainState = TextBox_State::STATE_END;
				common->SetLagIn_T();
				/*GameManager* GM = FindGameObject<GameManager>();
				GM->SetGameOver();*/
			}
		}
		break;
	case TextBox_State::STATE_END://STATEI—¹
		player->SetPlay(true);
		break;
	}

}

void TextBox::Draw()
{
	//–â‘è‚Ìo—Í”»’è
	switch (MainState)
	{
	case TextBox_State::STATE_JAPANESE://‘Œê
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(500, 570, "‚±‚Ì’†‚ÅŠHì—´”V‰î‚ª•`‚¢‚½–{‚ÍH", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 1, "‚PDlŠÔ¸Ši", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 2, "‚QD‚±‚±‚ë", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 3, "‚RD—…¶–å", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 4, "‚SD‰J‚É‚à•‰‚¯‚¸", GetColor(255, 255, 255), 1);

		break;
	case TextBox_State::STATE_MATH://Z”
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(500, 570, "‚R–‚S[‚QH", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 1, "‚PD‚U", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 2, "‚QD‚P‚O", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 3, "‚RD‚P‚S", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 4, "‚SD‚T", GetColor(255, 255, 255), 1);

		break;
	case TextBox_State::STATE_SCIENCE://—‰È
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(500, 570, "‰Î‚ª”R‚¦‚é‚Ì‚É•K—v‚È•¨¿‚ÍH", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 1, "‚PD“ñ_‰»’Y‘f", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 2, "‚QD…‘f", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 3, "‚RD_‘f", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 4, "‚SD’Y‘f", GetColor(255, 255, 255), 1);

		break;
	case TextBox_State::STATE_SOCIETY://Ğ‰ï
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(500, 570, "×”n‘ä‘‚ğ¡‚ß‚½l•¨‚ÍH", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 1, "‚PD¹“¿‘¾q", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 2, "‚QD‡®•”", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 3, "‚RD—¼–Êh™T", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 4, "‚SD”Ú–íŒÄ", GetColor(255, 255, 255), 1);

		break;
	case TextBox_State::STATE_EXTRA://“Á•Ê–â‘è
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(500, 570, "Z’·æ¶‚ÌD•¨‚ÍH", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 1, "‚PD‚¿‚­‚í", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 2, "‚QDƒ†ƒbƒP", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 3, "‚RDƒiƒ|ƒŠƒ^ƒ“", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 4, "‚SDÔ”Ñ", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_DICIDE://‚Í‚¢E‚¢‚¢‚¦
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(550, 570, "–â‘è‚É’§í‚µ‚Ü‚·‚©H", GetColor(255, 255, 255), 1);
		DrawString(600, 570 + 16 * 1, "‚PD‚Í‚¢", GetColor(255, 255, 255), 1);
		DrawString(600, 570 + 16 * 2, "‚QD‚¢‚¢‚¦", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_JP_HINT://‘Œê‚Ìƒqƒ“ƒg
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(490, HintX, "uŠHì—´”V‰î@‘ã•\ìF—…¶–åE•@1v", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_MT_HINT://Z”‚Ìƒqƒ“ƒg
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(430, HintX, "uŠ|‚¯Z‚ÆŠ„‚èZ‚Í‘«‚µZˆø‚«Z‚æ‚è‚àæ‚ÉŒvZ‚µ‚æ‚¤Iv", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_SCI_HINT://—‰È‚Ìƒqƒ“ƒg
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(450, HintX, "u‰Î‚ª”R‚¦‚é‚É‚Í_‘f‚ª•K—v•s‰ÂŒ‡IŠo‚¦‚Ä‚¨‚±‚¤Iv", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_SOC_HINT://Ğ‰ï‚Ìƒqƒ“ƒg
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(480, HintX, "u×”n‘ä‘‚ğ¡‚ß‚½˜`‘‚Ì—‰¤u”Ú–íŒÄvv", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_BLANK://‰½‚à‚È‚¢‚Æ‚«
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(500, 570, "‰½‚à‚È‚©‚Á‚½...", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_TRUE://³‰ğ
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(500, 570, "³‰ğI", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_FALSE://•s³‰ğ
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(500, 570, "•s³‰ğ...", GetColor(255, 255, 255), 1);
		break;
	}
}

void TextBox::QuestionJapanese()
{
	if (common->GetLagCheck())
	{
		if (CheckHitKey(KEY_INPUT_1))//•s³‰ğ
		{
			MainState = TextBox_State::STATE_FALSE;
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_2))//•s³‰ğ
		{
			MainState = TextBox_State::STATE_FALSE;
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_3))//³‰ğ
		{
			jpKey = true;
			MainState = TextBox_State::STATE_TRUE;
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_4))//•s³‰ğ
		{
			MainState = TextBox_State::STATE_FALSE;
			common->SetLagIn_T();
		}
	}
}

void TextBox::QuestionMathematics()
{
	if (common->GetLagCheck())
	{
		if (CheckHitKey(KEY_INPUT_1))//•s³‰ğ
		{
			MainState = TextBox_State::STATE_FALSE;
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_2))//³‰ğ
		{
			mtKey = true;
			MainState = TextBox_State::STATE_TRUE;
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_3))//•s³‰ğ
		{
			MainState = TextBox_State::STATE_FALSE;
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_4))//•s³‰ğ
		{
			MainState = TextBox_State::STATE_FALSE;
			common->SetLagIn_T();
		}
	}
}

void TextBox::QuestionScience()
{
	if (common->GetLagCheck())
	{
		if (CheckHitKey(KEY_INPUT_1))//•s³‰ğ
		{
			MainState = TextBox_State::STATE_FALSE;
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_2))//•s³‰ğ
		{
			MainState = TextBox_State::STATE_FALSE;
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_3))//³‰ğ
		{
			sciKey = true;
			MainState = TextBox_State::STATE_TRUE;
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_4))//•s³‰ğ
		{
			MainState = TextBox_State::STATE_FALSE;
			common->SetLagIn_T();
		}
	}
}

void TextBox::QuestionSociety()
{
	if (common->GetLagCheck())
	{
		if (CheckHitKey(KEY_INPUT_1))//•s³‰ğ
		{
			MainState = TextBox_State::STATE_FALSE;
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_2))//•s³‰ğ
		{
			MainState = TextBox_State::STATE_FALSE;
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_3))//•s³‰ğ
		{
			MainState = TextBox_State::STATE_FALSE;
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_4))//³‰ğ
		{
			socKey = true;
			MainState = TextBox_State::STATE_TRUE;
			common->SetLagIn_T();
		}
	}
}

void TextBox::QuestionExtra()
{
	if (common->GetLagCheck())
	{
		if (CheckHitKey(KEY_INPUT_1))//•s³‰ğ
		{
			MainState = TextBox_State::STATE_FALSE;
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_2))//•s³‰ğ
		{
			MainState = TextBox_State::STATE_FALSE;
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_3))//³‰ğ
		{
			MainState = TextBox_State::STATE_TRUE;
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_4))//•s³‰ğ
		{
			MainState = TextBox_State::STATE_FALSE;
			common->SetLagIn_T();
		}
	}
}


