#include "DXUT.h"
#include "cBoss1.h"
#include "cStage1Scene.h"
#include "cTimeLine_Boss11.h"
#include "cTimeLine_Boss12.h"
#include "cTimeLine_Boss13.h"

cBoss1::cBoss1()
{
}


cBoss1::~cBoss1()
{
}

void cBoss1::Init()
{
	AddComponent<cPath>()->AddPath(8, 0.99, Vec2(960, 300));
	AddComponent<cRenderer>()->m_Image = IMAGE->Find("Boss11");
	AddComponent<cCollider>()->m_CollFunc = [&](cObject* _Other)->void {
		m_Hp -= _Other->GetComponent<cBulletBase>()->m_Damage;
		_Other->m_Destroyed = true;
		GetComponent<cRenderer>()->m_Color = 0xffff0000;
		m_Owner->SetAlarm(0, 3);
		char Text[16];
		sprintf(Text, "Impact%d", Random(1, 4));
		SOUND->Play(Text, -1000);
	};
	GetComponent<cCollider>()->m_CollWith.push_back(Obj_PlayerBullet);

	CAMERA->MoveTo(Vec2(960, 250), 6, 0.99, 2);
	m_Hp = 0;
	m_MaxHp = 8000;
	m_Exp = 1500;
	m_Phase = 1;
	m_Start = false;
	m_Owner->m_Rot = 90;

	m_Owner->SetAlarmSize(3);
	m_Owner->SetAlarm(2, 270);
	m_Owner->m_AlarmFunc = [&](int _Index)->void {
		switch (_Index)
		{
		case 0:
			GetComponent<cRenderer>()->m_Color = 0xffffffff;
			break;

		case 1:
			switch (m_Phase)
			{
			case 2:
				AddComponent<cTimeLine_Boss12>();
				break;
			case 3:
				AddComponent<cTimeLine_Boss13>();
				break;
			}
			break;

		case 2:
			CAMERA->MoveTo(Vec2(960, 540), 6, 0.99, 1);
			break;
		}
	};

	cObject* a;
	for (int i = -1; i <= 1; i += 2)
	{
		a = OBJECT->AddObject("Part", Vec2(960 + 125 * i, -300), 0.59, Obj_None);
		a->AddComponent<cRenderer>()->m_Image = IMAGE->Find("Boss12");
		a->AddComponent<cPath>()->AddPath(5, 0.99, Vec2(960 + i * 110, 150));
		a->m_Rot = 90;
		a->m_Scale = Vec2(1, -i);
		m_Parts.push_back(a);
	}
}

