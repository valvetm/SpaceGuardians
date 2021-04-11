#pragma once
#include "cEnemy.h"
class cMidBoss2 : public cEnemy
{
public:
	cMidBoss2();
	~cMidBoss2();

	// Inherited via cEnemy
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void Death() override;

	float m_MaxHp;
	bool m_Start;
	bool m_Last;
	int m_Index;
};

