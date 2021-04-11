#include "DXUT.h"
#include "cPlayer.h"
#include "cBullet.h"
#include "cShield.h"
#include "cBomb.h"
#include "cEnemy.h"
#include "cBulletBFG.h"

cPlayer::cPlayer()
{
}


cPlayer::~cPlayer()
{
}

void cPlayer::Init()
{
	m_Dead = false;
	m_Shift = false;
	m_AttackAble = true;
	m_Level = SYSTEM->m_Level;
	m_Exp = SYSTEM->m_Exp;
	m_MaxExp = min(4000, 1000 * m_Level);
	m_MaxHp = ceil(100 * pow(1.2, m_Level - 1));
	m_Hp = m_MaxHp;
	m_BulletDamage = ceil(4 * pow(1.2, m_Level - 1));
	m_LaserDamage = ceil(1 * pow(1.4, m_Level - 1));
	m_Speed = 10;
	m_Damaged = 0;
	m_Charge = 0;
	m_Charging = false;
	m_ItemSound = true;
	m_Sound = SOUND->Play("Laser", -10000, true);
	OBJECT->m_Player = m_Owner;
	m_Owner->m_Scale = Vec2(0.3, 0.3);

	AddComponent<cRenderer>()->m_Image = IMAGE->Find("Player");
	AddComponent<cCollider>()->AddCollider(Vec2(0, 0), 40);
	GetComponent<cCollider>()->m_CollWith.push_back(Obj_EnemyBullet);
	GetComponent<cCollider>()->m_CollWith.push_back(Obj_Asteroid);
	GetComponent<cCollider>()->m_CollFunc = [&](cObject* _Other)->void {
		switch (_Other->m_Tag)
		{
		case Obj_EnemyBullet:
			_Other->GetComponent<cBulletBase>()->m_Grazed = true;
			_Other->GetComponent<cBulletBase>()->m_Grazing = true;
			if (D3DXVec2Length(&(m_Owner->m_Pos - _Other->m_Pos)) <= 5 + _Other->GetComponent<cCollider>()->m_Colliders[0].Radius)
			{
				_Other->m_Destroyed = true;
				m_Hp -= _Other->GetComponent<cBulletBase>()->m_Damage;
				m_Damaged = 255;
				SOUND->Play("Hit", -500);
				CAMERA->Shake(15, 30);
				if (m_Level >= 2)
				{
					cObject* a = OBJECT->AddObject("Shield", m_Owner->m_Pos, 0.4, Obj_None);
					a->AddComponent<cShield>()->m_Size = 50;
				}
			}
			break;

		case Obj_Asteroid:
			if (D3DXVec2Length(&(m_Owner->m_Pos - _Other->m_Pos)) <= 37)
			{
				_Other->m_Destroyed = true;
				m_Hp -= 50;
				m_Damaged = 255;
				SOUND->Play("Hit", -500);
				CAMERA->Shake(15, 30);
				cParticle* Part;
				char Text[16];
				for (int i = 0; i < 7; i++)
				{
					sprintf(Text, "Asteroid%d", Random(1, 6));
					Part = PART->AddParticle<cParticle>(IMAGE->Find(Text), _Other->m_Pos, Vec2(0.3, 0.3) * Random(0.75f, 1.25f), Random(0, 359), 0.51);
					Part->SetSpeed(Random(2.f, 7.f), 0.97, Random(0, 359));
					Part->SetRot(Random(-25, 25), 0.97);
					Part->SetScale(Vec2(-0.001, -0.001), 1.02);
				}
			}
			break;
		}
	};

	m_Owner->SetAlarmSize(4);
	m_Owner->SetAlarm(1, 0);
	m_Owner->SetAlarm(2, 0);
	m_Owner->m_AlarmFunc = [&](int _Index)->void {
		switch (_Index)
		{
		case 0:
			m_AttackAble = true;
			break;

		case 1:
			m_Skill[0] = true;
			break;

		case 2:
			m_Skill[1] = true;
			break;

		case 3:
			m_ItemSound = true;
			break;
		}
	};
}

