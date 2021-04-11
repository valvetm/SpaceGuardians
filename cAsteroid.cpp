#include "DXUT.h"
#include "cAsteroid.h"


cAsteroid::cAsteroid()
{
}


cAsteroid::~cAsteroid()
{
}

void cAsteroid::Init()
{
	char Text[16];
	sprintf(Text, "Asteroid%d", Random(1, 6));
	Texture* Tex = IMAGE->Find(Text);
	AddComponent<cRenderer>()->m_Image = Tex;
	AddComponent<cCollider>()->AddCollider(Vec2(0, 0), 32);
	GetComponent<cCollider>()->m_CollWith.push_back(Obj_EnemyBullet);
	GetComponent<cCollider>()->m_CollWith.push_back(Obj_PlayerBullet);
	GetComponent<cCollider>()->m_CollFunc = [&](cObject* _Other)->void {
		_Other->m_Destroyed = true;
	};
	m_Owner->m_Scale = Vec2(64.f / (float)Tex->Info.Width, 64.f / (float)Tex->Info.Height);
	m_Owner->m_Rot = Random(0, 359);
}

void cAsteroid::Update()
{
	m_Owner->m_Pos.y += m_Speed;
	if (m_Owner->m_Pos.y >= 1150)
	{
		m_Owner->m_Destroyed = true;
	}
}

void cAsteroid::Render()
{
}

void cAsteroid::Release()
{
}
