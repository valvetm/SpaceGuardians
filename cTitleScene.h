#pragma once
class cTitleScene : public cScene
{
public:
	cTitleScene();
	~cTitleScene();

	// Inherited via cScene
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	bool m_OnTitle;
	Vec2 m_Scale[4];
	D3DCOLOR m_Color[4];
	wstring m_Text[4];
	int m_Selected;
};

