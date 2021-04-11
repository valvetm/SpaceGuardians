#include "DXUT.h"
#include "cPath.h"


cPath::cPath()
{
}


cPath::~cPath()
{
}

void cPath::Init()
{
	m_Next = 0;
	m_Speed = 0;
	m_Friction = 1;
	m_Dir = 0;
}

void cPath::Update()
{
	if (m_Points.size() != 0)
	{
		if (D3DXVec2Length(&(m_Owner->m_Pos - m_Points[m_Next])) <= m_Speed + 1)
		{
			m_Owner->m_Pos = m_Points[m_Next];
			m_Next++;
			if (m_Next == m_Points.size())
			{
				m_Points.clear();
				m_Next = 0;
				m_Friction = 0;
				m_Speed = 0;
			}
			else
			{
				m_Dir = PointDirection(m_Owner->m_Pos, m_Points[m_Next]);
			}
		}
		else
		{
			m_Speed *= m_Friction;
			m_Owner->m_Pos += RotateVec(Vec2(m_Speed, 0), m_Dir);
		}
	}
}

void cPath::Render()
{
}

void cPath::Release()
{
}

void cPath::AddPath(float _Speed, float _Friction, Vec2 _End, Vec2 _Control)
{
	m_Speed = _Speed;
	m_Friction = _Friction;
	m_Points.clear();
	m_Next = 0;
	if (_Control == Vec2(0, 0))
	{
		m_Points.push_back(_End);
	}
	else
	{
		Vec2 v1, v2, v3;
		for (int i = 1; i <= 25; i++)
		{
			D3DXVec2Lerp(&v1, &m_Owner->m_Pos, &_Control, i * 0.04);
			D3DXVec2Lerp(&v2, &_Control, &_End, i * 0.04);
			D3DXVec2Lerp(&v3, &v1, &v2, i * 0.04);
			m_Points.push_back(v3);
		}
	}
	m_Dir = PointDirection(m_Owner->m_Pos, m_Points[0]);
}
