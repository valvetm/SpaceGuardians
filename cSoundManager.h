#pragma once
class cSoundManager : public cSingleton<cSoundManager>
{
public:
	cSoundManager();
	~cSoundManager();

	void Init();
	void Update();
	void Render();
	void Release();

	list<LPDIRECTSOUNDBUFFER> m_Channels;
	map<string, CSound*> m_Sounds;
	CSoundManager m_Manager;

	void AddSound(string _Key, LPWSTR _Path);
	LPDIRECTSOUNDBUFFER Play(string _key, int _Volume, bool _Loop = false);
	void StopAll();
};

#define SOUND cSoundManager::GetInstance()