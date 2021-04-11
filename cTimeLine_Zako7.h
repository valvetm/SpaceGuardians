#pragma once
class cTimeLine_Zako7 : public cTimeLine
{
public:
	cTimeLine_Zako7();
	~cTimeLine_Zako7();

	// Inherited via cTimeLine
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

