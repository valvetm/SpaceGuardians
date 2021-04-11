#pragma once
#include "cParticleBase.h"
class cParticleAnim : public cParticleBase
{
public:
	cParticleAnim();
	~cParticleAnim();

	// Inherited via cParticleBase
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	vector<Texture*>* m_Anim;
	int m_AnimSpeed = 0;
	int m_Frame = -1;
	int m_Timer = 0;
};

