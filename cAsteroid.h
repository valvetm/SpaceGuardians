#pragma once
class cAsteroid : public cComponent
{
public:
	cAsteroid();
	~cAsteroid();

	// Inherited via cComponent
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	float m_Speed;
};

