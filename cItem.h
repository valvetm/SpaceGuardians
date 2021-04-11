#pragma once
class cItem : public cComponent
{
public:
	cItem();
	~cItem();

	// Inherited via cComponent
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	float m_Speed;
	bool m_Magnetic;
};

