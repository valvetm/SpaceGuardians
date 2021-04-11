#pragma once
class cParticleFunc : public cParticleBase
{
public:
	cParticleFunc();
	~cParticleFunc();

	function<void(cParticleFunc* _Part)> m_Func;

	// Inherited via cParticleBase
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

