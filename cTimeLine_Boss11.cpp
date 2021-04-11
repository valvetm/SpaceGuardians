#include "DXUT.h"
#include "cTimeLine_Boss11.h"
#include "cPlayer.h"

cTimeLine_Boss11::cTimeLine_Boss11()
{
}


cTimeLine_Boss11::~cTimeLine_Boss11()
{
}

void cTimeLine_Boss11::Init()
{
}

void cTimeLine_Boss11::Update()
{
	m_Time++;
	if (OBJECT->m_Player->GetComponent<cPlayer>()->m_Level >= 3)
	{
		switch (m_Time)
		{
		case 75:
		{
			float Dir = PointDirection(m_Owner->m_Pos, OBJECT->m_Player->m_Pos);
			for (int i = 0; i < 36; i++)
			{
				FireBullet(m_Tex[1], m_Owner->m_Pos + RotateVec(Vec2(40, 0), i * 10), 9, 10, Dir, 6, 0xff00ffff);
			}
		}
		case 15:
		case 30:
		case 45:
		case 60:
			for (int i = 0; i < 18; i++)
			{
				FireFrictionBullet(m_Tex[1], m_Owner->m_Pos, 9, 10, i * 20 + m_Dir, 10, 4, 0.96, 0xff0000ff);
			}
			m_Dir += 6;
			break;

		case 150:
		{
			float Dir = PointDirection(m_Owner->m_Pos, OBJECT->m_Player->m_Pos);
			for (int i = 0; i < 36; i++)
			{
				FireBullet(m_Tex[1], m_Owner->m_Pos + RotateVec(Vec2(40, 0), i * 10), 9, 10, Dir, 6, 0xff00ffff);
			}
			m_Time = 0;
		}
		case 90:
		case 105:
		case 120:
		case 135:
			for (int i = 0; i < 18; i++)
			{
				FireFrictionBullet(m_Tex[1], m_Owner->m_Pos, 9, 10, i * 20 + m_Dir, 10, 4, 0.96, 0xff0000ff);
			}
			m_Dir -= 6;
			break;
		}
	}
	else
	{
		switch (m_Time)
		{
		case 120:
		{
			float Dir = PointDirection(m_Owner->m_Pos, OBJECT->m_Player->m_Pos);
			for (int i = -5; i <= 5; i++)
			{
				FireBullet(m_Tex[1], m_Owner->m_Pos, 9, 10, Dir + i * 10, 6, 0xff00ffff);
			}
		}
		case 20:
		case 40:
		case 80:
		case 100:
			for (int i = 0; i < 18; i++)
			{
				FireFrictionBullet(m_Tex[1], m_Owner->m_Pos, 9, 10, i * 20 + m_Dir, 10, 4, 0.96, 0xff0000ff);
			}
			m_Dir += 6;
			break;

		case 220:
		{
			float Dir = PointDirection(m_Owner->m_Pos, OBJECT->m_Player->m_Pos);
			for (int i = -5; i <= 5; i++)
			{
				FireBullet(m_Tex[1], m_Owner->m_Pos, 9, 10, Dir + i * 10, 6, 0xff00ffff);
			}
			m_Time = 0;
		}
		case 140:
		case 160:
		case 180:
		case 200:
			for (int i = 0; i < 18; i++)
			{
				FireFrictionBullet(m_Tex[1], m_Owner->m_Pos, 9, 10, i * 20 + m_Dir, 10, 4, 0.96, 0xff0000ff);
			}
			m_Dir -= 6;
			break;
		}
	}
}

void cTimeLine_Boss11::Render()
{
}

void cTimeLine_Boss11::Release()
{
}
