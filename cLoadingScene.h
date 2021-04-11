#pragma once
class cLoadingScene : public cScene
{
public:
	cLoadingScene();
	~cLoadingScene();

	// Inherited via cScene
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void LoadImage(string _Key, string _Path, int _Amount = 1);
	void LoadSound(string _Key, LPWSTR _Path, int _Amount = 1);
};

