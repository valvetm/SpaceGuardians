#pragma once
class cBulletBase : public cComponent
{
public:
	cBulletBase();
	virtual ~cBulletBase();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

	float m_Speed;
	float m_Dir;
	float m_Damage;
	bool m_Grazed = false;
	bool m_Grazing = false;
	bool m_ReflectAble = true;
	cObject* m_FiredFrom = nullptr;
	int m_FiredFromID = 0;

	void IsOutMap();
	void OnReflect();
};

