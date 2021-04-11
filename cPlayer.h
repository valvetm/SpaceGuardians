#pragma once
class cPlayer : public cComponent
{
public:
	cPlayer();
	~cPlayer();

	// Inherited via cComponent
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	bool m_AttackAble;
	bool m_Skill[2];
	bool m_Dead;
	bool m_Shift;
	float m_Speed;
	float m_MaxExp;
	float m_Exp;
	float m_MaxHp;
	float m_Hp;
	float m_BulletDamage;
	float m_LaserDamage;
	int m_Level;
	int m_Damaged;
	float m_Charge;
	bool m_Charging;
	bool m_ItemSound;
	LPDIRECTSOUNDBUFFER m_Sound;
	LPDIRECTSOUNDBUFFER m_BFGSound;

	void AddExp(float _Exp, Vec2 _Pos);
};

