#pragma once
struct Collider
{
	Vec2 WorldPos;
	Vec2 LocalPos;
	float Radius;
};
class cCollider : public cComponent
{
public:
	cCollider();
	~cCollider();

	// Inherited via cComponent
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	vector<Collider> m_Colliders;
	vector<ObjectTag> m_CollWith;
	function<void(cObject* _Other)> m_CollFunc;

	void AddCollider(Vec2 _Pos, float _Radius);
};

