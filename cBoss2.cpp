#include "DXUT.h"
#include "cBoss2.h"
#include "cBoss2Tail.h"
#include "cTimeLine_Boss21.h"
#include "cTimeLine_Boss22.h"
#include "cTimeLine_Boss23.h"
#include "cTimeLine_Boss24.h"
#include "cStage2Scene.h"

cBoss2::cBoss2()
{
}


cBoss2::~cBoss2()
{
}

void cBoss2::Init()
{
	AddComponent<cPath>()->AddPath(8, 0.99, Vec2(960, 300));
	AddComponent<cRenderer>()->m_Image = IMAGE->Find("Boss31");
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
	m_MaxHp = 17500;
	m_Exp = 1500;
	m_Start = false;
	m_Owner->m_Rot = 90;
	m_Phase = 1;

	m_Owner->SetAlarmSize(3);
	m_Owner->SetAlarm(2, 200);
	m_Owner->m_AlarmFunc = [&](int _Index)->void {
		switch (_Index)
		{
		case 0:
			GetComponent<cRenderer>()->m_Color = 0xffffffff;
			break;

		case 1:
			AddComponent<cTimeLine_Boss22>();
			m_Phase++;
			break;

		case 2:
			CAMERA->MoveTo(Vec2(960, 540), 6, 0.99, 1);
			break;
		}
	};

	cObject* a;
	cObject* Prev;
	for (int i = 0; i < 10; i++)
	{
		a = OBJECT->AddObject("Tail", Vec2(0, 0), 0.61, Obj_Enemy);
		a->AddComponent<cBoss2Tail>()->m_Index = i;
		a->GetComponent<cBoss2Tail>()->m_Hp = 4000 - 410 * i;
		a->GetComponent<cBoss2Tail>()->m_Head = m_Owner;
		a->m_Scale = Vec2(1 - i * 0.05, 1 - i * 0.05);
		if (i == 0)
		{
			a->GetComponent<cBoss2Tail>()->m_Prev = m_Owner;
			m_Next = a;
		}
		else
		{
			a->GetComponent<cBoss2Tail>()->m_Prev = Prev;
			Prev->GetComponent<cBoss2Tail>()->m_Next = a;
		}
		Prev = a;
	}
}

