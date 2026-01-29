#include "TextBox.h"
#include "Player.h"
#include "GameManager.h"
#include "Fader.h"
#include "Enemy.h"
#include "Common.h"
#include <assert.h>
#include <vector>



TextBox::TextBox()
{
	SetDrawOrder(-1000);
	//画像読み込み
	BoxImage = LoadGraph("Data/image/TextBox.png");
	assert(BoxImage > 0);

	//変数初期化
	MainState = TextBox_State::STATE_PRO;
	TalkState = TextBox_State::STATE_STRING_1;
	proEnd = false;
	False = false;

	//FindGameObject
	common = FindGameObject<Common>();
	keyManager = FindGameObject<KeyManager>();

	SetFontSize(16);
	
}

TextBox::~TextBox()
{
	//画像・音声素材のdelete
	DeleteGraph(BoxImage);
	DeleteSoundMem(NEXT_TEXT_SOUND);
	DeleteSoundMem(QUESTION_CORRECT_SOUND);
	DeleteSoundMem(QUESTION_WRONG_SOUND);
	DeleteSoundMem(CHOICES_DESIDE_SOUND);
	DeleteSoundMem(DOOR_OPEN_ONE_SOUND);
}

void TextBox::Update()
{

	Player* player = FindGameObject<Player>();
	//mainStateがEND以外だったらプレイヤーの動きを止める
	if (MainState != TextBox_State::STATE_END)//trueとfalseの衝突を防ぐ
	{
		player->SetPlay(false);//プレイヤーの動きを止める
	}

	Common* common = FindGameObject<Common>();
	GameManager* gameManager = FindGameObject<GameManager>();
	Fader* fader = FindGameObject<Fader>();
	//メインの状態
	switch (MainState)
	{
	case TextBox_State::STATE_PRO:
		switch (TalkState)
		{
		case TextBox_State::STATE_STRING_1:
			if (common->GetLagCheck())
			{
				if (CheckHitKey(KEY_INPUT_SPACE))
				{
					PlaySoundMem(NEXT_TEXT_SOUND, DX_PLAYTYPE_BACK);
					TalkState = TextBox_State::STATE_STRING_2;
					common->SetLagIn_T();
					proEnd = false;
				}
			}
			break;

		case TextBox_State::STATE_STRING_2:
			if (common->GetLagCheck())
			{
				if (CheckHitKey(KEY_INPUT_SPACE))
				{
					PlaySoundMem(NEXT_TEXT_SOUND, DX_PLAYTYPE_BACK);
					TalkState = TextBox_State::STATE_STRING_3;
					common->SetLagIn_T();
					proEnd = false;
				}
			}
			break;

		case TextBox_State::STATE_STRING_3:
			if (common->GetLagCheck())
			{
				if (CheckHitKey(KEY_INPUT_SPACE))
				{
					
					PlaySoundMem(NEXT_TEXT_SOUND, DX_PLAYTYPE_BACK);
					MainState = TextBox_State::STATE_END;
					TalkState = TextBox_State::STATE_END;
					common->SetLagIn_T();
				}
			}
			break;
		default:
			break;
		}
		break;
	case TextBox_State::STATE_JAPANESE://国語
		if (common->GetLagCheck())
		{
			QuestionJapanese();
		}
		break;
	case TextBox_State::STATE_MATH://算数
		if (common->GetLagCheck())
		{
			QuestionMathematics();
		}
		break;
	case TextBox_State::STATE_SCIENCE://理科
		if (common->GetLagCheck())
		{
			QuestionScience();
		}
		break;
	case TextBox_State::STATE_SOCIETY://社会
		if (common->GetLagCheck())
		{
			QuestionSociety();
		}
		break;
	case TextBox_State::STATE_EXTRA://特別問題
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
				PlaySoundMem(CHOICES_DESIDE_SOUND, DX_PLAYTYPE_BACK);
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
				PlaySoundMem(CHOICES_DESIDE_SOUND, DX_PLAYTYPE_BACK);
				MainState = TextBox_State::STATE_END;
				common->SetLagIn_T();
			}
		}
		break;
	case TextBox_State::STATE_JP_HINT://国語のヒント
		if (common->GetLagCheck())
		{
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				PlaySoundMem(NEXT_TEXT_SOUND, DX_PLAYTYPE_BACK);
				MainState = TextBox_State::STATE_END;
				common->SetLagIn_T();
			}
		}
		break;
	case TextBox_State::STATE_MT_HINT://算数のヒント
		if (common->GetLagCheck())
		{
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				PlaySoundMem(NEXT_TEXT_SOUND, DX_PLAYTYPE_BACK);
				MainState = TextBox_State::STATE_END;
				common->SetLagIn_T();
			}
		}
		break;

	case TextBox_State::STATE_SCI_HINT://理科のヒント
		if (common->GetLagCheck())
		{
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				PlaySoundMem(NEXT_TEXT_SOUND, DX_PLAYTYPE_BACK);
				MainState = TextBox_State::STATE_END;
				common->SetLagIn_T();
			}
		}
		break;
	case TextBox_State::STATE_SOC_HINT://社会のヒント
		if (common->GetLagCheck())
		{
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				PlaySoundMem(NEXT_TEXT_SOUND, DX_PLAYTYPE_BACK);
				MainState = TextBox_State::STATE_END;
				common->SetLagIn_T();
			}
		}
		break;
	case TextBox_State::STATE_CLASS_ROOM://すかし
		if (common->GetLagCheck())
		{
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				PlaySoundMem(NEXT_TEXT_SOUND, DX_PLAYTYPE_BACK);
				MainState = TextBox_State::STATE_END;
				common->SetLagIn_T();
			}
		}
		break;
	case TextBox_State::STATE_ART_ROOM://すかし
		if (common->GetLagCheck())
		{
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				PlaySoundMem(NEXT_TEXT_SOUND, DX_PLAYTYPE_BACK);
				MainState = TextBox_State::STATE_END;
				common->SetLagIn_T();
			}
		}
		break;
	case TextBox_State::STATE_ESCAPE_WAIT://屋上の扉
		if (common->GetLagCheck())
		{
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				PlaySoundMem(NEXT_TEXT_SOUND, DX_PLAYTYPE_BACK);
				MainState = TextBox_State::STATE_END;
				common->SetLagIn_T();
			}
		}
		break;
	case TextBox_State::STATE_PRINCIPAL_OFFICE://ナポヒント
		switch (TalkState)
		{
		case TextBox_State::STATE_STRING_1:
			if (common->GetLagCheck())
			{
				if (CheckHitKey(KEY_INPUT_SPACE))
				{
					PlaySoundMem(NEXT_TEXT_SOUND, DX_PLAYTYPE_BACK);
					TalkState = TextBox_State::STATE_STRING_2;
					common->SetLagIn_T();
				}
			}
			break;

		case TextBox_State::STATE_STRING_2:
			if (common->GetLagCheck())
			{
				if (CheckHitKey(KEY_INPUT_SPACE))
				{
					PlaySoundMem(NEXT_TEXT_SOUND, DX_PLAYTYPE_BACK);
					MainState = TextBox_State::STATE_END;
					TalkState = TextBox_State::STATE_END;
					SetFontSize(16);
					common->SetLagIn_T();
				}
			}
			break;
		}
		break;
	case TextBox_State::STATE_TRUE://正解
		if (common->GetLagCheck())
		{
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				PlaySoundMem(NEXT_TEXT_SOUND, DX_PLAYTYPE_BACK);
				switch (Q_AND_A)
				{
				case TextBox_State::STATE_JAPANESE:
					keyManager->SetJpKey();
					MainState = TextBox_State::STATE_JP_KEY;
					common->SetLagIn_T();
					break;
				case TextBox_State::STATE_MATH:
					keyManager->SetMtKey();
					MainState = TextBox_State::STATE_MT_KEY;
					common->SetLagIn_T();
					break;
				case TextBox_State::STATE_SCIENCE:
					keyManager->SetSciKey();
					MainState = TextBox_State::STATE_SCI_KEY;
					common->SetLagIn_T();
					break;
				case TextBox_State::STATE_SOCIETY:
					keyManager->SetSocKey();
					MainState = TextBox_State::STATE_SOC_KEY;
					common->SetLagIn_T();
					break;
				case TextBox_State::STATE_EXTRA:
					keyManager->SetExKey();
					MainState = TextBox_State::STATE_EX_KEY;
					common->SetLagIn_T();
					break;
				}
			}
		}
		break;
	case TextBox_State::STATE_FALSE://不正解
		if (common->GetLagCheck())
		{
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				PlaySoundMem(NEXT_TEXT_SOUND, DX_PLAYTYPE_BACK);
				MainState = TextBox_State::STATE_END;
				common->SetLagIn_T();
				/*GameManager* GM = FindGameObject<GameManager>();
				GM->SetGameOver();*/
			}
		}
		break;
	case TextBox_State::STATE_JP_KEY://国語の答案をゲット
		if (common->GetLagCheck())
		{
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				PlaySoundMem(NEXT_TEXT_SOUND, DX_PLAYTYPE_BACK);
				if (keyManager->GetSbjectKey())
				{
					MainState = TextBox_State::STATE_EX_GUIDE;
					TalkState = TextBox_State::STATE_STRING_1;
					common->SetLagIn_T();
				}
				else
				{
					MainState = TextBox_State::STATE_END;
					common->SetLagIn_T();
				}
			}
		}
		break;
	case TextBox_State::STATE_MT_KEY://算数の答案をゲット
		if (common->GetLagCheck())
		{
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				PlaySoundMem(NEXT_TEXT_SOUND, DX_PLAYTYPE_BACK);
				if (keyManager->GetSbjectKey())
				{
					MainState = TextBox_State::STATE_EX_GUIDE;
					TalkState = TextBox_State::STATE_STRING_1;
					common->SetLagIn_T();
				}
				else
				{
					MainState = TextBox_State::STATE_END;
					common->SetLagIn_T();
				}
			}
		}
		break;
	case TextBox_State::STATE_SCI_KEY://理科の答案をゲット
		if (common->GetLagCheck())
		{
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				PlaySoundMem(NEXT_TEXT_SOUND, DX_PLAYTYPE_BACK);
				if (keyManager->GetSbjectKey())
				{
					MainState = TextBox_State::STATE_EX_GUIDE;
					TalkState = TextBox_State::STATE_STRING_1;
					common->SetLagIn_T();
				}
				else
				{
					MainState = TextBox_State::STATE_END;
					common->SetLagIn_T();
				}
			}
		}
		break;
	case TextBox_State::STATE_SOC_KEY://社会の答案をゲット
		if (common->GetLagCheck())
		{
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				PlaySoundMem(NEXT_TEXT_SOUND, DX_PLAYTYPE_BACK);
				if (keyManager->GetSbjectKey())
				{
					MainState = TextBox_State::STATE_EX_GUIDE;
					TalkState = TextBox_State::STATE_STRING_1;
					common->SetLagIn_T();
				}
				else
				{
					MainState = TextBox_State::STATE_END;
					common->SetLagIn_T();
				}
			}
		}
		break;
	case TextBox_State::STATE_EX_KEY://屋上の鍵をゲット
		if (common->GetLagCheck())
		{
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				PlaySoundMem(NEXT_TEXT_SOUND, DX_PLAYTYPE_BACK);
				MainState = TextBox_State::STATE_ESCAPE_GUIDE;
				common->SetLagIn_T();
			}
		}
		break;
	case TextBox_State::STATE_EX_GUIDE://特別問題の場所を示唆
		switch (TalkState)
		{
		case TextBox_State::STATE_STRING_1:
			if (common->GetLagCheck())
			{
				if (CheckHitKey(KEY_INPUT_SPACE))
				{
					PlaySoundMem(NEXT_TEXT_SOUND, DX_PLAYTYPE_BACK);
					TalkState = TextBox_State::STATE_STRING_2;
					common->SetLagIn_T();
				}
			}
			break;

		case TextBox_State::STATE_STRING_2:
			if (common->GetLagCheck())
			{
				if (CheckHitKey(KEY_INPUT_SPACE))
				{
					PlaySoundMem(NEXT_TEXT_SOUND, DX_PLAYTYPE_BACK);
					MainState = TextBox_State::STATE_END;
					TalkState = TextBox_State::STATE_END;
					common->SetLagIn_T();
				}
			}
			break;

		default :
			break;
		}
		break;
	case TextBox_State::STATE_ESCAPE_GUIDE://屋上からの脱出を示唆
		if (common->GetLagCheck())
		{
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				PlaySoundMem(NEXT_TEXT_SOUND, DX_PLAYTYPE_BACK);
				MainState = TextBox_State::STATE_END;
				common->SetLagIn_T();
			}
		}
		break;
	case TextBox_State::STATE_FIND_PRINCIPAL://校長発見時
		switch (TalkState)
		{
		case TextBox_State::STATE_STRING_1:
			if (common->GetLagCheck())
			{
				if (CheckHitKey(KEY_INPUT_SPACE))
				{
					PlaySoundMem(NEXT_TEXT_SOUND, DX_PLAYTYPE_BACK);
					TalkState = TextBox_State::STATE_STRING_2;
					common->SetLagIn_T();
				}
			}
			break;
		case TextBox_State::STATE_STRING_2:
			if (common->GetLagCheck())
			{
				if (CheckHitKey(KEY_INPUT_SPACE))
				{
					PlaySoundMem(NEXT_TEXT_SOUND, DX_PLAYTYPE_BACK);
					common->SetFirstMove();
					MainState = TextBox_State::STATE_END;
					TalkState = TextBox_State::STATE_END;
					common->SetLagIn_T();
				}
			}
			break;
		default:
			break;
		}
		break;
	case TextBox_State:: STATE_ESCAPE_TIME://脱出時
		
		if (common->GetLagCheck())
		{
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				PlaySoundMem(DOOR_OPEN_ONE_SOUND, DX_PLAYTYPE_BACK);
				MainState = TextBox_State::STATE_FINISH;
				fader->FadeOut(3.0f);
				gameManager->SetGameClear();
				common->SetLagIn_T();
			}
		}
		break;
	case TextBox_State::STATE_AFTER_ESCAPE://脱出後
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		switch (TalkState)
		{
		case TextBox_State::STATE_STRING_1:
			if (common->GetLagCheck())
			{
				if (CheckHitKey(KEY_INPUT_SPACE))
				{
					PlaySoundMem(NEXT_TEXT_SOUND, DX_PLAYTYPE_BACK);
					TalkState = TextBox_State::STATE_STRING_2;
					common->SetLagIn_T();
				}
			}
			break;
		case TextBox_State::STATE_STRING_2:
			if (common->GetLagCheck())
			{
				if (CheckHitKey(KEY_INPUT_SPACE))
				{
					PlaySoundMem(NEXT_TEXT_SOUND, DX_PLAYTYPE_BACK);
					TalkState = TextBox_State::STATE_STRING_3;
					common->SetLagIn_T();
				}
			}
			break;
		case TextBox_State::STATE_STRING_3:
			if (common->GetLagCheck())
			{
				if (CheckHitKey(KEY_INPUT_SPACE))
				{
					PlaySoundMem(NEXT_TEXT_SOUND, DX_PLAYTYPE_BACK);
					MainState = TextBox_State::STATE_END;
					TalkState = TextBox_State::STATE_END;
					common->SetLagIn_T();
				}
			}
			break;
		default:
			break;
		}
		break;
	case TextBox_State::STATE_END://STATE終了
		player->SetPlay(true);
		break;
	default:
		break;
	}

}

