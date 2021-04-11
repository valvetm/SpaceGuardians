#pragma once
#include "cParticle.h"
#include "cParticleAnim.h"
#include "cParticleBase.h"
#include "cParticleFunc.h"
#include "cParticleText.h"
class cParticleManager : public cSingleton<cParticleManager>
{
public:
	cParticleManager();
	~cParticleManager();

	void Init();
	void Update();
	void Render();
	void Release();

	list<cParticleBase*> m_Particles;

	template<typename T>
	T* AddParticle(Texture* _Image, Vec2 _Pos, Vec2 _Scale, float _Rot, float _Depth, D3DCOLOR _Color = 0xffffffff)
	{
		T* a = new T;
		a->m_Image = _Image;
		a->m_Pos = _Pos;
		a->m_Scale = _Scale;
		a->m_Rot = _Rot;
		a->m_Depth = _Depth;
		a->m_Color = _Color;
		a->Init();
		m_Particles.push_back(a);
		return a;
	}
};

#define PART cParticleManager::GetInstance()
