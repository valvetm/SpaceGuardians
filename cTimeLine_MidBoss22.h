#pragma once
class cTimeLine_MidBoss22 : public cTimeLine
{
public:
	cTimeLine_MidBoss22();
	~cTimeLine_MidBoss22();

	// Inherited via cTimeLine
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