void cBoss2::Update()
{
	if (!m_Start)
	{
		m_Hp += m_MaxHp / 60 / 5;
		if (m_Hp >= m_MaxHp)
		{
			m_Start = true;
			GetComponent<cCollider>()->AddCollider(Vec2(-25, 0), 90);
			GetComponent<cCollider>()->AddCollider(Vec2(25, 0), 90);
			AddComponent<cTimeLine_Boss21>();
			cObject* Next = m_Next;
			while (Next != nullptr)
			{
				Next->AddComponent<cTimeLine_Boss23>();
				Next->GetComponent<cCollider>()->AddCollider(Vec2(0, -35) * Next->m_Scale.x, 50 * Next->m_Scale.x);
				Next->GetComponent<cCollider>()->AddCollider(Vec2(0, 35) * Next->m_Scale.x, 50 * Next->m_Scale.x);
				Next = Next->GetComponent<cBoss2Tail>()->m_Next;
			}
		}
	}
	else
	{
		if (m_Hp <= 8750 && m_Phase == 1)
		{
			m_Phase++;
			GetComponent<cPath>()->m_Points.clear();
			GetComponent<cPath>()->m_Speed = 0;
			GetComponent<cTimeLine_Boss21>()->m_Enable = false;
			m_Owner->SetAlarm(1, 120);

			char Text[16];
			cParticleFunc* Func;
			for (int i = 0; i < 5; i++)
			{
				Vec2 Pos = m_Owner->m_Pos + RotateVec(Vec2(Random(-115, 115), Random(-90, 90)), m_Owner->m_Rot);
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
			sprintf(Text, "BossExplosion%d", Random(1, 5));
			SOUND->Play(Text, -500);
			CAMERA->Shake(30, 120);
		}

		if (m_Phase == 2)
		{
			for (auto& iter : OBJECT->m_Objects[Obj_EnemyBullet])
			{
				iter->m_Destroyed = true;
			}
		}

		if (m_Hp <= 0)
		{
			Death();
		}
	}
	if (m_Next != nullptr)
	{
		m_Next->m_Pos = m_Owner->m_Pos + RotateVec(Vec2(-80 * m_Owner->m_Scale.x, 0), m_Owner->m_Rot);
		int Dir = (int)(m_Owner->m_Rot - m_Next->m_Rot + 180) % 360 - 180;
		m_Next->m_Rot = Lerp<float>(m_Next->m_Rot, m_Owner->m_Rot + Dir, 0.075);
	}
}

void cBoss2::Render()
{
	if (m_Hp > 0)
	{
		IMAGE->CenterRenderTextView(L"STAGE2 - FINAL BOSS", 32, Vec2(960, 15), Vec2(1, 1), 0.2, false, 0xffff0000);
		IMAGE->RenderView(IMAGE->Find("BossHp"), Vec2(420, 50), 0, Vec2(m_Hp / m_MaxHp * 1080, 1), 0.2);
	}
}

void cBoss2::Release()
{
}

void cBoss2::Death()
{
	for (auto& iter : OBJECT->m_Objects[Obj_EnemyBullet])
	{
		iter->m_Destroyed = true;
	}

	int Count = 0;
	cObject* Next = m_Next;
	while (Next != nullptr)
	{
		Count++;
		Next = Next->GetComponent<cBoss2Tail>()->m_Next;
	}

	cParticleFunc* Func;
	char Text[16];

	m_Owner->m_Destroyed = true;
	GetComponent<cTimeLine_Boss22>()->m_Enable = false;
	OBJECT->m_Player->GetComponent<cPlayer>()->AddExp(m_Exp, m_Owner->m_Pos);
	cStage2Scene* Scene = static_cast<cStage2Scene*>(SCENE->m_Cur);
	Scene->m_Missions[3]->m_Cleared = true;
	SYSTEM->m_Win = true;

	Func = PART->AddParticle<cParticleFunc>(GetComponent<cRenderer>()->m_Image, m_Owner->m_Pos, m_Owner->m_Scale, m_Owner->m_Rot, 0.65);
	Func->SetAlpha(1060 + Count * 60, -1, 1);
	Func->m_Func = [](cParticleFunc* _Part)->void {
		if (_Part->m_Alpha == 1000)
		{
			CAMERA->MoveTo(_Part->m_Pos, 6, 0.99, 2);
		}

		if (_Part->m_Alpha >= 800)
		{
			if (Random(0, 30) == 0)
			{
				cParticleFunc* Func;
				char Text[16];
				Vec2 Pos = _Part->m_Pos + RotateVec(Vec2(Random(-100, 100), Random(-80, 80)), _Part->m_Rot);
				cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, Pos, Vec2(3, 3) * Random(0.75f, 1.25f), Random(0, 359), 0.5);
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
		if (_Part->m_Alpha == 800)
		{
			char Text[16];
			cParticleFunc* Func;
			for (int i = 0; i < 15; i++)
			{
				Vec2 Pos = _Part->m_Pos + RotateVec(Vec2(Random(-115, 115), Random(-90, 90)), _Part->m_Rot);
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
			Text->m_Text = L"STAGE 2 CLEAR!!";

			Text = PART->AddParticle<cParticleText>(NULL, Vec2(960, 300), Vec2(4, 4), 0, 0, 0xffff0000);
			Text->m_Size = 32;
			Text->m_Text = L"You've saved the world!!";

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

			SYSTEM->m_Alarm[2] = 240;
		}
	};

	Next = m_Next;
	while (Next != nullptr)
	{
		Next->m_Destroyed = true;
		OBJECT->m_Player->GetComponent<cPlayer>()->AddExp(100, m_Owner->m_Pos);
		Func = PART->AddParticle<cParticleFunc>(IMAGE->Find("Boss32"), Next->m_Pos, Next->m_Scale, Next->m_Rot, 0.66);
		Func->SetAlpha(255 + 60 * Count, -1, 1);
		Func->m_Func = [](cParticleFunc* _Part)->void {
			if (_Part->m_Alpha == 255)
			{
				char Text[16];
				cParticleFunc* Func;
				for (int i = 0; i < 5; i++)
				{
					Vec2 Pos = _Part->m_Pos + RotateVec(Vec2(Random(-50, 50), Random(-85, 85)) * _Part->m_Scale.x, _Part->m_Rot);
					cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, Pos, Vec2(2, 2) * Random(0.75f, 1.25f) * _Part->m_Scale.x, Random(0, 359), 0.5);
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
				sprintf(Text, "BossExplosion%d", Random(1, 5));
				SOUND->Play(Text, -500);
				CAMERA->Shake(30 * _Part->m_Scale.x, 50);
				_Part->m_Alpha = 0;
			}
		};
		Count--;
		Next = Next->GetComponent<cBoss2Tail>()->m_Next;
	}

	for (auto& iter : OBJECT->m_Objects[Obj_Enemy])
	{
		if (iter->m_Destroyed == false)
		{
			iter->GetComponent<cBoss2Tail>()->m_Hp = 0;
		}
	}

}
