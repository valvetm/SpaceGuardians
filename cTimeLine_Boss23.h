#pragma once
class cTimeLine_Boss23 : public cTimeLine
{
public:
	cTimeLine_Boss23();
	~cTimeLine_Boss23();

	// Inherited via cTimeLine
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

