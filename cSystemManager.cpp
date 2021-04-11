#include "DXUT.h"
#include "cSystemManager.h"
#include "cPlayer.h"
#include "cItem.h"


cSystemManager::cSystemManager()
{
}


cSystemManager::~cSystemManager()
{
}

void cSystemManager::Init()
{
	PlayerInit();
	OnSceneChange();
	m_Rank.clear();
	m_Rank.push_back(RankData{ L"IOR", 10000 });
	m_Rank.push_back(RankData{ L"ZUN", 100000000 });
	m_Rank.push_back(RankData{ L"TOU", 10000000 });
	m_Rank.push_back(RankData{ L"HOU", 1000000 });
	m_Rank.push_back(RankData{ L"KYO", 100000 });
	m_Rank.push_back(RankData{ L"---", 0 });
	m_Rank.push_back(RankData{ L"---", 0 });
	m_Rank.push_back(RankData{ L"---", 0 });
	m_Rank.push_back(RankData{ L"---", 0 });
	m_Rank.push_back(RankData{ L"---", 0 });
	SortRank();
}

void cSystemManager::Update()
{
	for (int i = 0; i < 4; i++)
	{
		m_Alarm[i]--;
		if (m_Alarm[i] <= 0 && m_Alarm[i] > -100)
		{
			m_Alarm[i] = -100;
			switch (i)
			{
			case 0:
				SCENE->ChangeScene("STAGE2");
				OnSceneChange();
				break;
			case 1:
				SCENE->ChangeScene("STAGE1");
				OnSceneChange();
				break;
			case 2:
				SCENE->ChangeScene("RESULT");
				OnSceneChange();
				SOUND->StopAll();
				break;
			case 3:
				SCENE->ChangeScene("TITLE");
				OnSceneChange();
				PlayerInit();
				SOUND->StopAll();
				break;
			}
		}
	}

	if (OBJECT->m_Player != nullptr)
	{
		cPlayer* Player = OBJECT->m_Player->GetComponent<cPlayer>();
		if (INPUT->KeyDown(VK_F1))
		{
			if (Player->GetComponent<cCollider>()->m_CollWith.size() == 0)
			{
				Player->GetComponent<cCollider>()->m_CollWith.push_back(Obj_Asteroid);
				Player->GetComponent<cCollider>()->m_CollWith.push_back(Obj_EnemyBullet);
			}
			else
			{
				Player->GetComponent<cCollider>()->m_CollWith.clear();
			}
		}
		if (INPUT->KeyDown(VK_F2) && Player->m_Level != 5)
		{
			Player->m_Exp += Player->m_MaxExp;
		}
		if (INPUT->KeyDown(VK_F3))
		{
			cObject* a;
			switch (Random(1, OBJECT->m_Player->GetComponent<cPlayer>()->m_Level == 5 ? 9 : 10))
			{
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
				a = OBJECT->AddObject("Item_Hp", Player->m_Owner->m_Pos + Vec2(0,-100), 0.4, Obj_Item);
				break;
			case 7:
			case 8:
			case 9:
				a = OBJECT->AddObject("Item_Time", Player->m_Owner->m_Pos + Vec2(0, -100), 0.4, Obj_Item);
				break;
			case 10:
				a = OBJECT->AddObject("Item_Level", Player->m_Owner->m_Pos + Vec2(0, -100), 0.4, Obj_Item);
				break;
			}
			a->AddComponent<cItem>();
		}
	}
	if (INPUT->KeyDown(VK_F4))
	{
		m_Alarm[3] = 0;
	}
	if (INPUT->KeyDown(VK_F5))
	{
		m_Alarm[1] = 0;
	}
	if (INPUT->KeyDown(VK_F6))
	{
		m_Alarm[0] = 0;
	}
}