void cPlayer::Update()
{
	if (m_Dead)
	{
		if (m_Exp > m_MaxExp)
			m_Exp = m_MaxExp;
		return;
	}

	if (INPUT->KeyPress(VK_LEFT) && m_Owner->m_Pos.x >= 420)
	{
		m_Owner->m_Pos.x -= m_Speed;
	}
	if (INPUT->KeyPress(VK_RIGHT) && m_Owner->m_Pos.x <= 1500)
	{
		m_Owner->m_Pos.x += m_Speed;
	}
	if (INPUT->KeyPress(VK_UP) && m_Owner->m_Pos.y >= 20)
	{
		m_Owner->m_Pos.y -= m_Speed;
	}
	if (INPUT->KeyPress(VK_DOWN) && m_Owner->m_Pos.y <= 1060)
	{
		m_Owner->m_Pos.y += m_Speed;
	}

	if (INPUT->KeyDown(VK_SHIFT))
	{
		m_Shift = true;
		m_Speed = 5;
	}
	if (INPUT->KeyUp(VK_SHIFT))
	{
		m_Shift = false;
		m_Speed = 10;
	}
	
	m_Sound->SetVolume(-10000);
	if (INPUT->KeyPress('Z') && !m_Charging)
	{
		if (!m_Shift)
		{
			if (m_AttackAble)
			{
				m_AttackAble = false;
				int Count = 2;
				if (m_Level == 2 || m_Level == 3)
					Count = 3;
				if (m_Level == 4 || m_Level == 5)
					Count = 4;

				cObject* a;
				char Text[16];
				sprintf(Text, "PlayerFire%d", Random(1, 14));

				for (int i = -Count; i <= Count; i++)
				{
					a = OBJECT->AddObject("PlayerBullet", m_Owner->m_Pos, 0.7, Obj_PlayerBullet);
					a->AddComponent<cBullet>()->m_Damage = m_BulletDamage;
					a->GetComponent<cBullet>()->m_Dir = 270 + (8 - Count) * i;
					a->GetComponent<cBullet>()->m_Speed = 25;
					a->GetComponent<cRenderer>()->m_Image = IMAGE->Find("Bullet1");
					a->GetComponent<cRenderer>()->m_Color = D3DCOLOR_ARGB(0x90, 250 - 50 * m_Level, 255, 255);
					a->GetComponent<cCollider>()->AddCollider(Vec2(0, 0), 16);
					a->m_Scale = Vec2(2, 2);
				}
			sprintf(Text, "PlayerFire%d", Random(1, 14));
			SOUND->Play(Text, -1500);
			m_Owner->SetAlarm(0, 14 - m_BulletDamage * 0.5);
			}
		}
		else
		{
			m_Sound->SetVolume(0);
			cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Laser"), m_Owner->m_Pos + Vec2(0, -900), Vec2(5, 0.4 * m_LaserDamage + 0.5), 90, 0.7, 0xffff0000);
			Part->SetScale(Vec2(-0.03, -0.01), 1.03);
			Part->SetAlpha(255, -10, 1);

			cParticleFunc* Func = PART->AddParticle<cParticleFunc>(IMAGE->Find("LaserPart"), m_Owner->m_Pos, Vec2(1, 1), 0, 0.69);
			Func->SetAlpha(255, -5, 1);
			Func->SetScale(Vec2(0, -0.03), 1);
			Func->m_Func = [](cParticleFunc* _Part)->void {
				_Part->m_Dir += 0.3 + Random(-0.02f, 0.02f);
				_Part->m_Pos.y -= 10;
				_Part->m_Pos.x += cos(_Part->m_Dir) * 15 * _Part->m_Scale.y;
				_Part->m_Rot = 90 + cos(_Part->m_Dir) * 45;
				_Part->m_Color = D3DCOLOR_ARGB((int)_Part->m_Alpha, 255, (int)max(0, 255 - _Part->m_Dir * 50), (int)max(0, 255 - _Part->m_Dir * 50));
			};

			Func = PART->AddParticle<cParticleFunc>(IMAGE->Find("LaserPart"), m_Owner->m_Pos, Vec2(1, 1), 0, 0.69);
			Func->SetAlpha(255, -5, 1);
			Func->SetScale(Vec2(0, -0.03), 1);
			Func->m_Func = [](cParticleFunc* _Part)->void {
				_Part->m_Dir += 0.3 + Random(-0.02f, 0.02f);
				_Part->m_Pos.y -= 10;
				_Part->m_Pos.x -= cos(_Part->m_Dir) * 15 * _Part->m_Scale.y;
				_Part->m_Rot = 90 - cos(_Part->m_Dir) * 45;
				_Part->m_Color = D3DCOLOR_ARGB((int)_Part->m_Alpha, 255, (int)max(0, 255 - _Part->m_Dir * 50), (int)max(0, 255 - _Part->m_Dir * 50));
			};

			char Text[16];
			for (auto& iter : OBJECT->m_Objects[Obj_Enemy])
			{
				for (auto& Coll : iter->GetComponent<cCollider>()->m_Colliders)
				{
					if (D3DXVec2Length(&(Vec2(m_Owner->m_Pos.x, Coll.WorldPos.y) - Coll.WorldPos)) <= m_LaserDamage * 5 + Coll.Radius &&
						m_Owner->m_Pos.y >= Coll.WorldPos.y)
					{
						iter->GetComponent<cEnemy>()->m_Hp -= m_LaserDamage;
						iter->GetComponent<cRenderer>()->m_Color = 0xffff0000;
						iter->SetAlarm(0, 3);
						for (auto& Coll : iter->GetComponent<cCollider>()->m_Colliders)
						{
							for (int i = 0; i < 4; i++)
							{
								sprintf(Text, "Spark%d", Random(1, 4));
								Part = PART->AddParticle<cParticle>(IMAGE->Find(Text), Coll.WorldPos + Vec2(Random(-Coll.Radius, Coll.Radius), Random(-Coll.Radius, Coll.Radius)), Vec2(0.1, 0.1), Random(0, 359), 0.5, 0xffff0000);
								Part->SetAlpha(255 * Random(1, 4), -255, 1);
							}
						}
						break;
					}
				}
			}
		}
	}

	if (INPUT->KeyDown('C') && !m_Charging)
	{
		m_Charging = true;
		m_BFGSound = SOUND->Play("BFGCharge", -500);
	}
	if ((!INPUT->KeyPress('C') && m_Charge >= 15) || m_Charge == 180)
	{
		cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Ring"), m_Owner->m_Pos, Vec2(0.1, 0.1), 0, 0.49, 0xff00ffff);
		Part->SetScale(Vec2(0.001, 0.001) * m_Charge, 0.98);
		Part->SetAlpha(255, -2, 1.01);
		m_BFGSound->Stop();
		SOUND->Play("BFGFire", 0);
		m_Charging = false;
		cObject* a = OBJECT->AddObject("BFG", m_Owner->m_Pos, 0.5, Obj_PlayerBullet);
		a->AddComponent<cBulletBFG>()->m_Speed = 4;
		a->GetComponent<cBulletBFG>()->m_Dir = 270;
		a->GetComponent<cBulletBFG>()->m_Damage = m_Charge * 0.5 * (float)m_Level + 100;
		a->GetComponent<cBulletBFG>()->m_Charge = m_Charge * 0.5 * (float)m_Level + 40;
		a->m_Scale = (Vec2(0.5, 0.5) / 360) * (m_Charge * 0.5 * (float)m_Level + 40);
		a->GetComponent<cCollider>()->AddCollider(Vec2(0, 0), (120 / 360) * (m_Charge * 0.5 * (float)m_Level + 40));
		CAMERA->Shake(m_Charge * 0.05, 60);
		m_Charge = 0;
		if (m_Shift)
			m_Speed = 5;
		else
			m_Speed = 10;
	}
	if (m_Charging)
	{
		m_Speed = 2;
		m_Charge++;
		switch ((int)m_Charge)
		{
		case 1:
		case 30:
		case 57:
		case 81:
		case 102:
		case 120:
		case 135:
		case 147:
		{
			cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Shield"), m_Owner->m_Pos, Vec2(0.0025, 0.0025) * m_Charge, 0, 0.49, 0xff00ffff);
			Part->SetScale(Vec2(-0.002, -0.002), 1.05);
			Part->SetAlpha(255, -2, 1.01);
		}
		break;
		}

		char Text[16];
		cParticle* Part;
		for (int i = 0; i < 3; i++)
		{
			sprintf(Text, "Spark%d", Random(1, 4));
			Part = PART->AddParticle<cParticle>(IMAGE->Find(Text), m_Owner->m_Pos + Vec2(Random(-64, 64), Random(-64, 64)) * m_Owner->m_Scale.x, Vec2(0.001, 0.001) * m_Charge, Random(0, 359), 0.49, 0xff00ffff);
			Part->SetAlpha(255 * Random(1, 4), -255, 1);
		}
	}

	if (INPUT->KeyDown('X'))
	{
		if (m_Skill[0] && m_Level >= 3)
		{
			cObject* a = OBJECT->AddObject("Shield", m_Owner->m_Pos, 0.4, Obj_None);
			a->AddComponent<cShield>();
			m_Skill[0] = false;
			m_Owner->SetAlarm(1, 15 * 60);
		}
		else
		{
			cParticleText* Text = PART->AddParticle<cParticleText>(NULL, Vec2(960, 350), Vec2(2, 2), 0, 0.09, 0xffff0000);
			Text->m_Size = 32;
			Text->m_Kor = true;
			Text->SetAlpha(255, -2, 1);
			Text->m_Text = L"아직 사용할 수 없습니다.";
		}
	}

	if (INPUT->KeyDown(VK_SPACE))
	{
		if (m_Skill[1] && m_Level >= 5)
		{
			cObject* a = OBJECT->AddObject("Bomb", m_Owner->m_Pos, 0.4, Obj_None);
			a->AddComponent<cBomb>();
			m_Skill[1] = false;
			m_Owner->SetAlarm(2, 60 * 60);
		}
		else
		{
			cParticleText* Text = PART->AddParticle<cParticleText>(NULL, Vec2(960, 350), Vec2(2, 2), 0, 0.09, 0xffff0000);
			Text->m_Size = 32;
			Text->m_Kor = true;
			Text->SetAlpha(255, -2, 1);
			Text->m_Text = L"아직 사용할 수 없습니다.";
		}
	}

	if (m_Exp >= m_MaxExp && m_Level != 5)
	{
		m_Exp -= m_MaxExp;
		m_Level++;
		m_MaxExp = min(4000, 1000 * m_Level);
		m_MaxHp = ceil(100 * pow(1.2, m_Level - 1));
		m_Hp = m_MaxHp;
		m_BulletDamage = ceil(4 * pow(1.2, m_Level - 1));
		m_LaserDamage = ceil(1 * pow(1.4, m_Level - 1));

		SOUND->Play("Level", -500);
		if (m_Level == 5)
		{
			m_Exp = 4000;
			m_MaxExp = 4000;
		}

		for (auto& iter : OBJECT->m_Objects[Obj_EnemyBullet])
		{
			iter->m_Destroyed = true;
		}

		cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Ring"), m_Owner->m_Pos, Vec2(0.1, 0.1), 0, 0.4, D3DCOLOR_XRGB(255, 200, 50));
		Part->SetScale(Vec2(0.2, 0.2), 0.98);
		Part->SetAlpha(255, -1, 1.1);

		cParticleText* Text = PART->AddParticle<cParticleText>(NULL, Vec2(960, 300), Vec2(2, 2), 0, 0.09, D3DCOLOR_XRGB(255, 200, 50));
		Text->m_Size = 24;
		Text->m_Kor = true;
		Text->SetAlpha(255, -1, 1);
		switch (m_Level)
		{
		case 2:
			Text->m_Text = L"----------레벨 업!: 2 레벨----------\n피격 시 자동으로 쉴드가 전개됩니다.";
			break;
		case 3:
			Text->m_Text = L"----------레벨 업!: 3 레벨----------\nX를 눌러 쉴드를 사용할 수 있습니다.";
			break;
		case 4:
			Text->m_Text = L"----------레벨 업!: 4 레벨----------\n튕겨낸 탄이 적을 추적합니다.";
			break;
		case 5:
			Text->m_Text = L"----------레벨 업!: 5 레벨----------\n스페이스 바를 눌러 폭탄을 사용할 수 있습니다.";
			break;
		}
	}

	if (m_Owner->m_Pos.y <= 200)
	{
		for (auto& iter : OBJECT->m_Objects[Obj_Item])
		{
			iter->GetComponent<cItem>()->m_Magnetic = true;
		}
	}

	if (m_Hp <= 0 && m_Dead == false)
	{
		m_Dead = true;
		m_Hp = 0;
		if (m_Exp > m_MaxExp)
			m_Exp = m_MaxExp;
		GetComponent<cRenderer>()->m_Enable = false;
		GetComponent<cCollider>()->m_Enable = false;
		for (auto& iter : OBJECT->m_Objects[Obj_Item])
		{
			iter->GetComponent<cItem>()->m_Magnetic = false;
		}

		cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos, Vec2(4, 4) * Random(0.75f, 1.25f), Random(0, 359), 0.5);
		Anim->m_Anim = IMAGE->FindAnimation("Explosion");
		Anim->m_AnimSpeed = Random(1, 3);


		cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Ring"), m_Owner->m_Pos, Vec2(0.1, 0.1), 0, 0.4);
		Part->SetScale(Vec2(0.2, 0.2), 0.98);
		Part->SetAlpha(255, -1, 1.1);

		Part = PART->AddParticle<cParticle>(IMAGE->Find("Back1"), Vec2(0, 0), Vec2(1, 1), 0, 0.01, 0x00000000);
		Part->SetAlpha(0, 2, 1);

		char Text[16];
		sprintf(Text, "Explosion%d", Random(1, 4));
		SOUND->Play(Text, -500);
		CAMERA->Shake(30, 180);
		CAMERA->MoveTo(m_Owner->m_Pos, 6, 0.99, 2);
		SYSTEM->m_Alarm[2] = 360;

		cParticleText* TextPart = PART->AddParticle<cParticleText>(NULL, Vec2(960, 500), Vec2(5, 0), 0, 0, 0xffff0000);
		TextPart->m_Size = 32;
		TextPart->m_Text = L"YOU DIED...";
		TextPart->SetScale(Vec2(0, 0.05), 0.99);

		cParticleFunc* Func;
		for (auto& Coll : GetComponent<cCollider>()->m_Colliders)
		{
			for (int i = 0; i < 7; i++)
			{
				sprintf(Text, "Debris%d", Random(1, 6));
				Func = PART->AddParticle<cParticleFunc>(IMAGE->Find(Text), Coll.WorldPos, Vec2(0.6, 0.6) * Random(0.75f, 1.25f), Random(0, 359), 0.51);
				Func->SetSpeed(Random(2.f, 7.f), 0.97, Random(0, 359));
				Func->SetRot(Random(-25, 25), 0.97);
				Func->SetScale(Vec2(-0.001, -0.001), 1.04);
				Func->m_Func = [](cParticleFunc* _Part)->void {
					char Text[16];
					sprintf(Text, "Smoke%d", Random(1, 3));
					cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find(Text), _Part->m_Pos, Vec2(0.25, 0.25) * _Part->m_Scale.x, Random(0, 359), 0.505, 0xff909090);
					Part->SetScale(Vec2(-0.003, -0.003), 1);
					Part->SetAlpha(255, -4, 1);
				};
			}
		}
	}

	m_Damaged -= 3;
}

