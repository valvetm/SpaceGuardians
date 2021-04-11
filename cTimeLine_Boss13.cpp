#include "DXUT.h"
#include "cTimeLine_Boss13.h"
#include "cPlayer.h"

cTimeLine_Boss13::cTimeLine_Boss13()
{
}


cTimeLine_Boss13::~cTimeLine_Boss13()
{
}

void cTimeLine_Boss13::Init()
{
	m_Dir = PointDirection(m_Owner->m_Pos, OBJECT->m_Player->m_Pos);
}

void cTimeLine_Boss13::Update()
{
	m_Time++;
	if (m_Time % 2 == 0)
	{
		for (int i = 3; i <= 33; i++)
		{
			FireBullet(m_Tex[2], m_Owner->m_Pos, 9, 10, m_Dir + i * 10, 8, 0xffff0000)->GetComponent<cBullet>()->m_ReflectAble = false;
		}
	}
	m_Dir += 0.5;

	if (m_Time % 45 == 0)
	{
		for (int i = 0; i < 40; i++)
		{
			FireBullet(m_Tex[1], Vec2(400 + i * 10, 1080), 9, 10, 270, 3, 0xffff00ff);
			FireBullet(m_Tex[1], Vec2(1520 - i * 10, 0), 9, 10, 90, 3, 0xffff00ff);
		}
	}
}

void cTimeLine_Boss13::Render()
{
}

void cTimeLine_Boss13::Release()
{
}