void cSystemManager::Render()
{
	if (OBJECT->m_Player != nullptr)
	{
		cPlayer* Player = OBJECT->m_Player->GetComponent<cPlayer>();
		RECT Rect = { 0,0,0,0 };
		TCHAR Text[256];

		Rect.right = 350;
		Rect.bottom = 60;
		Rect.left = 350 - Clamp((Player->m_Hp / Player->m_MaxHp) * 350, 0, 350);
		IMAGE->CenterRenderRectView(IMAGE->Find("Gauge"), Vec2(1720 + Rect.left, 300), 0, Vec2(1, 1), 0.09, Rect, 0xffff0000);
		IMAGE->CenterRenderView(IMAGE->Find("Gauge"), Vec2(1720, 300), 0, Vec2(1, 1), 0.095, 0xff000000);
		swprintf(Text, L"%03d / %03d", (int)Player->m_Hp, (int)Player->m_MaxHp);
		IMAGE->CenterRenderTextView(Text, 32, Vec2(1720, 315), Vec2(1, 1), 0.08, false);

		Rect.left = 350 - Clamp((Player->m_Exp / Player->m_MaxExp) * 350, 0, 350);
		IMAGE->CenterRenderRectView(IMAGE->Find("Gauge"), Vec2(1720 + Rect.left, 360), 0, Vec2(1, -1), 0.09, Rect, 0xffffff00);
		IMAGE->CenterRenderView(IMAGE->Find("Gauge"), Vec2(1720, 360), 0, Vec2(1, -1), 0.095, 0xff000000);
		swprintf(Text, L"%04d / %04d", (int)Player->m_Exp, (int)Player->m_MaxExp);
		IMAGE->CenterRenderTextView(Text, 32, Vec2(1720, 345), Vec2(1, 1), 0.08, false, 0xff00ff00);

		swprintf(Text, L"Lv.%d", Player->m_Level);
		IMAGE->CenterRenderTextView(Text, 32, Vec2(1720, 270), Vec2(2, 2), 0.09, false, 0xff00ff00);

		swprintf(Text, L"SCORE   %012d", (int)m_Score);
		IMAGE->CenterRenderTextView(Text, 32, Vec2(1720, 50), Vec2(1, 1), 0.09, false);

		Rect.left = Rect.top = 0;
		Rect.right = 128;
		if (Player->m_Level >= 3)
		{
			Rect.bottom = Clamp(128 - (float)Player->m_Owner->m_Alarm[1] / (15 * 60) * 128, 0, 128);
			IMAGE->CenterRenderRectView(IMAGE->Find("Skill1"), Vec2(75, 100), 0, Vec2(1, 1), 0.09, Rect);
		}
		IMAGE->CenterRenderView(IMAGE->Find("Skill1"), Vec2(75, 100), 0, Vec2(1, 1), 0.095, 0xffff0000);
		if (Player->m_Level >= 5)
		{
			Rect.bottom = Clamp(128 - (float)Player->m_Owner->m_Alarm[2] / (60 * 60) * 128, 0, 128);
			IMAGE->CenterRenderRectView(IMAGE->Find("Skill2"), Vec2(250, 100), 0, Vec2(1, 1), 0.09, Rect);
		}
		IMAGE->CenterRenderView(IMAGE->Find("Skill2"), Vec2(250, 100), 0, Vec2(1, 1), 0.095, 0xffff0000);

		if (INPUT->KeyPress(VK_F7))
		{
			int Exp = Player->m_Exp;
			for (int i = 1; i < min(Player->m_Level, 4); i++)
			{
				Exp += i * 1000;
			}
			swprintf(Text, L"Exp: %d\nLv.2 - 1000\nLv.3 - 2000\nLv.4 - 6000\nLv.5 - 10000", Exp);
			IMAGE->CenterRenderTextView(Text, 32, Vec2(1720, 700), Vec2(1, 1), 0.09, false);
		}

		swprintf(Text, L"Reflected: %d", m_Reflected);
		IMAGE->RenderTextView(Text, 32, Vec2(50, 270), Vec2(1, 1), 0.09, false);
		swprintf(Text, L"x%d", m_ScoreItem);
		IMAGE->RenderView(IMAGE->Find("Item_Score"), Vec2(50, 340), 0, Vec2(3, 3), 0.09);
		IMAGE->RenderTextView(Text, 32, Vec2(110, 350), Vec2(1, 1), 0.09, false);
	}
}

void cSystemManager::Release()
{
}

void cSystemManager::SortRank()
{
	m_Rank.sort([&](RankData Prev, RankData Next)->bool {return Prev.Score > Next.Score; });
}

void cSystemManager::PlayerInit()
{
	m_Score = 0;
	m_Level = 1;
	m_Exp = 0;
	m_Win = false;
	m_ScoreItem = 0;
	m_Reflected = 0;
}

void cSystemManager::OnSceneChange()
{
	OBJECT->Release();
	PART->Release();
	CAMERA->Init();
	for (int i = 0; i < 4; i++)
	{
		m_Alarm[i] = -100;
	}
}
