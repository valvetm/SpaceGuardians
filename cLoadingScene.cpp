#include "DXUT.h"
#include "cLoadingScene.h"


cLoadingScene::cLoadingScene()
{
}


cLoadingScene::~cLoadingScene()
{
}

void cLoadingScene::Init()
{
	LoadImage("Player", "Player/Player");
	LoadImage("Point", "Player/Point");
	LoadImage("Zako", "Enemy/Zako", 10);
	LoadImage("Boss1", "Enemy/Boss1", 2);
	LoadImage("Boss2", "Enemy/Boss2");
	LoadImage("Boss3", "Enemy/Boss3", 2);
	LoadImage("Asteroid", "Effect/Asteroid ", 6);
	LoadImage("Debris", "Effect/Debris (", 6);
	LoadImage("Explosion", "Effect/Explosion");
	LoadImage("Explosion", "Effect/Explosion", 27);
	IMAGE->AddAnimation("Explosion", 27);
	LoadImage("Laser", "Effect/Laser");
	LoadImage("LaserPart", "Effect/LaserPart");
	LoadImage("Ring", "Effect/Ring");
	LoadImage("Shield", "Effect/Shield Bubble");
	LoadImage("Smoke", "Effect/Smoke ", 3);
	LoadImage("Spark", "Effect/spark_0", 4);
	LoadImage("Bullet", "Bullet/Bullet", 4);
	LoadImage("BossHp", "UI/BossHp");
	LoadImage("Gauge", "UI/Gauge");
	LoadImage("SideBar", "UI/SideBar");
	LoadImage("Skill", "UI/Skill", 2);
	LoadImage("Title", "UI/Title");
	LoadImage("Back", "Back", 2);
	LoadImage("Back_Win", "Back_Win");
	LoadImage("Back_Lose", "Back_Lose");
	LoadImage("Back_Title", "Back_Title");
	LoadImage("Item_Hp", "Item_Hp");
	LoadImage("Item_Time", "Item_Time");
	LoadImage("Item_Level", "Item_Level");
	LoadImage("Item_Score", "Item_Score");
	LoadImage("Damaged", "UI/Damaged");
	LoadImage("How", "How");
	LoadImage("Nebula", "Nebula", 3);
	LoadImage("BFG", "Bullet/BFG", 32);
	IMAGE->AddAnimation("BFG", 32);
	LoadImage("Beam", "Effect/Beam", 3);
	LoadImage("BFGExplosion", "Effect/BFGExplosion", 24);
	IMAGE->AddAnimation("BFGExplosion", 24);

	LoadSound("Explosion", L"Building Explosion ", 4);
	LoadSound("BossExplosion", L"Enemies Exploding ", 5);
	LoadSound("Hit", L"Hit");
	LoadSound("Impact", L"impact-", 4);
	LoadSound("Item", L"Item");
	LoadSound("Lose", L"Lose");
	LoadSound("Win", L"Win");
	LoadSound("Laser", L"Laser");
	LoadSound("PlayerFire", L"MG ", 14);
	LoadSound("Music", L"Music");
	LoadSound("Shield", L"Shield");
	LoadSound("Level", L"Level");
	LoadSound("BFGCharge", L"BFGCharge");
	LoadSound("BFGFire", L"BFGFire");
	LoadSound("Asteroid", L"Destruction ", 5);

	SCENE->ChangeScene("TITLE");
}

void cLoadingScene::Update()
{
}

void cLoadingScene::Render()
{
}

void cLoadingScene::Release()
{
}

void cLoadingScene::LoadImage(string _Key, string _Path, int _Amount)
{
	char Path[128];
	if (_Amount == 1)
	{
		sprintf(Path, "./Resource/Image/%s.png", _Path.c_str());
		IMAGE->AddImage(_Key, Path);
	}
	else
	{
		char Key[64];
		for (int i = 1; i <= _Amount; i++)
		{
			sprintf(Path, "./Resource/Image/%s%d.png", _Path.c_str(), i);
			sprintf(Key, "%s%d", _Key.c_str(), i);
			IMAGE->AddImage(Key, Path);
		}
	}
}

void cLoadingScene::LoadSound(string _Key, LPWSTR _Path, int _Amount)
{
	TCHAR Path[128];
	if (_Amount == 1)
	{
		swprintf(Path, L"./Resource/Sound/%s.wav", _Path);
		SOUND->AddSound(_Key, Path);
	}
	else
	{
		char Key[64];
		for (int i = 1; i <= _Amount; i++)
		{
			swprintf(Path, L"./Resource/Sound/%s%d.wav", _Path, i);
			sprintf(Key, "%s%d", _Key.c_str(), i);
			SOUND->AddSound(Key, Path);
		}
	}
}
