#pragma once
class cTimeLine_Zako8 : public cTimeLine
{
public:
	cTimeLine_Zako8();
	~cTimeLine_Zako8();

	// Inherited via cTimeLine
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

