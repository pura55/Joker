#include "PlayScene.h"
#include "Player.h"
#include "MainMap.h"
#include "FloorMap.h"
#include "TextBox.h"
#include "KeyManager.h"
#include "GameManager.h"
#include "Fader.h"
#include "Common.h"

PlayScene::PlayScene()
{
	//ƒvƒŒƒCƒV[ƒ“¶¬ƒRƒ‚ƒ“‚ğ‰Šú‰»
	Common* common = FindGameObject<Common>();
	common->INIT();
	new GameManager();


	//new KeyManager();
	//new FloorMap(1);//‰ŠúƒtƒƒA
	//new MainMap(1);//‰Šúƒ}ƒbƒv
	//new Player(64 * 5 + 64 * 4, 64 * 3 + 64 * 1);  //‰ŠúƒvƒŒƒCƒ„[¶¬
	//new TextBox();

	
	// ()‚Ì’†‚Écsv‚Ì”š“ü‚ê‚ê‚Î“Ç‚İ‚İ‚Ü‚·
	
	// ˆÈ‰ºMainMap&FloorMap‚Ìcsv‚Ì”š
	//1 = Eˆõº/2 = —‰Èº/3 = }‘º/4 = Z’·º/5 = ‰¹Šyº/6 = ”üpº
	//101 = ‚PŠK‹³º‚P/102 = ‚PŠK‹³º‚Q/201 = ‚QŠK‹³º‚P/202 = ‚QŠK‹³º‚Q
	//1000 = ‚PŠK˜L‰º/2000 = ‚QŠK˜L‰º
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{

	if (CheckHitKey(KEY_INPUT_O)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void PlayScene::Draw()
{
	//DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	//DrawString(100, 400, "Push [O]Key To Title", GetColor(255, 255, 255));
}
