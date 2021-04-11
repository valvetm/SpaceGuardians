#pragma once
#include "cParticleBase.h"
class cParticle : public cParticleBase
{
public:
	cParticle();
	~cParticle();

	// Inherited via cParticleBase
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

