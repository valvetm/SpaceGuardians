#pragma once
#include "cSingleton.h"
struct Texture
{
	LPDIRECT3DTEXTURE9 Image;
	D3DXIMAGE_INFO Info;
};
class cImageManager : public cSingleton<cImageManager>
{
public:
	cImageManager();
	~cImageManager();

	void Init();
	void Update();
	void Render();
	void Release();
	void Begin();
	void End();

	map<string, Texture*> m_Images;
	map<string, vector<Texture*>*> m_Animations;
	LPD3DXFONT m_Fonts[33];
	LPD3DXFONT m_FontsKor[33];
	LPD3DXSPRITE m_Sprite;

	Matrix m_Mat;
	RECT m_Rect;
	Vec2 m_Center;

	void AddImage(string _Key, string _Path);
	void AddAnimation(string _Key, int _Amount);
	Texture* Find(string _Key);
	vector<Texture*>* FindAnimation(string _Key);

	void Render(Texture* _Image, Vec2 _Pos, float _Rot, Vec2 _Scale, float _Depth, D3DCOLOR _Color = 0xffffffff);
	void CenterRender(Texture* _Image, Vec2 _Pos, float _Rot, Vec2 _Scale, float _Depth, D3DCOLOR _Color = 0xffffffff);
	void RenderRect(Texture* _Image, Vec2 _Pos, float _Rot, Vec2 _Scale, float _Depth, RECT _Rect, D3DCOLOR _Color = 0xffffffff);
	void CenterRenderRect(Texture* _Image, Vec2 _Pos, float _Rot, Vec2 _Scale, float _Depth, RECT _Rect, D3DCOLOR _Color = 0xffffffff);
	void RenderText(wstring _Text, int _Size, Vec2 _Pos, Vec2 _Scale, float _Depth, bool _Kor, D3DCOLOR _Color = 0xffffffff);
	void CenterRenderText(wstring _Text, int _Size, Vec2 _Pos, Vec2 _Scale, float _Depth, bool _Kor, D3DCOLOR _Color = 0xffffffff);

	void RenderView(Texture* _Image, Vec2 _Pos, float _Rot, Vec2 _Scale, float _Depth, D3DCOLOR _Color = 0xffffffff);
	void CenterRenderView(Texture* _Image, Vec2 _Pos, float _Rot, Vec2 _Scale, float _Depth, D3DCOLOR _Color = 0xffffffff);
	void RenderRectView(Texture* _Image, Vec2 _Pos, float _Rot, Vec2 _Scale, float _Depth, RECT _Rect, D3DCOLOR _Color = 0xffffffff);
	void CenterRenderRectView(Texture* _Image, Vec2 _Pos, float _Rot, Vec2 _Scale, float _Depth, RECT _Rect, D3DCOLOR _Color = 0xffffffff);
	void RenderTextView(wstring _Text, int _Size, Vec2 _Pos, Vec2 _Scale, float _Depth, bool _Kor, D3DCOLOR _Color = 0xffffffff);
	void CenterRenderTextView(wstring _Text, int _Size, Vec2 _Pos, Vec2 _Scale, float _Depth, bool _Kor, D3DCOLOR _Color = 0xffffffff);
};

#define IMAGE cImageManager::GetInstance()