#include "DXUT.h"
#include "cZako.h"


cZako::cZako()
{
}


cZako::~cZako()
{
}

void cZako::Init()
{
	AddComponent<cPath>();
	AddComponent<cRenderer>()->m_Image = IMAGE->Find(m_Owner->m_Name);
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

	if (m_Owner->m_Name == "Zako1" || m_Owner->m_Name == "Zako2" || m_Owner->m_Name == "Zako3")
	{
		GetComponent<cCollider>()->AddCollider(Vec2(0, 0), 40);
	}
	if (m_Owner->m_Name == "Zako4" || m_Owner->m_Name == "Zako5" || m_Owner->m_Name == "Zako6")
	{
		GetComponent<cCollider>()->AddCollider(Vec2(40, 0), 40);
		GetComponent<cCollider>()->AddCollider(Vec2(-40, 0), 40);
	}
	if (m_Owner->m_Name == "Zako7" || m_Owner->m_Name == "Zako8" || m_Owner->m_Name == "Zako9")
	{
		GetComponent<cCollider>()->AddCollider(Vec2(0, 40), 40);
		GetComponent<cCollider>()->AddCollider(Vec2(0, -40), 40);
	}

	m_Owner->SetAlarmSize(1);
	m_Owner->m_AlarmFunc = [&](int _Index)->void {
		switch (_Index)
		{
		case 0:
			GetComponent<cRenderer>()->m_Color = 0xffffffff;
			break;
		}
	};

	m_Owner->m_Scale = Vec2(2, 2);
}

void cZako::Update()
{
	m_Owner->m_Rot = GetComponent<cPath>()->m_Dir;
	if (m_Hp <= 0)
	{
		Death();
	}
	IsOutMap();
}

void cZako::Render()
{
}

void cZako::Release()
{
}

void cZako::Death()
{
	if (Random(0, 1250) <= m_Exp)
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
			a = OBJECT->AddObject("Item_Hp", m_Owner->m_Pos, 0.4, Obj_Item);
			break;
		case 7:
		case 8:
		case 9:
			a = OBJECT->AddObject("Item_Time", m_Owner->m_Pos, 0.4, Obj_Item);
			break;
		case 10:
			a = OBJECT->AddObject("Item_Level", m_Owner->m_Pos, 0.4, Obj_Item);
			break;
		}
		a->AddComponent<cItem>();
	}
	OBJECT->m_Player->GetComponent<cPlayer>()->AddExp(m_Exp, m_Owner->m_Pos);
	m_Owner->m_Destroyed = true;

	cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos, Vec2(4, 4) * Random(0.75f, 1.25f), Random(0, 359), 0.5);
	Anim->m_Anim = IMAGE->FindAnimation("Explosion");
	Anim->m_AnimSpeed = Random(1, 3);

	char Text[16];
	sprintf(Text, "Explosion%d", Random(1, 4));
	SOUND->Play(Text, -500);

	cParticleFunc* Func;
	for (auto& Coll : GetComponent<cCollider>()->m_Colliders)
	{
		for (int i = 0; i < 7; i++)
		{
			sprintf(Text, "Debris%d", Random(1, 6));
			Func = PART->AddParticle<cParticleFunc>(IMAGE->Find(Text), Coll.WorldPos, Vec2(0.6, 0.6) * Random(0.75f, 1.25f), Random(0, 359), 0.51);
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
}

void cZako::IsOutMap()
{
	Vec2 Pos = m_Owner->m_Pos;
	if (Pos.x <= 300 || Pos.x >= 1620 || Pos.y <= -100 || Pos.y >= 1180)
	{
		m_Owner->m_Destroyed = true;
	}
}
