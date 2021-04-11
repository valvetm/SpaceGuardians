#pragma once
class cBomb : public cComponent
{
public:
	cBomb();
	~cBomb();

	// Inherited via cComponent
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	int m_Timer;
};

