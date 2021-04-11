#pragma once
#include "cBulletBase.h"
class cBullet : public cBulletBase
{
public:
	cBullet();
	~cBullet();

	// Inherited via cBulletBase
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

