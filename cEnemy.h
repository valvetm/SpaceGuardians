#pragma once
#include "cBulletBase.h"
#include "cItem.h"
#include "cPlayer.h"
class cEnemy : public cComponent
{
public:
	cEnemy();
	~cEnemy();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
	virtual void Death() = 0;

	float m_Hp;
	float m_Exp;

};

