#pragma once
#include "../Library/GameObject.h"

//textboxの状態
enum class TextBox_State
{
	//問題
	STATE_JAPANESE = 1,//国語
	STATE_MATH,        //算数
	STATE_SCIENCE,     //理科
	STATE_SOCIETY,     //社会
	STATE_EXTRA,       //特別問題
	STATE_BLANK,       //何もない
	STATE_TRUE,        //正解
	STATE_FALSE,       //不正解

	//その他の状態
	STATE_END = 100,   //STATE終了
};

class TextBox : public GameObject
{
public:
	TextBox(TextBox_State state);
	~TextBox();
	void Update()override;
	void Draw()override;
	//問題の正誤判定関数
	void QuestionJapanese();    //国語の問題判定
	void QuestionMathematics(); //算数の問題判定
	void QuestionScience();     //理科の問題判定
	void QuestionSociety();     //社会の問題判定
	void QuestionExtra();       //特別問題の正誤判定
	
public:
	TextBox_State GetJapanse() const { return TextBox_State::STATE_JAPANESE; }
	TextBox_State GetMath() const { return TextBox_State::STATE_MATH; }
	TextBox_State GetScience() const { return TextBox_State::STATE_SCIENCE; }
	TextBox_State GetSociety() const { return TextBox_State::STATE_SOCIETY; }
	TextBox_State GetExtra() const { return TextBox_State::STATE_EXTRA; }
	TextBox_State GetBlank() const { return TextBox_State::STATE_BLANK; }

private:
	int BoxImage;//mapの描画変数
	int TextState;//textの状態
	float time;//ボタンを押す時間間隔
	bool TextJudge;//ボタンの時間のフラッグ
	TextBox_State question;//問題の状態
	TextBox_State another;//その他の状態

private:
	const int BoxPosX = 350;
	const int BoxPosY = 500;
};