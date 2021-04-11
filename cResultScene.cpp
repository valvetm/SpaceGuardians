#include "DXUT.h"
#include "cResultScene.h"


cResultScene::cResultScene()
{
}


cResultScene::~cResultScene()
{
}

void cResultScene::Init()
{
	m_OnTyping = true;
	m_Name.clear();

	cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Back1"), Vec2(0, 0), Vec2(1, 1), 0, 0.1, 0xff000000);
	Part->SetAlpha(255, -4, 1);

	if (SYSTEM->m_Win)
	{
		SOUND->Play("Win", -500);
	}
	else
	{
		SOUND->Play("Lose", -500);
	}
}

void cResultScene::Update()
{
	if (m_OnTyping)
	{
		if (m_Name.size() < 3)
		{
			for (int i = 65; i <= 90; i++)
			{
				if (INPUT->KeyDown(i))
				{
					m_Name.push_back(i);
					break;
				}
			}
		}
		else
		{
			if (INPUT->KeyDown(VK_RETURN))
			{
				SYSTEM->m_Rank.push_back(RankData{ m_Name, (int)SYSTEM->m_Score });
				SYSTEM->SortRank();
				m_OnTyping = false;
			}
		}

		if (m_Name.size() != 0)
		{
			if (INPUT->KeyDown(VK_BACK))
			{
				m_Name.pop_back();
			}
		}
	}
	else
	{
		if (INPUT->KeyDown(VK_RETURN) || INPUT->KeyDown('Z'))
		{
			cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Back1"), Vec2(0, 0), Vec2(1, 1), 0, 0.1, 0x00000000);
			Part->SetAlpha(0, 5, 1);
			SYSTEM->m_Alarm[3] = 60;
		}
	}
}

void cResultScene::Render()
{
	if (SYSTEM->m_Win)
	{
		IMAGE->Render(IMAGE->Find("Back_Win"), Vec2(0, 0), 0, Vec2(1, 1), 0.9);
	}
	else
	{
		IMAGE->Render(IMAGE->Find("Back_Lose"), Vec2(0, 0), 0, Vec2(1, 1), 0.9);
	}

	TCHAR Text[64];
	IMAGE->CenterRenderText(L"YOUR SCORE:", 32, Vec2(960, 100), Vec2(3, 3), 0.5, false);
	swprintf(Text, L"%d", (int)SYSTEM->m_Score);
	IMAGE->CenterRenderText(Text, 32, Vec2(960, 200), Vec2(4, 4), 0.5, false);

	IMAGE->CenterRenderText(L"Enter your name.", 32, Vec2(960, 300), Vec2(2, 2), 0.5, false);

	for (int i = 0; i < 3; i++)
	{
		IMAGE->CenterRenderText(L"_", 32, Vec2(860 + i * 100, 410), Vec2(4, 4), 0.5, false);
	}
	for (int i = 0; i < m_Name.size(); i++)
	{
		swprintf(Text, L"%c", m_Name[i]);
		IMAGE->CenterRenderText(Text, 32, Vec2(860 + i * 100, 400), Vec2(4, 4), 0.5, false);
	}

	auto iter = SYSTEM->m_Rank.begin();
	for (int i = 0; i < 10; i++)
	{
		swprintf(Text, L"%d", iter->Score);
		IMAGE->RenderText(iter->Name, 32, Vec2(700, 500 + i * 50), Vec2(2, 2), 0.5, false);
		IMAGE->RenderText(Text, 32, Vec2(960, 500 + i * 50), Vec2(2, 2), 0.5, false);
		iter++;
	}
}

void cResultScene::Release()
{
}
