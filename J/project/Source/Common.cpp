#include "Common.h"
#include "../ImGui/imgui.h"

Common::Common()
{
	DontDestroyOnSceneChange(); // Sceneが変わっても消えない
	
	//初期化
	ClearTime = 0.0f;
	TimeLag = 0.0f;
	lagCheck = true;

	warpOutX = -1;
	warpOutY = -1;
}

void Common::Update()
{
	/*ImGui::Begin("Common");
	ImGui::InputInt("Stage", &stageNumber);
	ImGui::Checkbox("NoDead", &noDead);
	ImGui::End()*/;

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
	PlaySoundMem(HELL_MUSIC, DX_PLAYTYPE_BACK);
}

void Common::StopHeavenMusic()
{
	StopSoundMem(HELL_MUSIC);
}

void Common::PlayHellMusic()
{
	PlaySoundMem(HELL_MUSIC, DX_PLAYTYPE_BACK);
}

void Common::StopHellMusic()
{
	StopSoundMem(HELL_MUSIC);
}