void cBoss1::Update()
{
	if (!m_Start)
	{
		m_Hp += m_MaxHp / 60 / 6;
		if (m_Hp >= m_MaxHp)
		{
			m_Start = true;
			GetComponent<cCollider>()->AddCollider(Vec2(0, 0), 100);
			GetComponent<cCollider>()->AddCollider(Vec2(-10, -100), 50);
			GetComponent<cCollider>()->AddCollider(Vec2(-10, 100), 50);
			GetComponent<cCollider>()->AddCollider(Vec2(-25, 150), 25);
			GetComponent<cCollider>()->AddCollider(Vec2(-25, 150), 25);
			AddComponent<cTimeLine_Boss11>();
		}
	}
	else
	{
		if (m_Hp <= 5000 && m_Phase == 1)
		{
			NextPhase();
			GetComponent<cTimeLine_Boss11>()->m_Enable = false;
			m_Owner->SetAlarm(1, 60);

			char Text[16];
			cParticleFunc* Func;
			for (int i = 0; i < 15; i++)
			{
				Vec2 Pos = m_Parts[0]->m_Pos + Vec2(Random(-70, 70), Random(-125, 125));
				cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, Pos, Vec2(4, 4) * Random(0.75f, 1.25f), Random(0, 359), 0.5);
				Anim->m_Anim = IMAGE->FindAnimation("Explosion");
				Anim->m_AnimSpeed = Random(1, 6);
				for (int i = 0; i < 7; i++)
				{
					sprintf(Text, "Debris%d", Random(1, 6));
					Func = PART->AddParticle<cParticleFunc>(IMAGE->Find(Text), Pos, Vec2(0.6, 0.6) * Random(0.75f, 1.25f), Random(0, 359), 0.51);
					Func->SetSpeed(Random(2.f, 7.f), 0.97, Random(0, 359));
					Func->SetRot(Random(-25, 25), 0.97);
					Func->SetScale(Vec2(-0.001, -0.001), 1.04);
					Func->m_Func = [](cParticleFunc* _Part)->void {
						char Text[16];
						sprintf(Text, "Smoke%d", Random(1, 3));
						cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find(Text), _Part->m_Pos, Vec2(0.25, 0.25) * _Part->m_Scale.x, Random(0, 359), 0.505, 0xff909090);
						Part->SetScale(Vec2(-0.003, -0.003), 1);
						Part->SetAlpha(255, -4, 1);
					};
				}
			}
			cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Ring"), m_Parts[0]->m_Pos, Vec2(0.1, 0.1), 0, 0.4);
			Part->SetScale(Vec2(0.2, 0.2), 0.98);
			Part->SetAlpha(255, -1, 1.1);
			sprintf(Text, "BossExplosion%d", Random(1, 5));
			SOUND->Play(Text, -500);
			CAMERA->Shake(15, 60);
			m_Parts[0]->m_Destroyed = true;
			m_Parts[0] = nullptr;
			
		}
		if (m_Hp <= 2500 && m_Phase == 2)
		{
			NextPhase();
			GetComponent<cTimeLine_Boss12>()->m_Enable = false;
			m_Owner->SetAlarm(1, 60);

			char Text[16];
			cParticleFunc* Func;
			for (int i = 0; i < 15; i++)
			{
				Vec2 Pos = m_Parts[1]->m_Pos + Vec2(Random(-70, 70), Random(-125, 125));
				cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, Pos, Vec2(4, 4) * Random(0.75f, 1.25f), Random(0, 359), 0.5);
				Anim->m_Anim = IMAGE->FindAnimation("Explosion");
				Anim->m_AnimSpeed = Random(1, 6);
				for (int i = 0; i < 7; i++)
				{
					sprintf(Text, "Debris%d", Random(1, 6));
					Func = PART->AddParticle<cParticleFunc>(IMAGE->Find(Text), Pos, Vec2(0.6, 0.6) * Random(0.75f, 1.25f), Random(0, 359), 0.51);
					Func->SetSpeed(Random(2.f, 7.f), 0.97, Random(0, 359));
					Func->SetRot(Random(-25, 25), 0.97);
					Func->SetScale(Vec2(-0.001, -0.001), 1.04);
					Func->m_Func = [](cParticleFunc* _Part)->void {
						char Text[16];
						sprintf(Text, "Smoke%d", Random(1, 3));
						cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find(Text), _Part->m_Pos, Vec2(0.25, 0.25) * _Part->m_Scale.x, Random(0, 359), 0.505, 0xff909090);
						Part->SetScale(Vec2(-0.003, -0.003), 1);
						Part->SetAlpha(255, -4, 1);
					};
				}
			}
			cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Ring"), m_Parts[1]->m_Pos, Vec2(0.1, 0.1), 0, 0.4);
			Part->SetScale(Vec2(0.2, 0.2), 0.98);
			Part->SetAlpha(255, -1, 1.1);
			sprintf(Text, "BossExplosion%d", Random(1, 5));
			SOUND->Play(Text, -500);
			CAMERA->Shake(15, 60);
			m_Parts[1]->m_Destroyed = true;
			m_Parts[1] = nullptr;
		}
		if (m_Hp <= 0)
		{
			Death();
		}

		for (auto& iter : m_Parts)
		{
			if (iter != nullptr)
			{
				iter->GetComponent<cRenderer>()->m_Color = GetComponent<cRenderer>()->m_Color;
			}
		}
	}
}

void cBoss1::Render()
{
	if (m_Hp > 0)
	{
		IMAGE->CenterRenderTextView(L"STAGE1 - FINAL BOSS", 32, Vec2(960, 15), Vec2(1, 1), 0.2, false, 0xffff0000);
		IMAGE->RenderView(IMAGE->Find("BossHp"), Vec2(420, 50), 0, Vec2(m_Hp / m_MaxHp * 1080, 1), 0.2);
	}
}

void cBoss1::Release()
{
}

