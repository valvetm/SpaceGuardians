#include "DXUT.h"
#include "cTimeLine_Boss24.h"
#include "cPlayer.h"


cTimeLine_Boss24::cTimeLine_Boss24()
{
}


cTimeLine_Boss24::~cTimeLine_Boss24()
{
}

void cTimeLine_Boss24::Init()
{
}

void cTimeLine_Boss24::Update()
{
	m_Time++;
	if (OBJECT->m_Player->GetComponent<cPlayer>()->m_Level >= 5)
	{
		if (m_Time % 300 == 0)
		{
			m_Dir = PointDirection(m_Owner->m_Pos, OBJECT->m_Player->m_Pos);
			for (int i = 0; i < 50; i++)
			{
				FireFrictionBullet(m_Tex[1], m_Owner->m_Pos, 9, 15, m_Dir + Random(-15.f, 15.f), 10, Random(1.f, 3.f), 0.96, 0xffff00ff);
			}
		}
	}
	else
	{
		if (m_Time % 350 == 0)
		{
			m_Dir = PointDirection(m_Owner->m_Pos, OBJECT->m_Player->m_Pos);
			for (int i = 0; i < 30; i++)
			{
				FireFrictionBullet(m_Tex[1], m_Owner->m_Pos, 9, 15, m_Dir + Random(-10.f, 10.f), 10, Random(1.f, 3.f), 0.96, 0xffff00ff);
			}
		}
	}

	if (GetComponent<cPath>()->m_Points.size() == 0)
	{
		GetComponent<cPath>()->AddPath(4, 1, Vec2(Random(500, 1420), Random(100, 500)), Vec2(Random(500, 1420), Random(100, 500)));
	}
	m_Owner->m_Rot = GetComponent<cPath>()->m_Dir;
}

void cTimeLine_Boss24::Render()
{
}

void cTimeLine_Boss24::Release()
{
}
