#pragma once
#include "../Library/GameObject.h"
#include "Common.h"

//textboxの状態
enum class TextBox_State
{
	//問題
	STATE_JAPANESE = 1,//国語
	STATE_MATH,        //算数
	STATE_SCIENCE,     //理科
	STATE_SOCIETY,     //社会
	STATE_EXTRA,       //特別問題
	STATE_DICIDE,      //はい・いいえ
	STATE_JP_HINT,     //国語のヒント
	STATE_MT_HINT,     //算数のヒント
	STATE_SCI_HINT,    //理科のヒント
	STATE_SOC_HINT,    //社会のヒント
	STATE_BLANK,       //何もない
	STATE_TRUE,        //正解
	STATE_FALSE,       //不正解
	STATE_END,   //STATE終了
};

class TextBox : public GameObject
{
public:
	TextBox();
	~TextBox();
	void Update()override;
	void Draw()override;
	void TextPro(); //プロローグ

	//問題の正誤判定関数
	void QuestionJapanese();    //国語の問題判定
	void QuestionMathematics(); //算数の問題判定
	void QuestionScience();     //理科の問題判定
	void QuestionSociety();     //社会の問題判定
	void QuestionExtra();       //特別問題の正誤判定
	
public://setter
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
	void SetJapaneseHint() { MainState = TextBox_State::STATE_JP_HINT; }//国語のヒントをセット
	void SetMathHint() { MainState = TextBox_State::STATE_MT_HINT; }//算数のヒントをセット
	void SetScienceHint() { MainState = TextBox_State::STATE_SCI_HINT; }//理科の問題をセット
	void SetSocietyHint() { MainState = TextBox_State::STATE_SOC_HINT; }//社会の問題をセット
	void SetBlank() { MainState = TextBox_State::STATE_BLANK; }//すかしをセット

public://getter
	bool GetJpKey()const { return jpKey; }
	bool GetMtKey()const { return mtKey; }
	bool GetSciKey()const { return sciKey; }
	bool GetSocKey()const { return socKey; }
	bool GetExKey()const { return exKey; }
private://変数
	int BoxImage;//mapの描画変数
	bool jpKey;  //国語の鍵
	bool mtKey;  //算数の鍵
	bool sciKey; //理科の鍵
	bool socKey; //社会の鍵
	bool exKey;  //特別問題の鍵

private://state
	TextBox_State MainState;//問題の状態
	TextBox_State Q_AND_A;
    TextBox_State TalkState;//プレイヤーの思考

private://object
	Common* common;

private://定数
	const int BoxPosX = 350;
	const int BoxPosY = 500;
	const int HintX = 580;//ヒント文のX座標
};