#include "DXUT.h"
#include "cTimeLine_Zako4.h"


cTimeLine_Zako4::cTimeLine_Zako4()
{
}


cTimeLine_Zako4::~cTimeLine_Zako4()
{
}

void cTimeLine_Zako4::Init()
{
}

void cTimeLine_Zako4::Update()
{
	m_Time++;
	switch (m_Time)
	{
	case 30:
		for (int i = 0; i < 6; i++)
		{
			FireFrictionBullet(m_Tex[1], m_Owner->m_Pos, 9, 10, i * 60, 10, 4, 0.96, 0xffffff00);
		}
		FireEffect(m_Owner->m_Pos, 0xffffff00);
		break;

	case 120:
		m_Time = 0;
	}
}

void cTimeLine_Zako4::Render()
{
}

void cTimeLine_Zako4::Release()
{
}
