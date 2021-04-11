#include "DXUT.h"
#include "cStage2Scene.h"
#include "cTimeLine_Zako5.h"
#include "cTimeLine_Zako6.h"
#include "cTimeLine_Zako7.h"
#include "cTimeLine_Zako8.h"
#include "cTimeLine_Zako9.h"
#include "cMidBoss2.h"
#include "cBoss2.h"

cStage2Scene::cStage2Scene()
{
}


cStage2Scene::~cStage2Scene()
{
}

void cStage2Scene::Init()
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
	m_Missions[1]->m_Text = L"중간 보스를 처치하십시오.";
	m_Missions[2]->m_Text = L"적들을 처치하고 진행하십시오.";
	m_Missions[3]->m_Text = L"최종 보스를 처치하십시오.";

	cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Back1"), Vec2(960, 540), Vec2(1, 1), 0, 0.01, 0xff000000);
	Part->SetAlpha(255, -2, 1);

	cParticleText* Text = PART->AddParticle<cParticleText>(NULL, Vec2(960, 250), Vec2(4, 4), 0, 0, 0xffff0000);
	Text->SetScale(Vec2(0, -0.03), 1);
	Text->m_Size = 32;
	Text->m_Text = L"STAGE 2";
}

void cStage2Scene::Update()
{
	cObject* a;
	m_Time++;
	switch (m_Time)
	{
	case 300:
		a = OBJECT->AddObject("Zako10", Vec2(960, -100), 0.6, Obj_None);
		a->AddComponent<cRenderer>()->m_Image = IMAGE->Find("Zako10");
		a->AddComponent<cPath>()->AddPath(6, 0.99, Vec2(960, 250));
		a->AddComponent<cTimeLine_Zako5>();
		break;

	case 1300:
	case 1330:
	case 1360:
	case 1390:
	case 1420:
	case 1450:
	case 1480:
	case 1510:
	case 1540:
	case 1570:
	case 1600:
		for (int i = -1; i <= 1; i += 2)
		{
			a = AddZako<cTimeLine_Zako6>("Zako2", Vec2(960 + 600 * i, 600), 50, 50);
			AddPath(a, 5, 1, Vec2(960 + 100 * i, -200), Vec2(960, 600));
		}
		break;

	case 1900:
		m_Missions[0]->m_Cleared = true;
		m_Missions[1]->m_OnGoing = true;
	case 1975:
	case 2050:
	{
		cParticleText* Text = PART->AddParticle<cParticleText>(NULL, Vec2(960, 250), Vec2(4, 4), 0, 0.3, 0xffff0000);
		Text->m_Size = 32;
		Text->m_Text = L"WARNING!!";
		Text->SetAlpha(255, -3, 1);
		CAMERA->Shake(30, 80);
	}
	break;

	case 2200:
		for (int i = -1; i <= 1; i += 2)
		{
			a = OBJECT->AddObject("Boss", Vec2(960 + 200 * i, -300), 0.6, Obj_Enemy);
			a->AddComponent<cMidBoss2>()->m_Index = (i == -1 ? 0 : 1);
		}
		m_BackVel = -0.02;
	break;

	case 2700:
	case 2850:
	case 3000:
		for (int i = -1; i <= 1; i += 2)
		{
			a = AddZako<cTimeLine_Zako7>("Zako8", Vec2(960 + 100 * i, -50), 300, 150);
			AddPath(a, 4, 1, Vec2(960 + 700 * i, 600), Vec2(960, 600));
		}
		break;

	case 2740:
	case 2780:
	case 2820:
	case 2860:
	case 2900:
	case 2940:
	case 2980:
		for (int i = -1; i <= 1; i += 2)
		{
			a = AddZako<cTimeLine_Zako6>("Zako1", Vec2(960 + 600 * i, 600), 20, 50);
			AddPath(a, 7, 1, Vec2(960 + 100 * i, -200), Vec2(960, 600));
		}
		break;

	case 3350:
		for (int i = -1; i <= 1; i++)
		{
			a = AddZako<cTimeLine_Zako8>("Zako9", Vec2(960 + 300 * i, 1130), 500, 250);
			AddPath(a, 1, 1.01, Vec2(a->m_Pos.x, -300));
		}
		break;

	case 3700:
	case 3710:
	case 3720:
	case 3730:
	case 3740:
	case 3750:
	case 3760:
	case 3770:
	case 3780:
	case 3790:
	case 3800:
	case 3810:
	case 3820:
	case 3830:
	case 3840:
	case 3850:
	case 3860:
	case 3870:
	case 3880:
	case 3890:
	case 3900:
	case 3910:
	case 3920:
	case 3930:
	case 3940:
	case 3950:
	case 3960:
	case 3970:
	case 3980:
	case 3990:
	case 4000:
	case 4010:
	case 4020:
	case 4030:
	case 4040:
	case 4050:
	case 4060:
	case 4070:
	case 4080:
	case 4090:
	case 4100:
	case 4110:
	case 4120:
	case 4130:
	case 4140:
	case 4150:
	case 4160:
	case 4170:
	case 4180:
	case 4190:
	case 4200:
	{
		for (int i = 0; i < 2; i++)
		{
			int Start = Random(1, 4);
			switch (Start)
			{
			case 1:
				a = AddZako<cTimeLine_Zako9>("Zako1", Vec2(350, Random(0, 1080)), 10, 30);
				break;
			case 2:
				a = AddZako<cTimeLine_Zako9>("Zako1", Vec2(Random(400, 1520), -50), 10, 30);
				break;
			case 3:
				a = AddZako<cTimeLine_Zako9>("Zako1", Vec2(1570, Random(0, 1080)), 10, 30);
				break;
			case 4:
				a = AddZako<cTimeLine_Zako9>("Zako1", Vec2(Random(400, 1520), 1130), 10, 30);
				break;
			}

			int End;
			do
			{
				End = Random(1, 4);
			} while (End == Start);

			switch (End)
			{
			case 1:
				AddPath(a, 6, 1, Vec2(200, Random(0, 1080)));
				break;
			case 2:
				AddPath(a, 6, 1, Vec2(Random(400, 1520), -200));
				break;
			case 3:
				AddPath(a, 6, 1, Vec2(1720, Random(0, 1080)));
				break;
			case 4:
				AddPath(a, 6, 1, Vec2(Random(400, 1520), 1280));
				break;
			}
		}
	}
	break;

	case 4500:
		m_Missions[2]->m_Cleared = true;
		m_Missions[3]->m_OnGoing = true;
	case 4575:
	case 4650:
	{
		cParticleText* Text = PART->AddParticle<cParticleText>(NULL, Vec2(960, 250), Vec2(4, 4), 0, 0.3, 0xffff0000);
		Text->m_Size = 32;
		Text->m_Text = L"WARNING!!";
		Text->SetAlpha(255, -3, 1);
		CAMERA->Shake(30, 80);
	}
	break;

	case 4800:
		a = OBJECT->AddObject("Boss", Vec2(960, -300), 0.6, Obj_Enemy);
		a->AddComponent<cBoss2>();
		m_BackVel = -0.02;
		break;

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
	if (m_BackPos >= 2600)
	{
		m_BackPos -= 2600;
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

void cStage2Scene::Render()
{
	IMAGE->RenderView(IMAGE->Find("SideBar"), Vec2(0, 0), 0, Vec2(1, 1), 0.1);
	IMAGE->RenderView(IMAGE->Find("SideBar"), Vec2(1920, 0), 0, Vec2(-1, 1), 0.1);

	IMAGE->Render(IMAGE->Find("Back2"), Vec2(100, m_BackPos), 0, Vec2(1, 1), 0.9);
	IMAGE->Render(IMAGE->Find("Back2"), Vec2(100, m_BackPos - 2600), 0, Vec2(1, 1), 0.9);
}

void cStage2Scene::Release()
{
}
