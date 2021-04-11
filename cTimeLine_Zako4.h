#pragma once
class cTimeLine_Zako4 : public cTimeLine
{
public:
	cTimeLine_Zako4();
	~cTimeLine_Zako4();

	// Inherited via cTimeLine
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

