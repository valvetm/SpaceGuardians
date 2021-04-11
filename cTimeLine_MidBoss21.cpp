#include "DXUT.h"
#include "cTimeLine_MidBoss21.h"
#include "cMidBoss2.h"

cTimeLine_MidBoss21::cTimeLine_MidBoss21()
{
}


cTimeLine_MidBoss21::~cTimeLine_MidBoss21()
{
}

void cTimeLine_MidBoss21::Init()
{
}

void cTimeLine_MidBoss21::Update()
{
	m_Time++;
	if (OBJECT->m_Player->GetComponent<cPlayer>()->m_Level >= 4)
	{
		if (m_Time % 4 == 0)
		{
			FireBullet(m_Tex[1], m_Owner->m_Pos, 9, 15, Random(0, 359), Random(2.f, 7.f), 0xffff0000);
		}

		if (Random(0, 300) == 0)
		{
			for (int i = 0; i < 24; i++)
			{
				FireFrictionBullet(m_Tex[1], m_Owner->m_Pos, 9, 15, i * 15, 20, 4, 0.95, 0xff00ff00);
			}
		}

		if (GetComponent<cMidBoss2>()->m_Index == 0)
		{
			int PlayerDir = PointDirection(m_Owner->m_Pos, OBJECT->m_Player->m_Pos);
			int Dir = (int)(PlayerDir - m_Owner->m_Rot + 180) % 360 - 180;
			m_Owner->m_Rot = Lerp<float>(m_Owner->m_Rot, m_Owner->m_Rot + Dir, 0.07);
			if (Random(0, 450) == 0)
			{
				for (int i = -3; i <= 3; i++)
				{
					for (int j = 0; j < 15; j++)
					{
						FireFrictionBullet(m_Tex[2], m_Owner->m_Pos, 9, 15, m_Owner->m_Rot + i * 10, 0.5, 5 + j * 0.5, 1.02, 0xff0000ff)->GetComponent<cBulletFriction>()->m_ReflectAble = false;
					}
				}
			}
		}
		else
		{
			m_Owner->m_Rot = GetComponent<cPath>()->m_Dir;
			float Rand = Random(0, 359);
			if (Random(0, 450) == 0)
			{
				for (int i = 0; i < 8; i++)
				{
					for (float j = 0; j < 6; j++)
					{
						for (float k = -(j * 0.5); k <= j * 0.5; k += 1)
						{
							FireBullet(m_Tex[1], m_Owner->m_Pos, 9, 15, Rand + i * 45 + k * 6, 10 - j * 0.5, 0xff0000ff);
						}
					}
				}
			}
		}
	}
	else
	{
		if (m_Time % 5 == 0)
		{
			FireBullet(m_Tex[1], m_Owner->m_Pos, 9, 15, Random(0, 359), Random(2.f, 7.f), 0xffff0000);
		}

		if (Random(0, 300) == 0)
		{
			for (int i = 0; i < 18; i++)
			{
				FireFrictionBullet(m_Tex[1], m_Owner->m_Pos, 9, 15, i * 20, 20, 4, 0.95, 0xff00ff00);
			}
		}

		if (GetComponent<cMidBoss2>()->m_Index == 0)
		{
			int PlayerDir = PointDirection(m_Owner->m_Pos, OBJECT->m_Player->m_Pos);
			int Dir = (int)(PlayerDir - m_Owner->m_Rot + 180) % 360 - 180;
			m_Owner->m_Rot = Lerp<float>(m_Owner->m_Rot, m_Owner->m_Rot + Dir, 0.07);
			if (Random(0, 450) == 0)
			{
				for (int i = -2; i <= 2; i++)
				{
					for (int j = 0; j < 15; j++)
					{
						FireFrictionBullet(m_Tex[2], m_Owner->m_Pos, 9, 15, m_Owner->m_Rot + i * 15, 0.5, 5 + j * 0.5, 1.02, 0xff0000ff)->GetComponent<cBulletFriction>()->m_ReflectAble = false;
					}
				}
			}
		}
		else
		{
			m_Owner->m_Rot = GetComponent<cPath>()->m_Dir;
			float Rand = Random(0, 359);
			if (Random(0, 450) == 0)
			{
				for (int i = 0; i < 6; i++)
				{
					for (float j = 0; j < 6; j++)
					{
						for (float k = -(j * 0.5); k <= j * 0.5; k += 1)
						{
							FireBullet(m_Tex[1], m_Owner->m_Pos, 9, 15, Rand + i * 60 + k * 6, 10 - j * 0.5, 0xff0000ff);
						}
					}
				}
			}
		}
	}

	if (GetComponent<cPath>()->m_Points.size() == 0)
	{
		GetComponent<cPath>()->AddPath(4, 1, Vec2(Random(500, 1420), Random(100, 500)), Vec2(Random(500, 1420), Random(100, 500)));
	}
}

void cTimeLine_MidBoss21::Render()
{
}

void cTimeLine_MidBoss21::Release()
{
}
