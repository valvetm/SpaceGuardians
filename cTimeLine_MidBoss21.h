#pragma once
class cTimeLine_MidBoss21 : public cTimeLine
{
public:
	cTimeLine_MidBoss21();
	~cTimeLine_MidBoss21();

	// Inherited via cTimeLine
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

