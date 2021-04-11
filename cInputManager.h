#pragma once
class cInputManager : public cSingleton<cInputManager>
{
public:
	cInputManager();
	~cInputManager();

	void Init();
	void Update();
	void Render();
	void Release();

	bool m_Cur[128];
	bool m_Old[128];

	bool KeyDown(int _Key) { return m_Cur[_Key] && !m_Old[_Key]; }
	bool KeyPress(int _Key) { return m_Cur[_Key]; }
	bool KeyUp(int _Key) { return !m_Cur[_Key] && m_Old[_Key]; }
};

#define INPUT cInputManager::GetInstance()