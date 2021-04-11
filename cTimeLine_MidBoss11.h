#pragma once
class cTimeLine_MidBoss11 : public cTimeLine
{
public:
	cTimeLine_MidBoss11();
	~cTimeLine_MidBoss11();

	// Inherited via cTimeLine
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

