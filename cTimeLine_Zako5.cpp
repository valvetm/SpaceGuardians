#include "DXUT.h"
#include "cTimeLine_Zako5.h"


cTimeLine_Zako5::cTimeLine_Zako5()
{
}


cTimeLine_Zako5::~cTimeLine_Zako5()
{
}

void cTimeLine_Zako5::Init()
{
	m_Angle = 1;
}

void cTimeLine_Zako5::Update()
{
	m_Time++;
	if (m_Time >= 100)
	{
		if (m_Time % 2 == 0)
		{
			for (int i = 0; i < 15; i++)
			{
				FireBullet(m_Tex[1], m_Owner->m_Pos, 9, 15, i * 24 + m_Dir, 8, 0xff00ffff);
			}
			m_Dir += 2 * m_Angle;
		}

		if (m_Time % 45 == 0)
		{
			m_Angle *= -1;
		}

		if (m_Time == 700)
		{
			GetComponent<cPath>()->AddPath(1, 1.01, Vec2(960, -300));
		}

		if (m_Owner->m_Pos.y <= -200)
		{
			m_Owner->m_Destroyed = true;
		}
	}
}

void cTimeLine_Zako5::Render()
{
}

void cTimeLine_Zako5::Release()
{
}
