#include "DXUT.h"
#include "cParticle.h"


cParticle::cParticle()
{
}


cParticle::~cParticle()
{
}

void cParticle::Init()
{
}

void cParticle::Update()
{
}

void cParticle::Render()
{
	IMAGE->CenterRender(m_Image, m_Pos, D3DXToRadian(m_Rot), m_Scale, m_Depth, m_Color);
}

void cParticle::Release()
{
}
