#pragma once
#include "cEnemy.h"
class cMidBoss1 : public cEnemy
{
public:
	cMidBoss1();
	~cMidBoss1();

	// Inherited via cEnemy
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void Death() override;

	float m_MaxHp;
	bool m_Start;
};

