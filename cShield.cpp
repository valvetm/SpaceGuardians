#include "DXUT.h"
#include "cShield.h"


cShield::cShield()
{
}


cShield::~cShield()
{
}

void cShield::Init()
{
	m_Size = 200;
	AddComponent<cRenderer>()->m_Image = IMAGE->Find("Shield");
	GetComponent<cRenderer>()->m_Color = D3DCOLOR_XRGB(0, 50, 255);
	AddComponent<cCollider>()->m_CollFunc = [&](cObject* _Other)->void {
		_Other->m_Destroyed = true;
		char Text[16];
		sprintf(Text, "Spark%d", Random(1, 4));
		cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find(Text), _Other->m_Pos, Vec2(0.15, 0.15), Random(0, 359), 0.35, D3DCOLOR_XRGB(0, 50, 255));
		Part->SetAlpha(255 * Random(1, 4), -255, 1);
	};
	GetComponent<cCollider>()->m_CollWith.push_back(Obj_EnemyBullet);
	SOUND->Play("Shield", -500);
}

void cShield::Update()
{
	m_Size -= 1;
	GetComponent<cCollider>()->m_Colliders.clear();
	GetComponent<cCollider>()->AddCollider(Vec2(0, 0), m_Size);
	m_Owner->m_Scale = Vec2(m_Size / 256.f, m_Size / 256.f);

	if (m_Size <= 3)
	{
		m_Owner->m_Destroyed = true;
	}
}

void cShield::Render()
{
}

void cShield::Release()
{
}
