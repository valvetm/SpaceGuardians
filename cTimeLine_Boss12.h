#pragma once
class cTimeLine_Boss12 : public cTimeLine
{
public:
	cTimeLine_Boss12();
	~cTimeLine_Boss12();

	// Inherited via cTimeLine
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

