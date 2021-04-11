#include "DXUT.h"
#include "cBulletBFG.h"
#include "cEnemy.h"


cBulletBFG::cBulletBFG()
{
}


cBulletBFG::~cBulletBFG()
{
}

void cBulletBFG::Init()
{
	AddComponent<cCollider>();
	AddComponent<cRenderer>();
	m_Anim = IMAGE->FindAnimation("BFG");
	m_Frame = -1;
	m_Timer = 0;
}

void cBulletBFG::Update()
{
	m_Owner->m_Pos += RotateVec(Vec2(m_Speed, 0), m_Dir);

	float Dist;
	float Rot;
	cParticle* Part;
	char Text[16];
	for (auto& iter : OBJECT->m_Objects[Obj_Enemy])
	{
		Dist = D3DXVec2Length(&(m_Owner->m_Pos - iter->m_Pos));
		if (Dist <= m_Charge + 50 && iter->GetComponent<cCollider>()->m_Colliders.size() != 0)
		{
			iter->GetComponent<cEnemy>()->m_Hp -= m_Charge * 0.007;
			iter->GetComponent<cRenderer>()->m_Color = 0xffff0000;
			iter->SetAlarm(0, 3);
			for (auto& Coll : iter->GetComponent<cCollider>()->m_Colliders)
			{
				Rot = PointDirection(m_Owner->m_Pos, Coll.WorldPos + Vec2(Random(-Coll.Radius, Coll.Radius), Random(-Coll.Radius, Coll.Radius)));
				sprintf(Text, "Beam%d", Random(1, 3));
				Part = PART->AddParticle<cParticle>(IMAGE->Find(Text), m_Owner->m_Pos + RotateVec(Vec2(Dist * 0.5, 0), Rot), Vec2(Dist / 512, Random(0.1f, 0.3f)), Rot, 0.59, 0xff00ffff);
				Part->SetAlpha(355, -100, 1);
				for (int i = 0; i < 4; i++)
				{
					sprintf(Text, "Spark%d", Random(1, 4));
					Part = PART->AddParticle<cParticle>(IMAGE->Find(Text), Coll.WorldPos + Vec2(Random(-Coll.Radius, Coll.Radius), Random(-Coll.Radius, Coll.Radius)), Vec2(0.1, 0.1), Random(0, 359), 0.5, 0xff00ffff);
					Part->SetAlpha(255 * Random(1, 4), -255, 1);
				}
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		sprintf(Text, "Spark%d", Random(1, 4));
		Part = PART->AddParticle<cParticle>(IMAGE->Find(Text), m_Owner->m_Pos  + Vec2(Random(-64, 64), Random(-64, 64)) * m_Owner->m_Scale.x, Vec2(0.1, 0.1), Random(0, 359), 0.49, 0xff00ffff);
		Part->SetAlpha(255 * Random(1, 4), -255, 1);
	}

	m_Timer--;
	if (m_Timer <= 0)
	{
		m_Frame++;
		m_Timer = 1;
		if (m_Frame == (*m_Anim).size())
		{
			m_Frame = 0;
		}
		GetComponent<cRenderer>()->m_Image = (*m_Anim)[m_Frame];
	}

	Vec2 Pos = m_Owner->m_Pos;
	if (Pos.x <= 300 || Pos.x >= 1620 || Pos.y <= -100 || Pos.y >= 1180)
	{
		m_Owner->m_Destroyed = true;
	}
}

void cBulletBFG::Render()
{
}

void cBulletBFG::Release()
{
	cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos, Vec2(2, 2), Random(0, 359), 0.4);
	Anim->m_Anim = IMAGE->FindAnimation("BFGExplosion");
	Anim->m_AnimSpeed = 2;
	Anim->SetScale(Vec2(0.2, 0.2), 0.98);
	CAMERA->Shake(40 * m_Owner->m_Scale.x, 60);
	char Text[16];
	sprintf(Text, "BossExplosion%d", Random(1, 5));
	SOUND->Play(Text, -500);
}
