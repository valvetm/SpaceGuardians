#include "DXUT.h"
#include "cTimeLine_MidBoss11.h"


cTimeLine_MidBoss11::cTimeLine_MidBoss11()
{
}


cTimeLine_MidBoss11::~cTimeLine_MidBoss11()
{
}

void cTimeLine_MidBoss11::Init()
{
}

void cTimeLine_MidBoss11::Update()
{
	m_Time++;
	if (m_Time % 30 == 0)
	{
		for (int i = 0; i < 24; i++)
		{
			FireFrictionBullet(m_Tex[1], m_Owner->m_Pos, 9, 10, i * 15 + Random(-5, 5), 10, 5, 0.97, 0xff0000ff);
		}
	}

	if (Random(0, 300) == 0)
	{
		GetComponent<cPath>()->AddPath(Random(3.f, 6.f), 0.99, Vec2(Random(500, 1420), Random(100, 500)));
		for (int i = 0; i < 100; i++)
		{
			FireBullet(m_Tex[1], m_Owner->m_Pos, 9, 10, Random(0, 359), Random(2.f, 7.f), 0xff00ff00);
		}
	}
}

void cTimeLine_MidBoss11::Render()
{
}

void cTimeLine_MidBoss11::Release()
{
}