void cBoss1::Death()
{
	GetComponent<cTimeLine_Boss13>()->m_Enable = false;

	cStage1Scene* Scene = static_cast<cStage1Scene*>(SCENE->m_Cur);
	Scene->m_Missions[3]->m_Cleared = true;

	for (auto& iter : OBJECT->m_Objects[Obj_EnemyBullet])
	{
		iter->m_Destroyed = true;
	}

	OBJECT->m_Player->GetComponent<cPlayer>()->AddExp(m_Exp, m_Owner->m_Pos);
	m_Owner->m_Destroyed = true;

	CAMERA->MoveTo(Vec2(960,250), 6, 0.99, 2);

	cParticleFunc* Func;
	Func = PART->AddParticle<cParticleFunc>(GetComponent<cRenderer>()->m_Image, m_Owner->m_Pos, m_Owner->m_Scale, m_Owner->m_Rot, 0.65);
	Func->SetAlpha(1000, -1, 1);
	Func->m_Func = [](cParticleFunc* _Part)->void {
		if (_Part->m_Alpha >= 800)
		{
			if (Random(0, 15) == 0)
			{
				cParticleFunc* Func;
				char Text[16];
				Vec2 Pos = _Part->m_Pos + Vec2(Random(-200, 200), Random(-110, 110));
				cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, Pos, Vec2(4, 4) * Random(0.75f, 1.25f), Random(0, 359), 0.5);
				Anim->m_Anim = IMAGE->FindAnimation("Explosion");
				Anim->m_AnimSpeed = Random(1, 6);
				for (int i = 0; i < 7; i++)
				{
					sprintf(Text, "Debris%d", Random(1, 6));
					Func = PART->AddParticle<cParticleFunc>(IMAGE->Find(Text), Pos, Vec2(0.6, 0.6) * Random(0.75f, 1.25f), Random(0, 359), 0.51);
					Func->SetSpeed(Random(2.f, 7.f), 0.97, Random(0, 359));
					Func->SetRot(Random(-25, 25), 0.97);
					Func->SetScale(Vec2(-0.001, -0.001), 1.04);
					Func->m_Func = [](cParticleFunc* _Part)->void {
						char Text[16];
						sprintf(Text, "Smoke%d", Random(1, 3));
						cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find(Text), _Part->m_Pos, Vec2(0.25, 0.25) * _Part->m_Scale.x, Random(0, 359), 0.505, 0xff909090);
						Part->SetScale(Vec2(-0.003, -0.003), 1);
						Part->SetAlpha(255, -4, 1);
					};
				}
				sprintf(Text, "Explosion%d", Random(1, 4));
				SOUND->Play(Text, -500);
				CAMERA->Shake(15, 30);
			}
		}
		if(_Part->m_Alpha == 800)
		{
			char Text[16];
			cParticleFunc* Func;
			for (int i = 0; i < 15; i++)
			{
				Vec2 Pos = _Part->m_Pos + Vec2(Random(-200, 200), Random(-110, 110));
				cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, Pos, Vec2(4, 4) * Random(0.75f, 1.25f), Random(0, 359), 0.5);
				Anim->m_Anim = IMAGE->FindAnimation("Explosion");
				Anim->m_AnimSpeed = Random(1, 6);
				for (int i = 0; i < 7; i++)
				{
					sprintf(Text, "Debris%d", Random(1, 6));
					Func = PART->AddParticle<cParticleFunc>(IMAGE->Find(Text), Pos, Vec2(0.6, 0.6) * Random(0.75f, 1.25f), Random(0, 359), 0.51);
					Func->SetSpeed(Random(2.f, 7.f), 0.97, Random(0, 359));
					Func->SetRot(Random(-25, 25), 0.97);
					Func->SetScale(Vec2(-0.001, -0.001), 1.04);
					Func->m_Func = [](cParticleFunc* _Part)->void {
						char Text[16];
						sprintf(Text, "Smoke%d", Random(1, 3));
						cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find(Text), _Part->m_Pos, Vec2(0.25, 0.25) * _Part->m_Scale.x, Random(0, 359), 0.505, 0xff909090);
						Part->SetScale(Vec2(-0.003, -0.003), 1);
						Part->SetAlpha(255, -4, 1);
					};
				}
			}
			cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Ring"), _Part->m_Pos, Vec2(0.1, 0.1), 0, 0.4);
			Part->SetScale(Vec2(0.2, 0.2), 0.98);
			Part->SetAlpha(255, -1, 1.1);
			sprintf(Text, "BossExplosion%d", Random(1, 5));
			SOUND->Play(Text, -500);
			CAMERA->Shake(30, 180);
			_Part->m_Pos = Vec2(0, 0);
		}

		if (_Part->m_Alpha == 750)
		{
			CAMERA->MoveTo(Vec2(960, 540), 6, 0.99, 1);
			cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Player"), OBJECT->m_Player->m_Pos, Vec2(0.3, 0.3), 0, 0.5);
			Part->SetSpeed(1.1, 1.01, 270);
			OBJECT->m_Player->GetComponent<cPlayer>()->m_Dead = true;
			OBJECT->m_Player->m_Pos = Vec2(0, 0);
		}

		if (_Part->m_Alpha == 700)
		{
			cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Back1"), Vec2(960, 540), Vec2(1, 1), 0, 0.01, 0x00000000);
			Part->SetAlpha(0, 1, 1);
		}

		if (_Part->m_Alpha == 650)
		{
			TCHAR Score[64];
			cParticleText* Text = PART->AddParticle<cParticleText>(NULL, Vec2(960, 200), Vec2(4, 4), 0, 0, 0xffff0000);
			Text->m_Size = 32;
			Text->m_Text = L"STAGE 1 CLEAR!!";

			int Bonus = OBJECT->m_Player->GetComponent<cPlayer>()->m_Hp * 1000000;
			swprintf(Score, L"LIFE BONUS   %d", Bonus);
			Text = PART->AddParticle<cParticleText>(NULL, Vec2(960, 400), Vec2(3, 3), 0, 0);
			Text->m_Size = 32;
			Text->m_Text = Score;

			SYSTEM->m_Score += Bonus;
			swprintf(Score, L"TOTAL SCORE   %d", (int)SYSTEM->m_Score);
			Text = PART->AddParticle<cParticleText>(NULL, Vec2(960, 500), Vec2(3, 3), 0, 0);
			Text->m_Size = 32;
			Text->m_Text = Score;

			SYSTEM->m_Alarm[0] = 240;
		}
	};
}

void cBoss1::NextPhase()
{
	for (auto& iter : OBJECT->m_Objects[Obj_EnemyBullet])
	{
		iter->m_Destroyed = true;
	}
	m_Phase++;
}
