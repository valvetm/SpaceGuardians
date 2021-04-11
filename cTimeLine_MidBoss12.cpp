#include "DXUT.h"
#include "cTimeLine_MidBoss12.h"


cTimeLine_MidBoss12::cTimeLine_MidBoss12()
{
}


cTimeLine_MidBoss12::~cTimeLine_MidBoss12()
{
}

void cTimeLine_MidBoss12::Init()
{
}

void cTimeLine_MidBoss12::Update()
{
	m_Time++;
	if (m_Time % 60 == 0)
	{
		for (int i = 0; i < 20; i++)
		{
			FireBullet(m_Tex[2], m_Owner->m_Pos, 9, 10, Random(60, 120), Random(3.f, 7.f), 0xffff0000)->GetComponent<cBullet>()->m_ReflectAble = false;
		}
	}
}

void cTimeLine_MidBoss12::Render()
{
}

void cTimeLine_MidBoss12::Release()
{
}
