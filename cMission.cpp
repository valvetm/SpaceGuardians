#include "DXUT.h"
#include "cMission.h"


cMission::cMission()
{
}


cMission::~cMission()
{
}

void cMission::Init()
{
	m_OnGoing = false;
	m_Cleared = false;
}

void cMission::Update()
{
	if (!m_Cleared)
	{
		if (m_OnGoing)
		{
			m_Color = D3DCOLOR_ARGB(255, 255, 255, 255);
			m_Owner->m_Scale = Lerp<Vec2>(m_Owner->m_Scale, Vec2(1.5, 1.5), 0.1);
		}
		else
		{
			m_Color = D3DCOLOR_ARGB(150, 255, 255, 255);
			m_Owner->m_Scale = Lerp<Vec2>(m_Owner->m_Scale, Vec2(1, 1), 0.1);
		}
	}
	else
	{
		if (m_OnGoing)
		{
			m_Color = D3DCOLOR_ARGB(255, 255, 200, 50);
			m_Owner->m_Scale = Vec2(2.5, 2.5);
			m_OnGoing = false;
		}
		else
		{
			m_Owner->m_Scale = Lerp<Vec2>(m_Owner->m_Scale, Vec2(1, 1), 0.1);
		}
	}
}

void cMission::Render()
{
	IMAGE->CenterRenderTextView(m_Text, 16, m_Owner->m_Pos, m_Owner->m_Scale, 0.09, true, m_Color);
}

void cMission::Release()
{
}
