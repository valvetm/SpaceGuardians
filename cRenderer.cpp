#include "DXUT.h"
#include "cRenderer.h"


cRenderer::cRenderer()
{
}


cRenderer::~cRenderer()
{
}

void cRenderer::Init()
{
}

void cRenderer::Update()
{
}

void cRenderer::Render()
{
	IMAGE->CenterRender(m_Image, m_Owner->m_Pos, D3DXToRadian(m_Owner->m_Rot), m_Owner->m_Scale, m_Owner->m_Depth, m_Color);
}

void cRenderer::Release()
{
}
