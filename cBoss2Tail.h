#pragma once
#include "cEnemy.h"
class cBoss2Tail : public cEnemy
{
public:
	cBoss2Tail();
	~cBoss2Tail();

	// Inherited via cEnemy
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void Death() override;

	cObject* m_Prev, *m_Next;
	cObject* m_Head;
	int m_Index;
};

