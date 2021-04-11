#include "DXUT.h"
#include "cCameraManager.h"


cCameraManager::cCameraManager()
{
}


cCameraManager::~cCameraManager()
{
}

void cCameraManager::Init()
{
	m_Pos = Vec2(960, 540);
	m_MoveTo = m_Pos;
	m_Scale = 1;
	m_ShakeForce = 0;
	m_ShakePos = Vec2(0, 0);
}

void cCameraManager::Update()
{
	if (m_ShakeForce != 0)
	{
		m_ShakeForce -= m_ShakeTime;
		if (m_ShakeForce <= 1)
		{
			m_ShakeForce = 0;
			m_ShakePos = Vec2(0, 0);
		}
		else
		{
			m_ShakePos = Vec2(Random(-m_ShakeForce, m_ShakeForce), Random(-m_ShakeForce, m_ShakeForce));
		}
	}

	if (m_MoveTo != m_Pos)
	{
		if (D3DXVec2Length(&(m_MoveTo - m_Pos)) <= m_Speed + 1)
		{
			m_Speed = 0;
			m_Pos = m_MoveTo;
			m_Scale = m_ScaleTo;
		}
		else
		{
			m_Speed *= m_Friction;
			Vec2 Dir;
			D3DXVec2Normalize(&Dir, &(m_MoveTo - m_Pos));
			m_Pos += Dir * m_Speed;
			m_Scale = Lerp<float>(m_ScaleTo, m_ScaleFrom, D3DXVec2Length(&(m_MoveTo - m_Pos)) / m_Dist);
		}
	}
	D3DXMatrixTransformation2D(&m_Mat, &Vec2(960, 540), 0, &(Vec2(1, 1) * m_Scale), NULL, 0, &(-m_Pos + Vec2(960, 540) + m_ShakePos));
}

void cCameraManager::Render()
{
	g_Device->SetTransform(D3DTS_VIEW, &m_Mat);
}

void cCameraManager::Release()
{
}

void cCameraManager::Shake(float _Force, float _Time)
{
	if (_Force <= m_ShakeForce)
		return;
	m_ShakeForce = _Force;
	m_ShakeTime = _Force / _Time;
}

void cCameraManager::MoveTo(Vec2 _To, float _Speed, float _Friction, float _Scale)
{
	m_MoveTo = _To;
	m_Speed = _Speed;
	m_Friction = _Friction;
	m_ScaleTo = _Scale;
	m_ScaleFrom = m_Scale;
	m_Dist = D3DXVec2Length(&(m_MoveTo - m_Pos));
}

Matrix cCameraManager::GetMatrix()
{
	Matrix Mat;
	D3DXMatrixInverse(&Mat, NULL, &m_Mat);
	return Mat;
}
