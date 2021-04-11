#pragma once
class cTimeLine_Zako6 : public cTimeLine
{
public:
	cTimeLine_Zako6();
	~cTimeLine_Zako6();

	// Inherited via cTimeLine
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

