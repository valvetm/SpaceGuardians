#pragma once
#include "cBullet.h"
#include "cBulletFriction.h"
class cTimeLine : public cComponent
{
public:
	cTimeLine();
	virtual ~cTimeLine();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

	int m_Time;
	Texture* m_Tex[4];
	float m_Dir;

	cObject* FireBullet(Texture* _Image, Vec2 _Pos, float _Radius, float _Damage, float _Dir, float _Speed, D3DCOLOR _Color);
	cObject* FireFrictionBullet(Texture* _Image, Vec2 _Pos, float _Radius, float _Damage, float _Dir, float _Speed, float _EndSpeed, float _Friction, D3DCOLOR _Color);
	void FireEffect(Vec2 _Pos, D3DCOLOR _Color);
};

