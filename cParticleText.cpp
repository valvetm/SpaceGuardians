#include "DXUT.h"
#include "cParticleText.h"


cParticleText::cParticleText()
{
}


cParticleText::~cParticleText()
{
}

void cParticleText::Init()
{
}

void cParticleText::Update()
{
}

void cParticleText::Render()
{
	if (m_Depth > 0.1f)
		IMAGE->CenterRenderText(m_Text, m_Size, m_Pos, m_Scale, m_Depth, m_Kor, m_Color);
	else
		IMAGE->CenterRenderTextView(m_Text, m_Size, m_Pos, m_Scale, m_Depth, m_Kor, m_Color);
}

void cParticleText::Release()
{
}