void TextBox::Draw()
{
	//問題の出力判定
	switch (MainState)
	{
	case TextBox_State::STATE_PRO:
		switch (TalkState)
		{
		case TextBox_State::STATE_STRING_1:
			DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
			DrawString(550, 570, "職員室に答案がない・・・　", GetColor(255, 255, 255), 1);
			break;
		case TextBox_State::STATE_STRING_2:
			DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
			DrawString(430, 570, "もしかしたら校内のどこかに隠されているかもしれない", GetColor(255, 255, 255), 1);
			break;
		case TextBox_State::STATE_STRING_3:
			DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
			DrawString(550, 570, "答案を盗んで脱出しよう！", GetColor(255, 255, 255), 1);
			break;
		default:
			break;
		}
		break;
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
		DrawString(500, 570, "３×４ー２＝？", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 1, "１．６", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 2, "２．１０", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 3, "３．１４", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 4, "４．５", GetColor(255, 255, 255), 1);

		break;
	case TextBox_State::STATE_SCIENCE://理科
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(500, 554, "夏の大三角を作る星座のうちデネブ、", GetColor(255, 255, 255), 1);
		DrawString(500, 554 + 16 * 1, "ベガ、あと一つは？", GetColor(255, 255, 255), 1);
		DrawString(550, 554 + 16 * 2, "１．アルタイル", GetColor(255, 255, 255), 1);
		DrawString(550, 554 + 16 * 3, "２．ペテルギウス", GetColor(255, 255, 255), 1);
		DrawString(550, 554 + 16 * 4, "３．シリウス", GetColor(255, 255, 255), 1);
		DrawString(550, 554 + 16 * 5, "４．アンタレス", GetColor(255, 255, 255), 1);

		break;
	case TextBox_State::STATE_SOCIETY://社会
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(500, 570, "710年にできた日本の首都の名前は？？", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 1, "１．平条京", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 2, "２．平安京", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 3, "３．幸安京", GetColor(255, 255, 255), 1);
		DrawString(550, 570 + 16 * 4, "４．平城京", GetColor(255, 255, 255), 1);

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
		switch (Q_AND_A)
		{
		case TextBox_State::STATE_JAPANESE:
			DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
			DrawString(550, 570, "国語の問題に挑戦しますか？", GetColor(255, 255, 255), 1);
			DrawString(600, 570 + 16 * 1, "１．はい", GetColor(255, 255, 255), 1);
			DrawString(600, 570 + 16 * 2, "２．いいえ", GetColor(255, 255, 255), 1);
			break;
		case TextBox_State::STATE_MATH:
			DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
			DrawString(550, 570, "算数の問題に挑戦しますか？", GetColor(255, 255, 255), 1);
			DrawString(600, 570 + 16 * 1, "１．はい", GetColor(255, 255, 255), 1);
			DrawString(600, 570 + 16 * 2, "２．いいえ", GetColor(255, 255, 255), 1);
			break;
		case TextBox_State::STATE_SCIENCE:
			DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
			DrawString(550, 570, "理科の問題に挑戦しますか？", GetColor(255, 255, 255), 1);
			DrawString(600, 570 + 16 * 1, "１．はい", GetColor(255, 255, 255), 1);
			DrawString(600, 570 + 16 * 2, "２．いいえ", GetColor(255, 255, 255), 1);
			break;
		case TextBox_State::STATE_SOCIETY:
			DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
			DrawString(550, 570, "社会の問題に挑戦しますか？", GetColor(255, 255, 255), 1);
			DrawString(600, 570 + 16 * 1, "１．はい", GetColor(255, 255, 255), 1);
			DrawString(600, 570 + 16 * 2, "２．いいえ", GetColor(255, 255, 255), 1);
			break;
		case TextBox_State::STATE_EXTRA:
			DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
			DrawString(550, 570, "最終問題に挑戦しますか？", GetColor(255, 255, 255), 1);
			DrawString(600, 570 + 16 * 1, "１．はい", GetColor(255, 255, 255), 1);
			DrawString(600, 570 + 16 * 2, "２．いいえ", GetColor(255, 255, 255), 1);
			break;
		}
		break;
	case TextBox_State::STATE_JP_HINT://国語のヒント
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(490, HintY, "「芥川龍之介　代表作：羅生門・鼻」", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_MT_HINT://算数のヒント
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(430, HintY, "「掛け算と割り算は足し算引き算よりも先に計算しよう！」", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_SCI_HINT://理科のヒント
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(470, HintY, "「デネブ　アルタイル　ベガ」", GetColor(255, 255, 255), 1);
		DrawString(470, HintY + 16, "「これが夏の大三角」", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_SOC_HINT://社会のヒント
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(480, HintY, "「納豆ねばねば平城京」", GetColor(255, 255, 255), 1);
		DrawString(480, HintY + 16, "「見間違いに注意！」", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_ART_ROOM://何もないとき
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(450, 580, "「校長先生の彫像のらしい... 筋肉ムキムキだ」", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_CLASS_ROOM://何もないとき
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(450, 580, "「机を探した...　しかしなにもなかった」", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_ESCAPE_WAIT:
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(450, 580, "「屋上の扉は固く閉ざされている」", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_PRINCIPAL_OFFICE://ナポ
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		switch (TalkState)
		{
		case TextBox_State::STATE_STRING_1:
			DrawString(450, HintY, "「ナポリタンが...  ナポい気分になってきた...」", GetColor(255, 255, 255), 1);
			break;
		case TextBox_State::STATE_STRING_2:
			SetFontSize(40);
			DrawString(500, HintY, "うぉww", GetColor(255, 255, 255), 1);
			break;
		default:
			break;
		}
		break;
	case TextBox_State::STATE_TRUE://正解
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(500, 580, "「正解！」", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_FALSE://不正解
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(500, 580, "「不正解...」", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_JP_KEY://国語の答案をゲット
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(490, HintY, "「国語の回答を手に入れた！」", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_MT_KEY://算数の答案をゲット
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(490, HintY, "「算数の回答を手に入れた！」", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_SCI_KEY://理科の答案をゲット
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(490, HintY, "「理科の回答を手に入れた！」", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_SOC_KEY://社会の答案をゲット
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(490, HintY, "「社会の回答を手に入れた！」", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_EX_KEY://屋上の鍵をゲット
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(490, HintY, "「屋上の鍵を手に入れた！」", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_EX_GUIDE://特別問題の場所を示唆
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		switch (TalkState)
		{
		case TextBox_State::STATE_STRING_1:
			DrawString(395, HintY, "「すべての回答を集めた！　脱出するために屋上のカギを探そう」", GetColor(255, 255, 255), 1);
			break;
		case TextBox_State::STATE_STRING_2:
			DrawString(490, HintY, "「めぼしい場所は職員室だろうか...」", GetColor(255,255,255), 1);
			break;
		default :
			break;
		}
		break;
	case TextBox_State::STATE_ESCAPE_GUIDE://屋上からの脱出を示唆
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(480, HintY, "「屋上へ向かって脱出しよう！」", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_FIND_PRINCIPAL://校長発見時
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		switch (TalkState)
		{
		case TextBox_State::STATE_STRING_1:
			DrawString(490, HintY, "「あれは・・・校長!?」", GetColor(255, 255, 255), 1);
			break;
		case TextBox_State::STATE_STRING_2:
			DrawString(480, HintY, "「捕まる前に屋上から脱出しないと!」", GetColor(255, 255, 255), 1);
			break;
		default:
			break;
		}
		break;
	case TextBox_State::STATE_ESCAPE_TIME://脱出時
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		DrawString(490, HintY, "「屋上の扉の鍵を開けた」", GetColor(255, 255, 255), 1);
		break;
	case TextBox_State::STATE_AFTER_ESCAPE:
		DrawRectGraph(BoxPosX, BoxPosY, 0, 0, 599, 180, BoxImage, 1);
		switch (TalkState)
		{
		case TextBox_State::STATE_STRING_1:
			DrawString(490, HintY, "「congratulation!」", GetColor(255, 255, 255), 1);
			break;
		case TextBox_State::STATE_STRING_2:
			DrawString(490, HintY, "「学校から脱出した」", GetColor(255, 255, 255), 1);
			break;
		case TextBox_State::STATE_STRING_3:
			DrawString(490, HintY, "「テストの回答を盗み出すことができた！」", GetColor(255, 255, 255), 1);
			break;
		default:
			break;
		}
		break;
	}
}

void TextBox::QuestionJapanese()
{
	if (common->GetLagCheck())
	{
		if (CheckHitKey(KEY_INPUT_1))//不正解
		{
			PlaySoundMem(QUESTION_WRONG_SOUND, DX_PLAYTYPE_BACK);
			MainState = TextBox_State::STATE_FALSE;
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_2))//不正解
		{
			PlaySoundMem(QUESTION_WRONG_SOUND, DX_PLAYTYPE_BACK);
			MainState = TextBox_State::STATE_FALSE;
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_3))//正解
		{
			PlaySoundMem(QUESTION_CORRECT_SOUND, DX_PLAYTYPE_BACK);
			MainState = TextBox_State::STATE_TRUE;
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_4))//不正解
		{
			PlaySoundMem(QUESTION_WRONG_SOUND, DX_PLAYTYPE_BACK);
			MainState = TextBox_State::STATE_FALSE;
			common->SetLagIn_T();
		}
	}
}

void TextBox::QuestionMathematics()
{
	if (common->GetLagCheck())
	{
		if (CheckHitKey(KEY_INPUT_1))//不正解
		{
			PlaySoundMem(QUESTION_WRONG_SOUND, DX_PLAYTYPE_BACK);
			MainState = TextBox_State::STATE_FALSE;
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_2))//正解
		{
			PlaySoundMem(QUESTION_CORRECT_SOUND, DX_PLAYTYPE_BACK);
			MainState = TextBox_State::STATE_TRUE;
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_3))//不正解
		{
			PlaySoundMem(QUESTION_WRONG_SOUND, DX_PLAYTYPE_BACK);
			MainState = TextBox_State::STATE_FALSE;
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_4))//不正解
		{
			PlaySoundMem(QUESTION_WRONG_SOUND, DX_PLAYTYPE_BACK);
			MainState = TextBox_State::STATE_FALSE;
			common->SetLagIn_T();
		}
	}
}

void TextBox::QuestionScience()
{
	if (common->GetLagCheck())
	{
		if (CheckHitKey(KEY_INPUT_1))//正解
		{
			PlaySoundMem(QUESTION_CORRECT_SOUND, DX_PLAYTYPE_BACK);
			MainState = TextBox_State::STATE_TRUE;
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_2))//不正解
		{
			PlaySoundMem(QUESTION_WRONG_SOUND, DX_PLAYTYPE_BACK);
			MainState = TextBox_State::STATE_FALSE;
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_3))//不正解
		{
			PlaySoundMem(QUESTION_WRONG_SOUND, DX_PLAYTYPE_BACK);
			MainState = TextBox_State::STATE_FALSE;
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_4))//不正解
		{
			PlaySoundMem(QUESTION_WRONG_SOUND, DX_PLAYTYPE_BACK);
			MainState = TextBox_State::STATE_FALSE;
			common->SetLagIn_T();
		}
	}
}

void TextBox::QuestionSociety()
{
	if (common->GetLagCheck())
	{
		if (CheckHitKey(KEY_INPUT_1))//不正解
		{
			PlaySoundMem(QUESTION_WRONG_SOUND, DX_PLAYTYPE_BACK);
			MainState = TextBox_State::STATE_FALSE;
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_2))//不正解
		{
			PlaySoundMem(QUESTION_WRONG_SOUND, DX_PLAYTYPE_BACK);
			MainState = TextBox_State::STATE_FALSE;
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_3))//不正解
		{
			PlaySoundMem(QUESTION_WRONG_SOUND, DX_PLAYTYPE_BACK);
			MainState = TextBox_State::STATE_FALSE;
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_4))//正解
		{
			PlaySoundMem(QUESTION_CORRECT_SOUND, DX_PLAYTYPE_BACK);
			MainState = TextBox_State::STATE_TRUE;
			common->SetLagIn_T();
		}
	}
}

void TextBox::QuestionExtra()
{
	if (common->GetLagCheck())
	{
		if (CheckHitKey(KEY_INPUT_1))//不正解
		{
			PlaySoundMem(QUESTION_WRONG_SOUND, DX_PLAYTYPE_BACK);
			MainState = TextBox_State::STATE_FALSE;
			False = true;
			common->PlayHellMusic();
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_2))//不正解
		{
			PlaySoundMem(QUESTION_WRONG_SOUND, DX_PLAYTYPE_BACK);
			MainState = TextBox_State::STATE_FALSE;
			False = true;
			common->PlayHellMusic();
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_3))//正解
		{
			PlaySoundMem(QUESTION_CORRECT_SOUND, DX_PLAYTYPE_BACK);
			MainState = TextBox_State::STATE_TRUE;
			common->SetLagIn_T();
		}
		if (CheckHitKey(KEY_INPUT_4))//不正解
		{
			PlaySoundMem(QUESTION_WRONG_SOUND, DX_PLAYTYPE_BACK);
			MainState = TextBox_State::STATE_FALSE;
			False = true;
			common->PlayHellMusic();
			common->SetLagIn_T();
		}
	}
}


