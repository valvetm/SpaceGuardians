#include "DXUT.h"
#include "cBulletHoming.h"


cBulletHoming::cBulletHoming()
{
}


cBulletHoming::~cBulletHoming()
{
}

void cBulletHoming::Init()
{
	AddComponent<cCollider>();
	AddComponent<cRenderer>();
}

void cBulletHoming::Update()
{
	if(m_Target != nullptr)
	{
		if (m_Target->m_ID == m_TargetID && m_Target->m_Destroyed == false)
		{
			m_Dir = PointDirection(m_Owner->m_Pos, m_Target->m_Pos);
		}
		else
		{
			m_Target = nullptr;
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

void cBulletHoming::Render()
{
}

void cBulletHoming::Release()
{
}
