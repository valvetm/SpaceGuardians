#include "DXUT.h"
#include "cTimeLine_Zako1.h"


cTimeLine_Zako1::cTimeLine_Zako1()
{
}


cTimeLine_Zako1::~cTimeLine_Zako1()
{
}

void cTimeLine_Zako1::Init()
{
}

void cTimeLine_Zako1::Update()
{
	m_Time++;
	switch (m_Time)
	{
	case 30:
		FireBullet(m_Tex[1], m_Owner->m_Pos, 9, 10, PointDirection(m_Owner->m_Pos, OBJECT->m_Player->m_Pos), 5, 0xff00ffff);
		FireEffect(m_Owner->m_Pos, 0xff00ffff);
		break;

	case 45:
		FireBullet(m_Tex[1], m_Owner->m_Pos, 9, 10, Random(0, 359), 4, 0xffff0000);
		FireEffect(m_Owner->m_Pos, 0xffff0000);
		break;

	case 150:
		m_Time = 0;
	}
}

void cTimeLine_Zako1::Render()
{
}

void cTimeLine_Zako1::Release()
{
}
