#include "DXUT.h"
#include "cTitleScene.h"


cTitleScene::cTitleScene()
{
}


cTitleScene::~cTitleScene()
{
}

void cTitleScene::Init()
{
	cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Back1"), Vec2(0, 0), Vec2(1, 1), 0, 0.01, 0xff000000);
	Part->SetAlpha(255, -4, 1);

	cObject* a = OBJECT->AddObject("Player", Vec2(960, 1500), 0.5, Obj_Player);
	a->AddComponent<cRenderer>()->m_Image = IMAGE->Find("Player");
	a->AddComponent<cPath>()->AddPath(10, 0.99, Vec2(960, 650));

	m_Selected = 0;
	m_OnTitle = true;
	SOUND->Play("Music", -750, true);
	SYSTEM->SortRank();

	m_Text[0] = L"START";
	m_Text[1] = L"HOW TO PLAY";
	m_Text[2] = L"RANKING";
	m_Text[3] = L"EXIT";

	m_Color[0] = 0xffffffff;
	m_Color[1] = 0x90ffffff;
	m_Color[2] = 0x90ffffff;
	m_Color[3] = 0x90ffffff;

	m_Scale[0] = Vec2(4, 4);
	m_Scale[1] = Vec2(3, 3);
	m_Scale[2] = Vec2(3, 3);
	m_Scale[3] = Vec2(3, 3);
}

void cTitleScene::Update()
{
	if (m_OnTitle)
	{
		if (INPUT->KeyDown(VK_UP))
		{
			m_Selected--;
			if (m_Selected == -1)
				m_Selected = 3;
		}
		if (INPUT->KeyDown(VK_DOWN))
		{
			m_Selected++;
			if (m_Selected == 4)
				m_Selected = 0;
		}

		if (INPUT->KeyDown('Z'))
		{
			m_OnTitle = false;
			switch (m_Selected)
			{
			case 0:
			{
				SYSTEM->m_Alarm[1] = 120;
				for (auto& iter : OBJECT->m_Objects[Obj_Player])
				{
					iter->GetComponent<cPath>()->AddPath(1, 1.02, Vec2(960, -1000));
				}
				cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Back1"), Vec2(0, 0), Vec2(1, 1), 0, 0.01, 0x00000000);
				Part->SetAlpha(0, 2.5, 1);
			}
			break;

			case 1:
				CAMERA->MoveTo(Vec2(960, 540 - 1080), 30, 0.98, 1);
				break;

			case 2:
				CAMERA->MoveTo(Vec2(960, 540 + 1080), 30, 0.98, 1);
				break;

			case 3:
				exit(0);
				break;
			}
		}
	}
	else
	{
		if (INPUT->KeyDown('X'))
		{
			m_OnTitle = true;
			CAMERA->MoveTo(Vec2(960, 540), 30, 0.98, 1);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (i == m_Selected)
		{
			m_Color[i] = 0xffffffff;
			m_Scale[i] = Lerp<Vec2>(m_Scale[i], Vec2(4, 4), 0.1);
		}
		else
		{
			m_Color[i] = 0x90ffffff;
			m_Scale[i] = Lerp<Vec2>(m_Scale[i], Vec2(3, 3), 0.1);
		}
	}
}

void cTitleScene::Render()
{
	for (int i = 0; i < 4; i++)
	{
		IMAGE->CenterRenderText(m_Text[i], 32, Vec2(400 + i * 25, 500 + i * 100), m_Scale[i], 0.5, false, m_Color[i]);
	}

	IMAGE->Render(IMAGE->Find("How"), Vec2(0, -1080), 0, Vec2(1, 1), 0.5);
	IMAGE->CenterRender(IMAGE->Find("Back_Title"), Vec2(960, 540), D3DXToRadian(90), Vec2(1.5, 1.5), 0.9);

	TCHAR Text[64];

	IMAGE->CenterRenderText(L"RANKING", 32, Vec2(960, 150 + 1080), Vec2(4, 4), 0.5, false, 0xffff0000);

	auto iter = SYSTEM->m_Rank.begin();
	for (int i = 0; i < 10; i++)
	{
		swprintf(Text, L"%d", iter->Score);
		IMAGE->RenderText(iter->Name, 32, Vec2(700, 300 + i * 60 + 1080), Vec2(2, 2), 0.5, false);
		IMAGE->RenderText(Text, 32, Vec2(950, 300 + i * 60 + 1080), Vec2(2, 2), 0.5, false);
		iter++;
	}
}

void cTitleScene::Release()
{
}
