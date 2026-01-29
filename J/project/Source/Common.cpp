#include "Common.h"
#include "TextBox.h"
#include "../ImGui/imgui.h"

Common::Common()
{
	DontDestroyOnSceneChange(); // Sceneが変わっても消えない
	
	//初期化
	ClearTime = 0.0f;
	TimeLag = 0.0f;
	walkTime = 0.0f;
	openTime = 0.0f;
	lagCheck = true;
	playWalkFlag = true;
	playOpenFlag = true;
	firstSpawn = true;
	firstMove = true;
	firstText = true;
	firstPlaySound = true;

	warpOutX = -1;
	warpOutY = -1;
}

Common::~Common()
{
	DeleteSoundMem(HEAVEN_MUSIC);
	DeleteSoundMem(HELL_MUSIC);
	DeleteSoundMem(WALK_SOUND);
	DeleteSoundMem(DOOR_OPEN_TWO_SOUND);
	DeleteSoundMem(START_SOUND);
	DeleteSoundMem(CLEAR_MUSIC);
	DeleteSoundMem(PRO_JINGLE);
}

void Common::INIT()
{
	ClearTime = 0.0f;
	TimeLag = 0.0f;
	walkTime = 0.0f;
	openTime = 0.0f;
	lagCheck = true;
	playWalkFlag = true;
	playOpenFlag = true;
	firstSpawn = true;
	firstMove = true;
	firstText = true;
	firstPlaySound = true;

	warpOutX = -1;
	warpOutY = -1;
}

void Common::Update()
{
	/*ImGui::Begin("Common");
	ImGui::InputInt("Stage", &stageNumber);
	ImGui::Checkbox("NoDead", &noDead);
	ImGui::End()*/;

	TextBox* textBox = FindGameObject<TextBox>();
	//校長先生出現時のスポーン・テキスト・プレイサウンド
	if (!firstSpawn)
	{
		if (firstText)
		{
			textBox->SetFindPri();
			firstText = false;
		}

		if (!firstMove)
		{
			if (firstPlaySound)
			{
				PlayHellMusic();
				firstPlaySound = false;
			}
		}
	}
    
	//1.0f経ったら歩くサウンドをストップする
	if (!playWalkFlag)
	{
		walkTime += Time::DeltaTime();
		if (walkTime >= 1.0f)
		{
			StopSoundMem(WALK_SOUND);
			playWalkFlag = true;
			walkTime = 0.0f;
		}
	}

	//
	if (!playOpenFlag)
	{
		openTime += Time::DeltaTime();
		if (openTime >= 1.2f)
		{
			StopSoundMem(DOOR_OPEN_TWO_SOUND);
			playOpenFlag = true;
			openTime = 0.0f;
		}
	}
	

	//ワープした時のラグ
	if (!lagCheck)
	{
		if (nowState == COMMON_STATE::STATE_WARP)
		{
			WarpLag();//ワープをするのにかかるラグをセット
		}
		else if (nowState == COMMON_STATE::STATE_TEXT)
		{
			TextLag();//textを勧めるのにかかるラグをセット
		}

	}

}

void Common::WarpLag()
{
	TimeLag += Time::DeltaTime();
	if (TimeLag >= 0.5f)
	{
		lagCheck = true;
		TimeLag = 0.0f;
	}
}

void Common::TextLag()
{
	TimeLag += Time::DeltaTime();
	if (TimeLag >= 0.65f)
	{
		lagCheck = true;
		TimeLag = 0.0f;
	}
}

void Common::PlayHeavenMusic()
{
	PlaySoundMem(HEAVEN_MUSIC, DX_PLAYTYPE_BACK);
}

void Common::StopHeavenMusic()
{
	StopSoundMem(HEAVEN_MUSIC);
}

void Common::PlayHellMusic()
{
	PlaySoundMem(HELL_MUSIC, DX_PLAYTYPE_BACK);
}

void Common::StopHellMusic()
{
	StopSoundMem(HELL_MUSIC);
}

void Common::PlayWalkSound()
{
	if (playWalkFlag)
	{
		PlaySoundMem(WALK_SOUND, DX_PLAYTYPE_BACK);
		playWalkFlag = false;
	}
}

void Common::StopWalkSound()
{
	StopSoundMem(WALK_SOUND);
}

void Common::PlayOpenDoorSound()
{
	if (playOpenFlag)
	{
		PlaySoundMem(DOOR_OPEN_TWO_SOUND, DX_PLAYTYPE_BACK);
		playOpenFlag = false;
	}
}

void Common::PlayStartSound()
{
	PlaySoundMem(START_SOUND, DX_PLAYTYPE_BACK);
}

void Common::PlayClearMusic()
{
	PlaySoundMem(CLEAR_MUSIC, DX_PLAYTYPE_LOOP);
}

void Common::StopClearMusic()
{
	StopSoundMem(CLEAR_MUSIC);
}

void Common::PlayProJingle()
{
	PlaySoundMem(PRO_JINGLE, DX_PLAYTYPE_BACK);
}
