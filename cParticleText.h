#pragma once
class cParticleText : public cParticleBase
{
public:
	cParticleText();
	~cParticleText();

	// Inherited via cParticleBase
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	wstring m_Text;
	int m_Size;
	bool m_Kor = false;
};

