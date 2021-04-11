#pragma once
#include "cEnemy.h"
class cBoss2 : public cEnemy
{
public:
	cBoss2();
	~cBoss2();

	// Inherited via cEnemy
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void Death() override;

	float m_MaxHp;
	bool m_Start;
	int m_Phase;
	cObject* m_Next;
};

