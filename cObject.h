#pragma once
#include "cComponent.h"
class cComponent;
enum ObjectTag
{
	Obj_Player,
	Obj_Enemy,
	Obj_PlayerBullet,
	Obj_EnemyBullet,
	Obj_Item,
	Obj_Asteroid,
	Obj_None,
	Obj_End
};
class cObject
{
public:
	cObject();
	~cObject();

	void Init();
	void Update();
	void Render();
	void Release();

	Vec2 m_Pos = Vec2(0,0);
	Vec2 m_Scale = Vec2(1,1);
	float m_Rot = 0;
	float m_Depth = 0;
	string m_Name = "";
	ObjectTag m_Tag = Obj_None;
	list<cComponent*> m_Components;
	bool m_Destroyed = false;
	int* m_Alarm = nullptr;
	int m_AlarmSize = 0;
	function<void(int _Index)> m_AlarmFunc;
	int m_ID = 0;

	void SetAlarmSize(int _Size) { m_Alarm = new int[_Size]; m_AlarmSize = _Size; for (int i = 0; i < _Size; i++) { m_Alarm[i] = -100; } }
	void SetAlarm(int _Index, int _Time) { m_Alarm[_Index] = _Time; }

	template<typename T>
	T* AddComponent()
	{
		T* a = new T;
		a->m_Owner = this;
		m_Components.push_back(a);
		a->Init();
		return a;
	}

	template<typename T>
	T* GetComponent()
	{
		for (auto& iter : m_Components)
		{
			if (typeid(*iter) == typeid(T))
			{
				return static_cast<T*>(iter);
			}
		}

		T* Cast;
		for (auto& iter : m_Components)
		{
			Cast = dynamic_cast<T*>(iter);
			if (Cast != nullptr)
			{
				return Cast;
			}
		}
		return nullptr;
	}
};

