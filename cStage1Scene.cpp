#include "DXUT.h"
#include "cStage1Scene.h"
#include "cTimeLine_Zako1.h"
#include "cTimeLine_Zako2.h"
#include "cTimeLine_Zako3.h"
#include "cTimeLine_Zako4.h"
#include "cPlayer.h"
#include "cMidBoss1.h"
#include "cBoss1.h"
#include "cTimeLine_MidBoss12.h"

cStage1Scene::cStage1Scene()
{
}


cStage1Scene::~cStage1Scene()
{
}

void cStage1Scene::Init()
{
	m_BackSpeed = 4;
	m_BackEnd = 4;
	m_BackVel = 0;
	m_BackPos = 0;
	m_Time = 0;

	OBJECT->AddObject("Player", Vec2(960, 700), 0.5, Obj_Player)->AddComponent<cPlayer>();

	cObject* a;
	for (int i = 0; i < 4; i++)
	{
		a = OBJECT->AddObject("Mission", Vec2(200, 600 + 50 * i), 0.09, Obj_None);
		m_Missions[i] = a->AddComponent<cMission>();
	}
	m_Missions[0]->m_OnGoing = true;
	m_Missions[0]->m_Text = L"적들을 처치하고 진행하십시오.";
	m_Missions[1]->m_Text = L"중간 보스를 격퇴하십시오.";
	m_Missions[2]->m_Text = L"중간 보스를 추격하십시오.";
	m_Missions[3]->m_Text = L"최종 보스를 처치하십시오.";

	cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Back1"), Vec2(960, 540), Vec2(1, 1), 0, 0.01, 0xff000000);
	Part->SetAlpha(255, -2, 1);

	cParticleText* Text = PART->AddParticle<cParticleText>(NULL, Vec2(960, 250), Vec2(4, 4), 0, 0, 0xffff0000);
	Text->SetScale(Vec2(0, -0.03), 1);
	Text->m_Size = 32;
	Text->m_Text = L"STAGE 1";
}

