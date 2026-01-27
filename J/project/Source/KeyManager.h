#pragma once
#include "../Library/GameObject.h"

enum class WINDOW
{
	//初期化
	STATE_INIT = 0,

	//ウィンドウのオン・オフ
	STATE_ON = 1,
	STATE_OFF = 2,

	//タスク
	STATE_TASK_FINISH
};

class KeyManager : public GameObject
{
public:
	KeyManager() ;
	~KeyManager() ;
	void Update() override;
	void Draw() override;
	void ChangeColor();
	void Line();

public://setter
	void SetJpKey() { jpKey = true; }   //国語の回答が正解
	void SetMtKey() { mtKey = true; }	//算数の回答が正解
	void SetSciKey() { sciKey = true; }	//理科の回答が正解
	void SetSocKey() { socKey = true; }	//社会の回答が正解
	void SetExKey() { exKey = true; }	//特別問題の回答が正解

public://getter
	bool GetJpKey() const{ return jpKey; }
	bool GetMtKey() const{ return mtKey; }
	bool GetSciKey() const{ return sciKey; }
	bool GetSocKey() const{ return socKey; }
	bool GetExKey() const { return exKey; }
	bool GetSbjectKey() const { return subjectKey; }

private:
	//鍵
	bool jpKey;      //国語の鍵
	bool mtKey;	     //算数の鍵
	bool sciKey;     //理科の鍵
	bool socKey;     //社会の鍵
	bool exKey;	     //特別問題の鍵
	bool subjectKey; //4教科の鍵

	bool showWindow; //ウィンドウを表示する

	//色
	int RGB_JP;
	int RGB_MT;
	int RGB_SOC;
	int RGB_SCI;
	int RGB_EX;
	int RGB_ESC;

	WINDOW state;
	WINDOW string;

private:
	//画像
	const int WINDOW_BOX = LoadGraph("data/image/windowBOX.jpg");

	//定数
	//タスクの座標
	const int taskPosX = 454;
	const int taskPosY = 200;
	const int taskSpaceY = 80;
	const int lineSpaceY = 8;
	const int lineFront = 24;
	const int lineBack = 8;
};