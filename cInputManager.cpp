#include "DXUT.h"


cInputManager::cInputManager()
{
}


cInputManager::~cInputManager()
{
}

void cInputManager::Init()
{
}

void cInputManager::Update()
{
	memcpy(m_Old, m_Cur, 128);
	memset(m_Cur, false, 128);
	for (int i = 0; i < 128; i++)
	{
		if (GetAsyncKeyState(i) & 0x8000)
		{
			m_Cur[i] = true;
		}
	}
}

void cInputManager::Render()
{
}

void cInputManager::Release()
{
}
