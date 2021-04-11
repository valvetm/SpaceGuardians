#include "DXUT.h"
#include "cTimeLine_MidBoss22.h"
#include "cPlayer.h"

cTimeLine_MidBoss22::cTimeLine_MidBoss22()
{
}


cTimeLine_MidBoss22::~cTimeLine_MidBoss22()
{
}

void cTimeLine_MidBoss22::Init()
{
}

void cTimeLine_MidBoss22::Update()
{
	m_Time++;
	if (OBJECT->m_Player->GetComponent<cPlayer>()->m_Level >= 4)
	{
		if (m_Time % 5 == 0)
		{
			for (int i = 0; i < 4; i++)
			{
				FireBullet(m_Tex[1], m_Owner->m_Pos, 9, 15, i * 90 + m_Dir, 6, 0xffffff00);
				FireBullet(m_Tex[1], m_Owner->m_Pos, 9, 15, i * 90 - m_Dir, 6, 0xffffff00);
			}
			m_Dir += 8;
		}
	}
	else
	{
		if (m_Time % 7 == 0)
		{
			for (int i = 0; i < 4; i++)
			{
				FireBullet(m_Tex[1], m_Owner->m_Pos, 9, 15, i * 90 + m_Dir, 6, 0xffffff00);
				FireBullet(m_Tex[1], m_Owner->m_Pos, 9, 15, i * 90 - m_Dir, 6, 0xffffff00);
			}
			m_Dir += 10;
		}
	}
}

void cTimeLine_MidBoss22::Render()
{
}

void cTimeLine_MidBoss22::Release()
{
}
