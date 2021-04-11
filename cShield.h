#pragma once
class cShield : public cComponent
{
public:
	cShield();
	~cShield();

	// Inherited via cComponent
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	float m_Size;
};

