#include "DXUT.h"
#include "cTimeLine_Boss22.h"
#include "cPlayer.h"


cTimeLine_Boss22::cTimeLine_Boss22()
{
}


cTimeLine_Boss22::~cTimeLine_Boss22()
{
}

void cTimeLine_Boss22::Init()
{
}

void cTimeLine_Boss22::Update()
{
	m_Time++;
	if (OBJECT->m_Player->GetComponent<cPlayer>()->m_Level >= 5)
	{
		if (m_Time % 10 == 0)
		{
			for (int i = 0; i < 8; i++)
			{
				FireBullet(m_Tex[1], m_Owner->m_Pos, 9, 15, i * 45 + m_Dir + Random(-3.f, 3.f), 6, 0xffff0000);
				FireBullet(m_Tex[1], m_Owner->m_Pos, 9, 15, i * 45 - m_Dir + Random(-3.f, 3.f), 6, 0xffff0000);
			}
			m_Dir += 8;
		}
	}
	else
	{
		if(m_Time % 12 == 0)
		{
			for (int i = 0; i < 8; i++)
			{
				FireBullet(m_Tex[1], m_Owner->m_Pos, 9, 15, i * 45 + m_Dir + Random(-3.f, 3.f), 5, 0xffff0000);
				FireBullet(m_Tex[1], m_Owner->m_Pos, 9, 15, i * 45 - m_Dir + Random(-3.f, 3.f), 5, 0xffff0000);
			}
			m_Dir += 9;
		}
	}

	if (GetComponent<cPath>()->m_Points.size() == 0)
	{
		GetComponent<cPath>()->AddPath(4, 1, Vec2(Random(500, 1420), Random(100, 800)), Vec2(Random(500, 1420), Random(100, 1000)));
	}
	m_Owner->m_Rot = GetComponent<cPath>()->m_Dir;
}

void cTimeLine_Boss22::Render()
{
}

void cTimeLine_Boss22::Release()
{
}
