#include "DXUT.h"
#include "cParticleFunc.h"


cParticleFunc::cParticleFunc()
{
}


cParticleFunc::~cParticleFunc()
{
}

void cParticleFunc::Init()
{
}

void cParticleFunc::Update()
{
	m_Func(this);
}

void cParticleFunc::Render()
{
	IMAGE->CenterRender(m_Image, m_Pos, D3DXToRadian(m_Rot), m_Scale, m_Depth, m_Color);
}

void cParticleFunc::Release()
{
}
