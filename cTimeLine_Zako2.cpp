#include "DXUT.h"
#include "cTimeLine_Zako2.h"


cTimeLine_Zako2::cTimeLine_Zako2()
{
}


cTimeLine_Zako2::~cTimeLine_Zako2()
{
}

void cTimeLine_Zako2::Init()
{
}

void cTimeLine_Zako2::Update()
{
	m_Time++;
	if (m_Time % 2 == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			FireFrictionBullet(m_Tex[1], m_Owner->m_Pos, 9, 10, 45 + m_Owner->m_Rot + 90 * i, 10, 4, 0.96, 0xffff00ff)->GetComponent<cBulletFriction>()->m_FiredFromID = 0;
		}
	}
	m_Owner->m_Rot += 0.15 * m_Dir;

	if (m_Owner->m_Pos.y >= 1200)
	{
		m_Owner->m_Destroyed = true;
	}
}

void cTimeLine_Zako2::Render()
{
}

void cTimeLine_Zako2::Release()
{
}
