#pragma once
#include "cMission.h"
#include "cZako.h"
#include "cAsteroid.h"
class cStage2Scene : public cScene
{
public:
	cStage2Scene();
	~cStage2Scene();

	// Inherited via cScene
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	float m_BackPos;
	float m_BackSpeed;
	float m_BackVel;
	float m_BackEnd;
	int m_Time;
	cMission* m_Missions[4];

	template<typename T>
	cObject* AddZako(string _Name, Vec2 _Pos, float _Hp, float _Exp)
	{
		cObject* a = OBJECT->AddObject(_Name, _Pos, 0.6, Obj_Enemy);
		a->AddComponent<cZako>()->m_Hp = _Hp;
		a->GetComponent<cZako>()->m_Exp = _Exp;
		a->AddComponent<T>();
		return a;
	}

	void AddPath(cObject* _Obj, float _Speed, float _Friction, Vec2 _End, Vec2 _Control = Vec2(0, 0))
	{
		_Obj->GetComponent<cPath>()->AddPath(_Speed, _Friction, _End, _Control);
	}

	void AddAsteroid(int _XFrom, int _XTo, int _YFrom, int _YTo, float _Speed)
	{
		cObject* a;
		for (int i = _XFrom; i <= _XTo; i++)
		{
			for (int j = _YFrom; j <= _YTo; j++)
			{
				a = OBJECT->AddObject("Asteroid", Vec2(384 + i * 64, -56 - j * 64), 0.69, Obj_Asteroid);
				a->AddComponent<cAsteroid>()->m_Speed = _Speed;
			}
		}
	}
};

