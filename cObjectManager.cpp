#include "DXUT.h"
#include "cObjectManager.h"


cObjectManager::cObjectManager()
{
}


cObjectManager::~cObjectManager()
{
}

void cObjectManager::Init()
{
}

void cObjectManager::Update()
{
	for (int Tag = 0; Tag < Obj_End; Tag++)
	{
		for (auto& iter = m_Objects[Tag].begin(); iter != m_Objects[Tag].end();)
		{
			if ((*iter)->m_Destroyed)
			{
				(*iter)->Release();
				SAFE_DELETE(*iter);
				iter = m_Objects[Tag].erase(iter);
			}
			else
			{
				(*iter)->Update();
				CollisionCheck(*iter);
				iter++;
			}
		}
	}
}

void cObjectManager::Render()
{
	for (int Tag = 0; Tag < Obj_End; Tag++)
	{
		for (auto& iter : m_Objects[Tag])
		{
			iter->Render();
		}
	}
}

void cObjectManager::Release()
{
	for (int Tag = 0; Tag < Obj_End; Tag++)
	{
		for (auto& iter : m_Objects[Tag])
		{
			iter->Release();
			SAFE_DELETE(iter);
		}
		m_Objects[Tag].clear();
	}
	m_ID = 1;
}

cObject* cObjectManager::AddObject(string _Name, Vec2 _Pos, float _Depth, ObjectTag _Tag)
{
	cObject* a = new cObject;
	a->m_Name = _Name;
	a->m_Pos = _Pos;
	a->m_Depth = _Depth;
	a->m_Tag = _Tag;
	a->m_ID = m_ID;
	m_ID++;
	m_Objects[_Tag].push_back(a);
	return a;
}

void cObjectManager::CollisionCheck(cObject * _Object)
{
	cCollider* Self = _Object->GetComponent<cCollider>();
	if (Self == nullptr || Self->m_Enable == false)
		return;

	cCollider* Other;
	for (auto& Tag : Self->m_CollWith)
	{
		for (auto& iter : m_Objects[Tag])
		{
			Other = iter->GetComponent<cCollider>();
			if (Other->m_Enable == false)
				continue;
			for (auto& SelfColl : Self->m_Colliders)
			{
				for (auto& OtherColl : Other->m_Colliders)
				{
					if (D3DXVec2Length(&(SelfColl.WorldPos - OtherColl.WorldPos)) <= SelfColl.Radius + OtherColl.Radius)
					{
						Self->m_CollFunc(iter);
						goto Next;
					}
				}
			}
		Next:
			continue;
		}
	}
}
