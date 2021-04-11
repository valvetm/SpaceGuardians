#include "DXUT.h"
#include "cBulletFriction.h"


cBulletFriction::cBulletFriction()
{
}


cBulletFriction::~cBulletFriction()
{
}

void cBulletFriction::Init()
{
	AddComponent<cCollider>();
	AddComponent<cRenderer>();
}

void cBulletFriction::Update()
{
	m_Speed *= m_Friction;

	if (m_Friction > 1)
	{
		if(m_EndSpeed <= m_Speed)
		{
			m_Speed = m_EndSpeed;
			m_Friction = 1;
		}
	}
	else if (m_Friction < 1)
	{
		if (m_EndSpeed >= m_Speed)
		{
			m_Speed = m_EndSpeed;
			m_Friction = 1;
		}
	}

	m_Owner->m_Pos += RotateVec(Vec2(m_Speed, 0), m_Dir);
	m_Owner->m_Rot = m_Dir;

	IsOutMap();

	if (m_Grazed && !m_Grazing && m_ReflectAble)
	{
		OnReflect();
	}
	m_Grazing = false;
}

void cBulletFriction::Render()
{
}

void cBulletFriction::Release()
{
}
