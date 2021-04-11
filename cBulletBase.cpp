#include "DXUT.h"
#include "cBulletBase.h"
#include "cBulletHoming.h"
#include "cPlayer.h"

cBulletBase::cBulletBase()
{
}


cBulletBase::~cBulletBase()
{
	cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Explosion"), m_Owner->m_Pos, Vec2(0.75, 0.75), Random(0, 359), 0.4, GetComponent<cRenderer>()->m_Color);
	Part->SetScale(Vec2(-0.001, -0.001), 1.1);
	Part->SetAlpha(255, -1, 1.1);
}

void cBulletBase::IsOutMap()
{
	Vec2 Pos = m_Owner->m_Pos;
	if (Pos.x <= 350 || Pos.x >= 1570 || Pos.y <= -50 || Pos.y >= 1130)
	{
		m_Owner->m_Destroyed = true;
	}
}

void cBulletBase::OnReflect()
{
	cPlayer* Player = OBJECT->m_Player->GetComponent<cPlayer>();
	if (Player->m_Level != 5)
	{
		Player->m_Exp += ceil(m_Damage * 0.1);
	}
	SYSTEM->m_Score += 25000;
	SYSTEM->m_Reflected++;
	m_Owner->m_Destroyed = true;
	cObject* a = OBJECT->AddObject("PlayerBullet", m_Owner->m_Pos, 0.7, Obj_PlayerBullet);
	a->AddComponent<cBulletHoming>()->m_Damage = ceil(m_Damage * Player->m_Level * 0.75f);
	a->GetComponent<cBulletHoming>()->m_Speed = 25;
	a->GetComponent<cRenderer>()->m_Image = GetComponent<cRenderer>()->m_Image;
	a->GetComponent<cRenderer>()->m_Color = 0x90ffffff;
	a->GetComponent<cCollider>()->AddCollider(Vec2(0, 0), GetComponent<cCollider>()->m_Colliders[0].Radius);
	
	if (m_FiredFrom->m_ID == m_FiredFromID)
	{
		if (Player->m_Level >= 4)
		{
			a->GetComponent<cBulletHoming>()->m_Target = m_FiredFrom;
			a->GetComponent<cBulletHoming>()->m_TargetID = m_FiredFromID;
		}
		else
		{
			a->GetComponent<cBulletHoming>()->m_Dir = PointDirection(m_Owner->m_Pos, m_FiredFrom->m_Pos);
		}
	}
	else if(OBJECT->m_Objects[Obj_Enemy].size() != 0)
	{
		cObject* Near;
		float Dist;
		float NearDist = 10000;
		for (auto& iter : OBJECT->m_Objects[Obj_Enemy])
		{
			Dist = D3DXVec2Length(&(Player->m_Owner->m_Pos - iter->m_Pos));
			if (Dist < NearDist)
			{
				NearDist = Dist;
				Near = iter;
			}
		}

		if (Player->m_Level >= 4)
		{
			a->GetComponent<cBulletHoming>()->m_Target = Near;
			a->GetComponent<cBulletHoming>()->m_TargetID = Near->m_ID;
		}
		else
		{
			a->GetComponent<cBulletHoming>()->m_Dir = PointDirection(m_Owner->m_Pos, Near->m_Pos);
		}
	}
	else
	{
		a->GetComponent<cBulletHoming>()->m_Dir = m_Dir;
	}
	m_Owner->m_Pos = Vec2(0, 0);
}
