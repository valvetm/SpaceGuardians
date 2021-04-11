#include "DXUT.h"
#include "cTimeLine_Zako8.h"


cTimeLine_Zako8::cTimeLine_Zako8()
{
}


cTimeLine_Zako8::~cTimeLine_Zako8()
{
}

void cTimeLine_Zako8::Init()
{
}

void cTimeLine_Zako8::Update()
{
	m_Time++;
	if (m_Time % 4 == 0)
	{
		FireFrictionBullet(m_Tex[1], m_Owner->m_Pos, 9, 15, Random(0, 359), 1, 8, 1.015, 0xff00ffff);
		FireEffect(m_Owner->m_Pos, 0xff00ffff);
	}
}

void cTimeLine_Zako8::Render()
{
}

void cTimeLine_Zako8::Release()
{
}
