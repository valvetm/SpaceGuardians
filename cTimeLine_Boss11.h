#pragma once
class cTimeLine_Boss11 : public cTimeLine
{
public:
	cTimeLine_Boss11();
	~cTimeLine_Boss11();

	// Inherited via cTimeLine
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