void cStage1Scene::Update()
{
	cObject* a;
	m_Time++;
	switch (m_Time)
	{
	case 300:
	case 330:
	case 360:
	case 390:
	case 420:
	case 450:
	case 480:
	case 510:
	case 540:
	case 570:
	case 600:
		for (int i = -1; i <= 1; i += 2)
		{
			a = AddZako<cTimeLine_Zako1>("Zako1", Vec2(960 + 600 * i, 600), 15, 40);
			AddPath(a, 5, 1, Vec2(960 + 100 * i, -200), Vec2(960, 600));
		}
		break;

	case 900:
		for (int i = -1; i <= 1; i += 2)
		{
			a = OBJECT->AddObject("Zako10", Vec2(960 + 500 * i, -50), 0.6, Obj_None);
			a->AddComponent<cPath>()->AddPath(2, 1, Vec2(960 + 500 * i, 1300));
			a->AddComponent<cTimeLine_Zako2>()->m_Dir = i;
			a->AddComponent<cRenderer>()->m_Image = IMAGE->Find("Zako10");
		}
		break;

	case 1000:
		for (int i = -1; i <= 1; i += 2)
		{
			a = AddZako<cTimeLine_Zako3>("Zako6", Vec2(960 + 450 * i, -50), 600, 150);
			AddPath(a, 2, 1, Vec2(960 + 450 * i, 1300));
		}
		break;

	case 1800:
	case 1830:
	case 1860:
	case 1890:
	case 1920:
	case 1950:
	case 1980:
	case 2010:
	case 2040:
	case 2070:
	case 2100:
		for (int i = -1; i <= 1; i += 2)
		{
			a = AddZako<cTimeLine_Zako4>("Zako2", Vec2(960 + 600 * i, Random(0, 500)), 40, 50);
			AddPath(a, 5, 1, Vec2(960 - 700 * i, Random(0, 500)), Vec2(Random(400, 1520), Random(0, 500)));
		}
		break;

	case 2400:
		m_Missions[0]->m_Cleared = true;
		m_Missions[1]->m_OnGoing = true;
	case 2475:
	case 2550:
	{
		cParticleText* Text = PART->AddParticle<cParticleText>(NULL, Vec2(960, 250), Vec2(4, 4), 0, 0.3, 0xffff0000);
		Text->m_Size = 32;
		Text->m_Text = L"WARNING!!";
		Text->SetAlpha(255, -3, 1);
		CAMERA->Shake(30, 80);
	}
	break;

	case 2700:
		a = OBJECT->AddObject("Boss", Vec2(960, -300), 0.6, Obj_Enemy);
		a->AddComponent<cMidBoss1>();
		m_BackVel = -0.02;
		break;

	case 3300:
		a = OBJECT->AddObject("Boss", Vec2(960, -300), 0.6, Obj_None);
		a->AddComponent<cRenderer>()->m_Image = IMAGE->Find("Boss11");
		a->AddComponent<cPath>()->AddPath(6, 0.99, Vec2(960, 100));
		a->AddComponent<cTimeLine_MidBoss12>();
		a->m_Rot = 90;
		break;

	case 3500:
		m_AsteroidPos = 9;
		break;

	case 4200:
		for (auto& iter : OBJECT->m_Objects[Obj_None])
		{
			if (iter->m_Name == "Boss")
			{
				iter->GetComponent<cPath>()->AddPath(1, 1.01, Vec2(iter->m_Pos.x, -200));
			}
		}
		break;

	case 4400:
		m_Missions[2]->m_Cleared = true;
		m_Missions[3]->m_OnGoing = true;
	case 4475:
	case 4550:
	{
		cParticleText* Text = PART->AddParticle<cParticleText>(NULL, Vec2(960, 250), Vec2(4, 4), 0, 0.3, 0xffff0000);
		Text->m_Size = 32;
		Text->m_Text = L"WARNING!!";
		Text->SetAlpha(255, -3, 1);
		CAMERA->Shake(30, 80);
	}
	break;

	case 4700:
		a = OBJECT->AddObject("Boss", Vec2(960, -300), 0.6, Obj_Enemy);
		a->AddComponent<cBoss1>();
		m_BackVel = -0.05;
		break;


	}

	if (m_Time >= 3500 && m_Time <= 4100 && m_Time % 10 == 0)
	{
		int Rand = Random(-2, 2);
		for (auto& iter : OBJECT->m_Objects[Obj_None])
		{
			if (iter->m_Name == "Boss")
			{
				iter->GetComponent<cPath>()->AddPath(abs(6.4 * Rand), 1, Vec2(384 + m_AsteroidPos * 64, 100));
				CAMERA->Shake(5, 30);
				cParticle* Part;
				char Text[16];
				for (int i = 0; i < 20; i++)
				{
					sprintf(Text, "Asteroid%d", Random(1, 6));
					Part = PART->AddParticle<cParticle>(IMAGE->Find(Text), iter->m_Pos + Vec2(Random(-200, 200), Random(-50, -100)), Vec2(0.3, 0.3) * Random(0.75f, 1.25f), Random(0, 359), 0.51);
					Part->SetSpeed(Random(2.f, 7.f), 0.97, Random(0, 359));
					Part->SetRot(Random(-25, 25), 0.97);
					Part->SetScale(Vec2(-0.001, -0.001), 1.02);
				}
			}
		}
		AddAsteroid(0, m_AsteroidPos - 3, 0, 1, 12.8);
		AddAsteroid(m_AsteroidPos + 3, 18, 0, 1, 12.8);
		m_AsteroidPos += Rand;
		if (m_AsteroidPos < 3)
			m_AsteroidPos = 3;
		if (m_AsteroidPos > 15)
			m_AsteroidPos = 15;
	}
	if (m_Time >= 3500 && m_Time <= 4100 && m_Time % 30 == 0)
	{
		char Text[16];
		sprintf(Text, "Asteroid%d", Random(1, 5));
		SOUND->Play(Text, -500);
	}

	m_BackSpeed += m_BackVel;
	if (m_BackEnd <= m_BackSpeed)
	{
		m_BackSpeed = m_BackEnd;
		m_BackVel = 0;
	}
	if (m_BackSpeed <= 0)
	{
		m_BackSpeed = 0;
		m_BackVel = 0;
	}

	m_BackPos += m_BackSpeed;
	if (m_BackPos >= 2048)
	{
		m_BackPos -= 2048;
	}

	if (Random(0, 300) == 0 && m_BackSpeed != 0)
	{
		char Text[16];
		float Dist = Random(0.1f, 0.5f);
		sprintf(Text, "Nebula%d", Random(1, 3));
		cParticleFunc* Func = PART->AddParticle<cParticleFunc>(IMAGE->Find(Text), Vec2(Random(200, 1720), -500), Vec2(1, 1) * Dist, Random(0, 359), 0.8 + Dist * 0.1);
		Func->m_Alpha = 400 * Dist;
		Func->m_Func = [&](cParticleFunc* _Part)->void {
			_Part->m_Pos.y += m_BackSpeed * _Part->m_Scale.x;
			if (_Part->m_Pos.y >= 1600)
			{
				_Part->m_Alpha = 0;
			}
		};
	}
}

void cStage1Scene::Render()
{
	IMAGE->RenderView(IMAGE->Find("SideBar"), Vec2(0, 0), 0, Vec2(1, 1), 0.1);
	IMAGE->RenderView(IMAGE->Find("SideBar"), Vec2(1920, 0), 0, Vec2(-1, 1), 0.1);

	IMAGE->Render(IMAGE->Find("Back1"), Vec2(0, m_BackPos), 0, Vec2(0.5, 0.5), 0.9);
	IMAGE->Render(IMAGE->Find("Back1"), Vec2(0, m_BackPos - 2048), 0, Vec2(0.5, 0.5), 0.9);
}

void cStage1Scene::Release()
{
}
