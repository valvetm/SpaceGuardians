#include "DXUT.h"
#include "cBomb.h"
#include "cEnemy.h"

cBomb::cBomb()
{
}


cBomb::~cBomb()
{
}

void cBomb::Init()
{
	cParticle* Part;
	for (int i = 0; i < 6; i++)
	{
		Part = PART->AddParticle<cParticle>(IMAGE->Find("Shield"), m_Owner->m_Pos + RotateVec(Vec2(100, 0), i * 60), Vec2(0.1, 0.1), 0, 0.3, 0xffff0000);
		Part->SetScale(Vec2(0.2, 0.2), 0.98);
		Part->SetAlpha(255, -1.4, 1);
	}
	CAMERA->Shake(30, 180);
	char Text[20];
	sprintf(Text, "BossExplosion%d", Random(1, 5));
	SOUND->Play(Text, -500);
	for (auto& iter : OBJECT->m_Objects[Obj_Enemy])
	{
		if(iter->GetComponent<cCollider>()->m_Colliders.size() != 0)
			iter->GetComponent<cEnemy>()->m_Hp -= 500;
	}

	m_Timer = 0;
}

void cBomb::Update()
{
	cParticle* Part;
	char Text[16];
	for (auto& iter : OBJECT->m_Objects[Obj_Enemy])
	{
		if (iter->GetComponent<cCollider>()->m_Colliders.size() != 0)
		{
			iter->GetComponent<cEnemy>()->m_Hp -= 1;
			iter->GetComponent<cRenderer>()->m_Color = 0xffff0000;
			iter->SetAlarm(0, 3);
			for (auto& Coll : iter->GetComponent<cCollider>()->m_Colliders)
			{
				for (int i = 0; i < 4; i++)
				{
					sprintf(Text, "Spark%d", Random(1, 4));
					Part = PART->AddParticle<cParticle>(IMAGE->Find(Text), Coll.WorldPos + Vec2(Random(-Coll.Radius, Coll.Radius), Random(-Coll.Radius, Coll.Radius)), Vec2(0.1, 0.1), Random(0, 359), 0.5, 0xffff0000);
					Part->SetAlpha(255 * Random(1, 4), -255, 1);
				}
			}
		}
	}

	for (auto& iter : OBJECT->m_Objects[Obj_EnemyBullet])
	{
		iter->m_Destroyed = true;
	}
	m_Timer++;
	if (m_Timer == 180)
	{
		m_Owner->m_Destroyed = true;
	}
}

void cBomb::Render()
{
}

void cBomb::Release()
{
}
