#include "DXUT.h"
#include "cTimeLine_Boss12.h"
#include "cPlayer.h"

cTimeLine_Boss12::cTimeLine_Boss12()
{
}


cTimeLine_Boss12::~cTimeLine_Boss12()
{
}

void cTimeLine_Boss12::Init()
{
}

void cTimeLine_Boss12::Update()
{
	m_Time++;
	if (OBJECT->m_Player->GetComponent<cPlayer>()->m_Level >= 3)
	{
		if (m_Time % 3 == 0)
		{
			FireBullet(m_Tex[1], m_Owner->m_Pos, 9, 10, 90 + m_Dir, 6, 0xff00ff00);
			FireBullet(m_Tex[1], m_Owner->m_Pos, 9, 10, 90 - m_Dir, 6, 0xff00ff00);
			m_Dir += 4;
		}

		if (m_Time % 12 == 0)
		{
			FireFrictionBullet(m_Tex[3], Vec2(400, Random(0, 1080)), 5.5, 10, Random(-20, 20), 1, 8, 1.02, 0xffffff00);
			FireFrictionBullet(m_Tex[3], Vec2(1520, Random(0, 1080)), 5.5, 10, Random(160, 200), 1, 8, 1.02, 0xffffff00);
		}
	}
	else
	{
		if (m_Time % 4 == 0)
		{
			FireBullet(m_Tex[1], m_Owner->m_Pos, 9, 10, 90 + m_Dir, 6, 0xff00ff00);
			FireBullet(m_Tex[1], m_Owner->m_Pos, 9, 10, 90 - m_Dir, 6, 0xff00ff00);
			m_Dir += 5;
		}

		if (m_Time % 15 == 0)
		{
			FireFrictionBullet(m_Tex[3], Vec2(400, Random(0, 1080)), 5.5, 10, Random(-20, 20), 1, 8, 1.02, 0xffffff00);
			FireFrictionBullet(m_Tex[3], Vec2(1520, Random(0, 1080)), 5.5, 10, Random(160, 200), 1, 8, 1.02, 0xffffff00);
		}
	}
}

void cTimeLine_Boss12::Render()
{
}

void cTimeLine_Boss12::Release()
{
}