void cPlayer::Render()
{
	if (m_Hp < 0)
		m_Hp = 0;
	IMAGE->RenderView(IMAGE->Find("Damaged"), Vec2(0, 0), 0, Vec2(1, 1), 0.02, D3DCOLOR_ARGB(max(0, m_Damaged), 255, 255, 255));
	if (m_Dead)
		return;
	if (m_Shift)
		IMAGE->CenterRender(IMAGE->Find("Point"), m_Owner->m_Pos, 0, Vec2(1, 1), 0.11);
}

void cPlayer::Release()
{
	OBJECT->m_Player = nullptr;
	SYSTEM->m_Level = m_Level;
	SYSTEM->m_Exp = m_Exp;
}

void cPlayer::AddExp(float _Exp, Vec2 _Pos)
{
	SYSTEM->m_Score += _Exp * 100000;
	cObject* a;
	for (int i = 0; i < ceil(_Exp * 0.1); i++)
	{
		a = OBJECT->AddObject("Item_Score", _Pos + Vec2(Random(-75, 75), Random(-75, 75)), 0.41, Obj_Item);
		a->AddComponent<cItem>();
	}
	if (m_Level == 5)
		return;

	m_Exp += _Exp;

	TCHAR Exp[16];
	swprintf(Exp, L"%dEXP+", (int)_Exp);

	cParticleText* Text = PART->AddParticle<cParticleText>(NULL, _Pos, Vec2(1, 1.5), 0, 0.3, D3DCOLOR_XRGB(255, 200, 50));
	Text->m_Text = Exp;
	Text->m_Size = 32;
	Text->SetSpeed(3, 0.99, 270);
	Text->SetScale(Vec2(0, -0.01), 1);
}
