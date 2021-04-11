#include "DXUT.h"
#include "cTimeLine_Boss23.h"
#include "cPlayer.h"


cTimeLine_Boss23::cTimeLine_Boss23()
{
}


cTimeLine_Boss23::~cTimeLine_Boss23()
{
}

void cTimeLine_Boss23::Init()
{
}

void cTimeLine_Boss23::Update()
{
	if (OBJECT->m_Player->GetComponent<cPlayer>()->m_Level >= 5)
	{
		if (Random(0, 400) == 0)
		{
			for (int i = 0; i < 18; i++)
			{
				FireFrictionBullet(m_Tex[1], m_Owner->m_Pos, 9, 15, i * 20, 10, 4, 0.97, 0xff00ffff);
			}
		}
	}
	else
	{
		if (Random(0, 500) == 0)
		{
			for (int i = 0; i < 15; i++)
			{
				FireFrictionBullet(m_Tex[1], m_Owner->m_Pos, 9, 15, i * 24, 10, 4, 0.97, 0xff00ffff);
			}
		}
	}
}

void cTimeLine_Boss23::Render()
{
}

void cTimeLine_Boss23::Release()
{
}
