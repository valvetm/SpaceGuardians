#pragma once
#include "cEnemy.h"
class cZako : public cEnemy
{
public:
	cZako();
	~cZako();

	// Inherited via cEnemy
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void Death() override;

	void IsOutMap();
};

