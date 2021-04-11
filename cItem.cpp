#include "DXUT.h"
#include "cItem.h"
#include "cPlayer.h"


cItem::cItem()
{
}


cItem::~cItem()
{
}

void cItem::Init()
{
	AddComponent<cRenderer>()->m_Image = IMAGE->Find(m_Owner->m_Name);
	AddComponent<cCollider>()->AddCollider(Vec2(0, 0), 5);
	GetComponent<cCollider>()->m_CollWith.push_back(Obj_Player);
	GetComponent<cCollider>()->m_CollFunc = [&](cObject* _Other)->void {
		cPlayer* Player = _Other->GetComponent<cPlayer>();
		if (m_Owner->m_Name == "Item_Hp")
		{
			Player->m_Hp = min(Player->m_MaxHp, Player->m_Hp + Player->m_MaxHp * 0.2);
		}
		else if (m_Owner->m_Name == "Item_Time")
		{
			_Other->SetAlarm(1, 0);
			_Other->SetAlarm(2, 0);
		}
		else if(m_Owner->m_Name == "Item_Level")
		{
			Player->m_Exp += Player->m_MaxExp;
		}
		else
		{
			SYSTEM->m_Score += 100000;
			SYSTEM->m_ScoreItem++;
		}
		if (Player->m_ItemSound)
		{
			SOUND->Play("Item", 0);
			Player->m_ItemSound = false;
			Player->m_Owner->SetAlarm(3, 5);
		}
		m_Owner->m_Destroyed = true;
	};
	m_Speed = -5;
	m_Magnetic = false;
}

void cItem::Update()
{
	if (m_Speed < 5)
	{
		m_Speed += 0.075;
	}
	if ((D3DXVec2Length(&(m_Owner->m_Pos - OBJECT->m_Player->m_Pos)) <= 150 || m_Magnetic) && OBJECT->m_Player->GetComponent<cPlayer>()->m_Dead == false)
	{
		m_Magnetic = true;
		Vec2 Dir;
		D3DXVec2Normalize(&Dir, &(OBJECT->m_Player->m_Pos - m_Owner->m_Pos));
		m_Owner->m_Pos += 11 * Dir;
	}
	else
	{
		m_Owner->m_Pos.y += m_Speed;
	}

	if (m_Owner->m_Pos.y >= 1200)
	{
		m_Owner->m_Destroyed = true;
	}
}

void cItem::Render()
{
}

void cItem::Release()
{
}
