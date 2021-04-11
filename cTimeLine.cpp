#include "DXUT.h"
#include "cTimeLine.h"
#include "cBullet.h"
#include "cBulletFriction.h"


cTimeLine::cTimeLine()
{
	m_Time = 0;
	m_Dir = 0;
	m_Tex[0] = IMAGE->Find("Explosion");
	m_Tex[1] = IMAGE->Find("Bullet2");
	m_Tex[2] = IMAGE->Find("Bullet3");
	m_Tex[3] = IMAGE->Find("Bullet4");
}


cTimeLine::~cTimeLine()
{
}

cObject * cTimeLine::FireBullet(Texture * _Image, Vec2 _Pos, float _Radius, float _Damage, float _Dir, float _Speed, D3DCOLOR _Color)
{
	cObject* a = OBJECT->AddObject("EnemyBullet", _Pos, 0.5, Obj_EnemyBullet);
	a->AddComponent<cBullet>()->m_Damage = _Damage;
	a->GetComponent<cBullet>()->m_Dir = _Dir;
	a->GetComponent<cBullet>()->m_Speed = _Speed;
	a->GetComponent<cBullet>()->m_FiredFrom = m_Owner;
	a->GetComponent<cBullet>()->m_FiredFromID = m_Owner->m_ID;
	a->GetComponent<cCollider>()->AddCollider(Vec2(0, 0), _Radius);
	a->GetComponent<cRenderer>()->m_Image = _Image;
	a->GetComponent<cRenderer>()->m_Color = _Color;
	return a;
}

cObject * cTimeLine::FireFrictionBullet(Texture * _Image, Vec2 _Pos, float _Radius, float _Damage, float _Dir, float _Speed, float _EndSpeed, float _Friction, D3DCOLOR _Color)
{
	cObject* a = OBJECT->AddObject("EnemyBullet", _Pos, 0.5, Obj_EnemyBullet);
	a->AddComponent<cBulletFriction>()->m_Damage = _Damage;
	a->GetComponent<cBulletFriction>()->m_Dir = _Dir;
	a->GetComponent<cBulletFriction>()->m_Speed = _Speed;
	a->GetComponent<cBulletFriction>()->m_EndSpeed = _EndSpeed;
	a->GetComponent<cBulletFriction>()->m_Friction = _Friction;
	a->GetComponent<cBulletFriction>()->m_FiredFrom = m_Owner;
	a->GetComponent<cBulletFriction>()->m_FiredFromID = m_Owner->m_ID;
	a->GetComponent<cCollider>()->AddCollider(Vec2(0, 0), _Radius);
	a->GetComponent<cRenderer>()->m_Image = _Image;
	a->GetComponent<cRenderer>()->m_Color = _Color;
	return a;
}

void cTimeLine::FireEffect(Vec2 _Pos, D3DCOLOR _Color)
{
	cParticle* Part = PART->AddParticle<cParticle>(m_Tex[0], _Pos, Vec2(0.1, 0.1), Random(0, 359), 0.45, _Color);
	Part->SetScale(Vec2(0.1, 0.1), 0.98);
	Part->SetAlpha(255, -5, 1.01);
}
