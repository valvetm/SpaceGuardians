#pragma once
class cTimeLine_Boss21 : public cTimeLine
{
public:
	cTimeLine_Boss21();
	~cTimeLine_Boss21();

	// Inherited via cTimeLine
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

