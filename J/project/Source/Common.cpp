#include "Common.h"
#include "../ImGui/imgui.h"

Common::Common()
{
	DontDestroyOnSceneChange(); // Scene‚ª•Ï‚í‚Á‚Ä‚àÁ‚¦‚È‚¢
	ClearTime = 0.0f;
	LagTime = 0.0f;
	PushStop = true;
}

void Common::Update()
{
	/*ImGui::Begin("Common");
	ImGui::InputInt("Stage", &stageNumber);
	ImGui::Checkbox("NoDead", &noDead);
	ImGui::End()*/;
	if (!PushStop)
	{
		LagTime += Time::DeltaTime();
		if (LagTime >= 0.5f)
		{
			PushStop = true;
			LagTime = 0.0f;
		}
	}
}

void Common::SetLagTime()
{
	
}
