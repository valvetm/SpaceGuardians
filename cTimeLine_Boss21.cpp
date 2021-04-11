#include "DXUT.h"
#include "cTimeLine_Boss21.h"
#include "cPlayer.h"


cTimeLine_Boss21::cTimeLine_Boss21()
{
}


cTimeLine_Boss21::~cTimeLine_Boss21()
{
}

void cTimeLine_Boss21::Init()
{
}

void cTimeLine_Boss21::Update()
{
	m_Time++;
	if (OBJECT->m_Player->GetComponent<cPlayer>()->m_Level >= 5)
	{
		if (m_Time % 12 == 0)
		{
			for (int i = 0; i < 8; i++)
			{
				FireBullet(m_Tex[1], m_Owner->m_Pos, 9, 15, i * 45 + m_Dir, 5, 0xff0000ff);
				FireBullet(m_Tex[1], m_Owner->m_Pos, 9, 15, i * 45 - m_Dir, 5, 0xff0000ff);
			}
			m_Dir += 9;
		}
	}
	else
	{
		if (m_Time % 14 == 0)
		{
			for (int i = 0; i < 8; i++)
			{
				FireBullet(m_Tex[1], m_Owner->m_Pos, 9, 15, i * 45 + m_Dir, 4, 0xff0000ff);
				FireBullet(m_Tex[1], m_Owner->m_Pos, 9, 15, i * 45 - m_Dir, 4, 0xff0000ff);
			}
			m_Dir += 10;
		}
	}

	if (GetComponent<cPath>()->m_Points.size() == 0)
	{
		GetComponent<cPath>()->AddPath(4, 1, Vec2(Random(500, 1420), Random(100, 500)), Vec2(Random(500, 1420), Random(100, 500)));
	}
	m_Owner->m_Rot = GetComponent<cPath>()->m_Dir;
}

void cTimeLine_Boss21::Render()
{
}

void cTimeLine_Boss21::Release()
{
}
