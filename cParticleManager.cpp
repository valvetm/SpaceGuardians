#include "DXUT.h"
#include "cParticleManager.h"


cParticleManager::cParticleManager()
{
}


cParticleManager::~cParticleManager()
{
}

void cParticleManager::Init()
{
}

void cParticleManager::Update()
{
	for (auto& iter = m_Particles.begin(); iter != m_Particles.end();)
	{
		(*iter)->m_PosVel *= (*iter)->m_PosFri;
		(*iter)->m_ScaleVel *= (*iter)->m_ScaleFri;
		(*iter)->m_RotVel *= (*iter)->m_RotFri;
		(*iter)->m_AlphaVel *= (*iter)->m_AlphaFri;

		(*iter)->m_Pos += RotateVec(Vec2((*iter)->m_PosVel, 0), (*iter)->m_Dir);
		(*iter)->m_Scale += (*iter)->m_ScaleVel;
		(*iter)->m_Rot += (*iter)->m_RotVel;
		(*iter)->m_Alpha += (*iter)->m_AlphaVel;

		(*iter)->m_Color = ((*iter)->m_Color & 0x00ffffff) | ((int)min(255, (*iter)->m_Alpha) << 24);
		(*iter)->Update();

		if ((*iter)->m_Alpha <= 0 || (*iter)->m_Scale.x <= 0 || (*iter)->m_Scale.y <= 0)
		{
			(*iter)->Release();
			SAFE_DELETE(*iter);
			iter = m_Particles.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void cParticleManager::Render()
{
	for (auto& iter : m_Particles)
	{
		iter->Render();
	}
}

void cParticleManager::Release()
{
	for (auto& iter : m_Particles)
	{
		iter->Release();
		SAFE_DELETE(iter);
	}
	m_Particles.clear();
}
