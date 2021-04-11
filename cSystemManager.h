#pragma once
struct RankData
{
	wstring Name;
	int Score;
};
class cSystemManager : public cSingleton<cSystemManager>
{
public:
	cSystemManager();
	~cSystemManager();

	void Init();
	void Update();
	void Render();
	void Release();

	list<RankData> m_Rank;
	float m_Score;
	int m_Level;
	float m_Exp;
	bool m_Win;
	int m_Alarm[4];
	int m_Reflected;
	int m_ScoreItem;

	void SortRank();
	void PlayerInit();
	void OnSceneChange();
};

#define SYSTEM cSystemManager::GetInstance()