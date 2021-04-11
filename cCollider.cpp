#include "DXUT.h"
#include "cCollider.h"


cCollider::cCollider()
{
}


cCollider::~cCollider()
{
}

void cCollider::Init()
{
}

void cCollider::Update()
{
	for (auto& iter : m_Colliders)
	{
		iter.WorldPos = m_Owner->m_Pos + RotateVec(iter.LocalPos, m_Owner->m_Rot);
	}
}

void cCollider::Render()
{
}

void cCollider::Release()
{
}

void cCollider::AddCollider(Vec2 _Pos, float _Radius)
{
	m_Colliders.push_back(Collider{ _Pos,_Pos,_Radius });
}
