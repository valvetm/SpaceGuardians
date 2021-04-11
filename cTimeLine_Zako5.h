#pragma once
class cTimeLine_Zako5 : public cTimeLine
{
public:
	cTimeLine_Zako5();
	~cTimeLine_Zako5();

	// Inherited via cTimeLine
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	float m_Angle;
};

