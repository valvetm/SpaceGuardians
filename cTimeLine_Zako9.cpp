#include "DXUT.h"
#include "cTimeLine_Zako9.h"
#include "cZako.h"


cTimeLine_Zako9::cTimeLine_Zako9()
{
}


cTimeLine_Zako9::~cTimeLine_Zako9()
{
}

void cTimeLine_Zako9::Init()
{
}

void cTimeLine_Zako9::Update()
{
	m_Time++;
	if (GetComponent<cZako>()->m_Hp <= 0)
	{
		for (int i = 0; i < 6; i++)
		{
			FireFrictionBullet(m_Tex[1], m_Owner->m_Pos, 9, 10, Random(0, 359), 10, Random(2.f, 5.f), 0.97, 0xff00ff00);
		}
		FireEffect(m_Owner->m_Pos, 0xff00ff00);
	}
}

void cTimeLine_Zako9::Render()
{
}

void cTimeLine_Zako9::Release()
{
}
