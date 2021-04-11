#include "DXUT.h"
#include "cMidBoss2.h"
#include "cStage2Scene.h"
#include "cTimeLine_MidBoss21.h"
#include "cTimeLine_MidBoss22.h"

cMidBoss2::cMidBoss2()
{
}


cMidBoss2::~cMidBoss2()
{
}

void cMidBoss2::Init()
{
	AddComponent<cPath>()->AddPath(8, 0.99, Vec2(m_Owner->m_Pos.x, 250));
	AddComponent<cRenderer>()->m_Image = IMAGE->Find("Boss2");
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
	m_MaxHp = 3000;
	m_Exp = 1000;
	m_Start = false;
	m_Last = false;
	m_Owner->m_Rot = 90;

	m_Owner->SetAlarmSize(3);
	m_Owner->SetAlarm(2, 200);
	m_Owner->m_AlarmFunc = [&](int _Index)->void {
		switch (_Index)
		{
		case 0:
			GetComponent<cRenderer>()->m_Color = 0xffffffff;
			break;

		case 1:
			break;

		case 2:
			CAMERA->MoveTo(Vec2(960, 540), 6, 0.99, 1);
			break;
		}
	};
}

void cMidBoss2::Update()
{
	if (!m_Start)
	{
		m_Hp += m_MaxHp / 60 / 5;
		if (m_Hp >= m_MaxHp)
		{
			m_Start = true;
			GetComponent<cCollider>()->AddCollider(Vec2(0, 0), 70);
			GetComponent<cCollider>()->AddCollider(Vec2(-30, 0), 70);
			GetComponent<cCollider>()->AddCollider(Vec2(30, 0), 70);
			AddComponent<cTimeLine_MidBoss21>();
		}
	}
	else
	{
		if (m_Hp <= 0)
		{
			Death();
		}
	}
	cStage2Scene* Scene = static_cast<cStage2Scene*>(SCENE->m_Cur);
	Scene->m_Time = 2300;
}

void cMidBoss2::Render()
{
	if (m_Hp > 0)
	{
		IMAGE->CenterRenderTextView(L"STAGE2 - MIDDLE BOSS", 32, Vec2(960, 15), Vec2(1, 1), 0.2, false, 0xffff0000);
		IMAGE->RenderView(IMAGE->Find("BossHp"), Vec2(420 + 550 * m_Index, 50), 0, Vec2(m_Hp / m_MaxHp * 530, 1), 0.2);
	}
}

void cMidBoss2::Release()
{
}

void cMidBoss2::Death()
{
	for (auto& iter : OBJECT->m_Objects[Obj_EnemyBullet])
	{
		iter->m_Destroyed = true;
	}

	OBJECT->AddObject("Item_Hp", m_Owner->m_Pos, 0.4, Obj_Item)->AddComponent<cItem>();

	OBJECT->m_Player->GetComponent<cPlayer>()->AddExp(m_Exp, m_Owner->m_Pos);
	m_Owner->m_Destroyed = true;

	cParticleFunc* Func;
	char Text[16];

	if (m_Last)
	{
		cStage2Scene* Scene = static_cast<cStage2Scene*>(SCENE->m_Cur);
		Scene->m_Missions[1]->m_Cleared = true;
		Scene->m_Missions[2]->m_OnGoing = true;
		CAMERA->MoveTo(m_Owner->m_Pos, 6, 0.99, 2);

		GetComponent<cTimeLine_MidBoss21>()->m_Enable = false;
		GetComponent<cTimeLine_MidBoss22>()->m_Enable = false;

		Func = PART->AddParticle<cParticleFunc>(GetComponent<cRenderer>()->m_Image, m_Owner->m_Pos, m_Owner->m_Scale, m_Owner->m_Rot, 0.65);
		Func->SetAlpha(1000, -1, 1);
		Func->m_Func = [](cParticleFunc* _Part)->void {
			if (_Part->m_Alpha >= 800)
			{
				if (Random(0, 15) == 0)
				{
					cParticleFunc* Func;
					char Text[16];
					Vec2 Pos = _Part->m_Pos + RotateVec(Vec2(Random(-100, 100), Random(-70, 70)), _Part->m_Rot);
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
			if (_Part->m_Alpha == 800)
			{
				char Text[16];
				cParticleFunc* Func;
				for (int i = 0; i < 15; i++)
				{
					Vec2 Pos = _Part->m_Pos + RotateVec(Vec2(Random(-100, 100), Random(-70, 70)), _Part->m_Rot);
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
				cStage2Scene* Scene = static_cast<cStage2Scene*>(SCENE->m_Cur);
				Scene->m_BackEnd = 4;
				Scene->m_BackVel = 0.02;
			}
		};
	}
	else
	{
		GetComponent<cTimeLine_MidBoss21>()->m_Enable = false;
		for (auto& iter : OBJECT->m_Objects[Obj_Enemy])
		{
			if (iter != m_Owner)
			{
				iter->GetComponent<cMidBoss2>()->m_Last = true;
				iter->AddComponent<cTimeLine_MidBoss22>();
			}
		}

		Func = PART->AddParticle<cParticleFunc>(GetComponent<cRenderer>()->m_Image, m_Owner->m_Pos, m_Owner->m_Scale, m_Owner->m_Rot, 0.65);
		Func->SetAlpha(1000, -1, 1);
		Func->m_Func = [](cParticleFunc* _Part)->void {
			if (_Part->m_Alpha >= 800)
			{
				if (Random(0, 15) == 0)
				{
					cParticleFunc* Func;
					char Text[16];
					Vec2 Pos = _Part->m_Pos + RotateVec(Vec2(Random(-100, 100), Random(-70, 70)), _Part->m_Rot);
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
					CAMERA->Shake(5, 30);
				}
			}
			if (_Part->m_Alpha == 800)
			{
				char Text[16];
				cParticleFunc* Func;
				for (int i = 0; i < 15; i++)
				{
					Vec2 Pos = _Part->m_Pos + RotateVec(Vec2(Random(-100, 100), Random(-70, 70)), _Part->m_Rot);
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
				CAMERA->Shake(15, 60);
				_Part->m_Pos = Vec2(0, 0);
			}
		};
	}
}
