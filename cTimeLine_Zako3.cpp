#include "DXUT.h"
#include "cTimeLine_Zako3.h"


cTimeLine_Zako3::cTimeLine_Zako3()
{
}


cTimeLine_Zako3::~cTimeLine_Zako3()
{
}

void cTimeLine_Zako3::Init()
{
}

void cTimeLine_Zako3::Update()
{
	m_Time++;
	if (m_Time % 30 == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			FireBullet(m_Tex[1], m_Owner->m_Pos, 9, 10, Random(0, 359), Random(2.f, 7.f), 0xff00ff00);
		}
		FireEffect(m_Owner->m_Pos, 0xff00ff00);
	}
}

void cTimeLine_Zako3::Render()
{
}

void cTimeLine_Zako3::Release()
{
}
