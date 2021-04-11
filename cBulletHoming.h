#pragma once
#include "cBulletBase.h"
class cBulletHoming : public cBulletBase
{
public:
	cBulletHoming();
	~cBulletHoming();

	// Inherited via cBulletBase
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	cObject* m_Target = nullptr;
	int m_TargetID = 0;
};

