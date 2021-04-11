#include "DXUT.h"
#include "cParticleBase.h"


cParticleBase::cParticleBase()
{
}


cParticleBase::~cParticleBase()
{
}

void cParticleBase::SetSpeed(float _Vel, float _Fri, float _Dir)
{
	m_PosVel = _Vel;
	m_PosFri = _Fri;
	m_Dir = _Dir;
}

void cParticleBase::SetScale(Vec2 _Vel, float _Fri)
{
	m_ScaleVel = _Vel;
	m_ScaleFri = _Fri;
}

void cParticleBase::SetRot(float _Vel, float _Fri)
{
	m_RotVel = _Vel;
	m_RotFri = _Fri;
}

void cParticleBase::SetAlpha(float _Val, float _Vel, float _Fri)
{
	m_Alpha = _Val;
	m_AlphaVel = _Vel;
	m_AlphaFri = _Fri;
}
