#pragma once
class cPath : public cComponent
{
public:
	cPath();
	~cPath();

	// Inherited via cComponent
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	vector<Vec2> m_Points;
	int m_Next;
	float m_Speed;
	float m_Dir;
	float m_Friction;

	void AddPath(float _Speed, float _Friction, Vec2 _End, Vec2 _Control = Vec2(0, 0));
};

