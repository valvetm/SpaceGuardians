#pragma once
class cTimeLine_Zako3 : public cTimeLine
{
public:
	cTimeLine_Zako3();
	~cTimeLine_Zako3();

	// Inherited via cTimeLine
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

