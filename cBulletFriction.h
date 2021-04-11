#pragma once
#include "cBulletBase.h"
class cBulletFriction : public cBulletBase
{
public:
	cBulletFriction();
	~cBulletFriction();

	// Inherited via cBulletBase
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	float m_Friction;
	float m_EndSpeed;
};

