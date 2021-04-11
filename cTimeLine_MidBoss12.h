#pragma once
class cTimeLine_MidBoss12 : public cTimeLine
{
public:
	cTimeLine_MidBoss12();
	~cTimeLine_MidBoss12();

	// Inherited via cTimeLine
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

