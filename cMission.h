#pragma once
class cMission : public cComponent
{
public:
	cMission();
	~cMission();

	// Inherited via cComponent
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	D3DCOLOR m_Color;
	wstring m_Text;
	bool m_OnGoing;
	bool m_Cleared;
};

