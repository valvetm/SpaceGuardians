#pragma once
class cParticleBase
{
public:
	cParticleBase();
	virtual ~cParticleBase();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

	Texture* m_Image;
	D3DCOLOR m_Color = 0xffffffff;
	float m_Depth = 0;

	Vec2 m_Pos = Vec2(0, 0);
	float m_PosVel = 0;
	float m_PosFri = 1;
	float m_Dir = 0;

	Vec2 m_Scale = Vec2(1, 1);
	Vec2 m_ScaleVel = Vec2(0, 0);
	float m_ScaleFri = 1;
	
	float m_Rot = 0;
	float m_RotVel = 0;
	float m_RotFri = 1;

	float m_Alpha = 255;
	float m_AlphaVel = 0;
	float m_AlphaFri = 1;

	void SetSpeed(float _Vel, float _Fri, float _Dir);
	void SetScale(Vec2 _Vel, float _Fri);
	void SetRot(float _Vel, float _Fri);
	void SetAlpha(float _Val, float _Vel, float _Fri);
};

