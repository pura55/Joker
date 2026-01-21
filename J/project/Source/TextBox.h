#pragma once
#include "../Library/GameObject.h"
#include "Common.h"
#include "KeyManager.h"

//textboxの状態
enum class TextBox_State
{
	//STATE終了
	STATE_END = 0,

	//プロローグ
	STATE_PRO = 1,

	//問題
	STATE_JAPANESE = 2,//国語
	STATE_MATH,        //算数
	STATE_SCIENCE,     //理科
	STATE_SOCIETY,     //社会
	STATE_EXTRA,       //特別問題

	//選択
	STATE_DICIDE,      //はい・いいえ

	//ヒント
	STATE_JP_HINT,     //国語のヒント
	STATE_MT_HINT,     //算数のヒント
	STATE_SCI_HINT,    //理科のヒント
	STATE_SOC_HINT,    //社会のヒント

	//鍵
	STATE_JP_KEY,      //国語の鍵
	STATE_MT_KEY,      //算数の鍵
	STATE_SCI_KEY,     //理科の鍵
	STATE_SOC_KEY,     //社会の鍵
	STATE_EX_KEY,      //特別問題の鍵

	//場所
	STATE_CLASS_ROOM,   //教室
	STATE_ART_ROOM,     //美術室
	STATE_PRINCIPAL_OFFICE,//校長室

	//場面
	STATA_FIND_PRINCIPAL, //校長発見時
	STATE_ESCAPE_TIME,    //脱出時

	//案内
	STATE_EX_GUIDE,    //特別問題の場所を示唆
	STATE_ESCAPE_GUIDE,//屋上からの脱出を示唆

	//脱出を止める
	STATE_ESCAPE_WAIT,

	//脱出後
	STATE_AFTER_ESCAPE,

	//同じ内容の文章で複数文章がある場合使用する
	STATE_STRING_1,
	STATE_STRING_2,
	STATE_STRING_3,
	STATE_STRING_4,

	//正解
	STATE_TRUE,    
	//不正解
	STATE_FALSE           

	//STATE_BLANK,       //使うかもしれないから残す
};

class TextBox : public GameObject
{
public:
	TextBox();
	~TextBox();
	void Update()override;
	void Draw()override;

	//問題の正誤判定関数
	void QuestionJapanese();    //国語の問題判定
	void QuestionMathematics(); //算数の問題判定
	void QuestionScience();     //理科の問題判定
	void QuestionSociety();     //社会の問題判定
	void QuestionExtra();       //特別問題の正誤判定

public://setter

	//プロローグ
	void SetPro() 
	{ 
		MainState = TextBox_State::STATE_PRO; 
		TalkState = TextBox_State::STATE_STRING_1;
	}

	//問題
	void SetJapanese()//国語の問題をセット
	{
		MainState = TextBox_State::STATE_DICIDE;
		Q_AND_A = TextBox_State::STATE_JAPANESE;
	}
	void SetMath()//算数の問題をセット
	{
		MainState = TextBox_State::STATE_DICIDE;
		Q_AND_A = TextBox_State::STATE_MATH;
	}
	void SetScience()//理科の問題をセット
	{
		MainState = TextBox_State::STATE_DICIDE;
		Q_AND_A = TextBox_State::STATE_SCIENCE;
	}
	void SetSociety()//社会の問題をセット
	{
		MainState = TextBox_State::STATE_DICIDE;
		Q_AND_A = TextBox_State::STATE_SOCIETY;
	}
	void SetExtra()//特別問題をセット
	{
		MainState = TextBox_State::STATE_DICIDE;
		Q_AND_A = TextBox_State::STATE_EXTRA;
	}

	//ヒント
	void SetJapaneseHint() { MainState = TextBox_State::STATE_JP_HINT; }//国語のヒントをセット
	void SetMathHint() { MainState = TextBox_State::STATE_MT_HINT; }//算数のヒントをセット
	void SetScienceHint() { MainState = TextBox_State::STATE_SCI_HINT; }//理科の問題をセット
	void SetSocietyHint() { MainState = TextBox_State::STATE_SOC_HINT; }//社会の問題をセット

	//透かし
	void SetArt() { MainState = TextBox_State::STATE_ART_ROOM; }//美術室
	void SetCls() { MainState = TextBox_State::STATE_CLASS_ROOM; }//教室
	void SetPri() 
	{
		MainState = TextBox_State::STATE_PRINCIPAL_OFFICE;
		TalkState = TextBox_State::STATE_STRING_1;
	}//校長室

	//脱出口
	void SetEscapeWait() { MainState = TextBox_State::STATE_ESCAPE_WAIT; }//屋上

	//場面
	void SetEscapeText() { MainState = TextBox_State::STATE_ESCAPE_TIME; }

private://変数
	int BoxImage;//mapの描画変数
	bool proEnd;

private://sound
	const int NEXT_TEXT_SOUND = LoadSoundMem("data/sound/Nexttext.mp3");
	const int QUESTION_RIGHT_SOUND = LoadSoundMem("data/sound/Right.mp3");
	const int QUESTION_WRONG_SOUND = LoadSoundMem("data/sound/Notright.mp3");
	const int CHOICES_DESIDE_SOUND = LoadSoundMem("data/sound/deside.mp3");
	const int DOOR_OPEN_ONE_SOUND = LoadSoundMem("data/sound/openonedoor.mp3");

private://state
	TextBox_State MainState;//テキストボックスの状態
	TextBox_State Q_AND_A;  //問題の状態
	TextBox_State TalkState;//プレイヤーの思考

private://object
	Common* common;
	KeyManager* keyManager;

private://定数
	const int BoxPosX = 350;
	const int BoxPosY = 500;
	const int HintY = 580;//ヒント文のY座標
};