#include "DXUT.h"
#include "cParticleAnim.h"


cParticleAnim::cParticleAnim()
{
}


cParticleAnim::~cParticleAnim()
{
}

void cParticleAnim::Init()
{
}

void cParticleAnim::Update()
{
	m_Timer--;
	if (m_Timer <= 0)
	{
		m_Timer = m_AnimSpeed;
		m_Frame++;
		if (m_Frame == (*m_Anim).size())
		{
			m_Alpha = 0;
		}
	}
}

void cParticleAnim::Render()
{
	IMAGE->CenterRender((*m_Anim)[m_Frame], m_Pos, D3DXToRadian(m_Rot), m_Scale, m_Depth, m_Color);
}

void cParticleAnim::Release()
{
}
