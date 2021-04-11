#pragma once
#include "cBulletBase.h"
class cBulletBFG : public cBulletBase
{
public:
	cBulletBFG();
	~cBulletBFG();

	// Inherited via cBulletBase
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	vector<Texture*>* m_Anim;
	float m_Charge;
	int m_Timer;
	int m_Frame;
};

