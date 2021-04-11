#pragma once
#include "cEnemy.h"
class cBoss1 : public cEnemy
{
public:
	cBoss1();
	~cBoss1();

	// Inherited via cEnemy
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void Death() override;

	float m_MaxHp;
	int m_Phase;
	bool m_Start;
	vector<cObject*> m_Parts;
	
	void NextPhase();
};

