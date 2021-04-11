#pragma once
class cTimeLine_Zako9 : public cTimeLine
{
public:
	cTimeLine_Zako9();
	~cTimeLine_Zako9();

	// Inherited via cTimeLine
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

