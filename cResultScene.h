#pragma once
class cResultScene : public cScene
{
public:
	cResultScene();
	~cResultScene();

	// Inherited via cScene
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	wstring m_Name;
	bool m_OnTyping;
};

