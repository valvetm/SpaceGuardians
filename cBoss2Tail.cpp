#include "DXUT.h"
#include "cBoss2Tail.h"
#include "cTimeLine_Boss23.h"
#include "cTimeLine_Boss24.h"
#include "cBoss2.h"

cBoss2Tail::cBoss2Tail()
{
}


cBoss2Tail::~cBoss2Tail()
{
}

void cBoss2Tail::Init()
{
	AddComponent<cPath>();
	AddComponent<cRenderer>()->m_Image = IMAGE->Find("Boss32");
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
	m_Hp = 2500;
	m_Exp = 100;
	m_Owner->m_Rot = 90;
	m_Prev = m_Next = nullptr;

	m_Owner->SetAlarmSize(1);
	m_Owner->m_AlarmFunc = [&](int _Index)->void {
		switch (_Index)
		{
		case 0:
			GetComponent<cRenderer>()->m_Color = 0xffffffff;
			break;
		}
	};
}

void cBoss2Tail::Update()
{
	if (m_Next != nullptr)
	{
		m_Next->m_Pos = m_Owner->m_Pos + RotateVec(Vec2(-80 * m_Owner->m_Scale.x, 0), m_Owner->m_Rot);
		int Dir = (int)(m_Owner->m_Rot - m_Next->m_Rot + 180) % 360 - 180;
		m_Next->m_Rot = Lerp<float>(m_Next->m_Rot, m_Owner->m_Rot + Dir, 0.075);
	}

	if (m_Hp <= 0)
	{
		Death();
	}
}

void cBoss2Tail::Render()
{
}

void cBoss2Tail::Release()
{
}

void cBoss2Tail::Death()
{
	if (m_Prev != nullptr)
	{
		if (m_Prev->GetComponent<cBoss2>() != nullptr)
		{
			m_Prev->GetComponent<cBoss2>()->m_Next = nullptr;
		}
		else
		{
			m_Prev->GetComponent<cBoss2Tail>()->m_Next = nullptr;
		}
	}
	else
	{
		GetComponent<cTimeLine_Boss24>()->m_Enable = false;
	}
	if (m_Next != nullptr)
	{
		m_Next->GetComponent<cBoss2Tail>()->m_Prev = nullptr;
		m_Next->AddComponent<cTimeLine_Boss24>();
	}

	m_Owner->m_Destroyed = true;
	m_Owner->GetComponent<cTimeLine_Boss23>()->m_Enable = false;
	m_Head->GetComponent<cBoss2>()->m_Hp -= 1500;

	OBJECT->m_Player->GetComponent<cPlayer>()->AddExp(m_Exp, m_Owner->m_Pos);

	char Text[16];
	cParticleFunc* Func;
	for (int i = 0; i < 5; i++)
	{
		Vec2 Pos = m_Owner->m_Pos + RotateVec(Vec2(Random(-50, 50), Random(-85, 85)) * m_Owner->m_Scale.x, m_Owner->m_Rot);
		cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, Pos, Vec2(3, 3) * Random(0.75f, 1.25f) * m_Owner->m_Scale.x, Random(0, 359), 0.5);
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
	CAMERA->Shake(10, 30);
}
