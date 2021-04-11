#include "DXUT.h"
#include "cTimeLine_Zako6.h"


cTimeLine_Zako6::cTimeLine_Zako6()
{
}


cTimeLine_Zako6::~cTimeLine_Zako6()
{
}

void cTimeLine_Zako6::Init()
{
}

void cTimeLine_Zako6::Update()
{
	m_Time++;
	switch (m_Time)
	{
	case 30:
		m_Dir = PointDirection(m_Owner->m_Pos, OBJECT->m_Player->m_Pos);
	case 45:
	case 60:
		for (int i = -1; i <= 1; i++)
		{
			FireFrictionBullet(m_Tex[1], m_Owner->m_Pos, 9, 15, m_Dir + 20 * i, 10, 5, 0.97, 0xffff00000);
		}
		FireEffect(m_Owner->m_Pos, 0xffff0000);
		break;

	case 200:
		m_Time = 0;
		break;
	}
}

void cTimeLine_Zako6::Render()
{
}

void cTimeLine_Zako6::Release()
{
}
