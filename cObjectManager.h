#pragma once
#include "cObject.h"
class cObjectManager : public cSingleton<cObjectManager>
{
public:
	cObjectManager();
	~cObjectManager();

	void Init();
	void Update();
	void Render();
	void Release();

	list<cObject*> m_Objects[Obj_End];
	cObject* m_Player = nullptr;
	int m_ID = 1;

	cObject* AddObject(string _Name, Vec2 _Pos, float _Depth, ObjectTag _Tag);
	void CollisionCheck(cObject* _Object);

};

#define OBJECT cObjectManager::GetInstance()