#include "DXUT.h"
#include "cTimeLine_Zako7.h"


cTimeLine_Zako7::cTimeLine_Zako7()
{
}


cTimeLine_Zako7::~cTimeLine_Zako7()
{
}

void cTimeLine_Zako7::Init()
{
}

void cTimeLine_Zako7::Update()
{
	m_Time++;
	switch (m_Time)
	{
	case 30:
		for (int i = 0; i < 24; i++)
		{
			FireBullet(m_Tex[1], m_Owner->m_Pos, 9, 15, i * 15, 6, 0xff0000ff);
		}
		FireEffect(m_Owner->m_Pos, 0xff0000ff);
		break;

	case 60:
		for (int i = 0; i < 3; i++)
		{
			for (int j = -3; j <= 3; j++)
			{
				FireFrictionBullet(m_Tex[1], m_Owner->m_Pos, 9, 15, m_Owner->m_Rot + i * 120 + j * 7, 10, 4, 0.96, 0xffff0000);
			}
		}
		FireEffect(m_Owner->m_Pos, 0xffff0000);
		break;

	case 120:
		m_Time = 0;
	}
}

void cTimeLine_Zako7::Render()
{
}

void cTimeLine_Zako7::Release()
{
}
