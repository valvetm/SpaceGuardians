#include "DXUT.h"
#include "cBullet.h"


cBullet::cBullet()
{
}


cBullet::~cBullet()
{
}

void cBullet::Init()
{
	AddComponent<cCollider>();
	AddComponent<cRenderer>();
}

void cBullet::Update()
{
	m_Owner->m_Pos += RotateVec(Vec2(m_Speed, 0), m_Dir);
	m_Owner->m_Rot = m_Dir;
	
	IsOutMap();

	if (m_Grazed && !m_Grazing && m_ReflectAble)
	{
		OnReflect();
	}
	m_Grazing = false;
}

void cBullet::Render()
{
}

void cBullet::Release()
{
}
