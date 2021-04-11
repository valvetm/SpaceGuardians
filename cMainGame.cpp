#include "DXUT.h"
#include "cMainGame.h"
#include "cLoadingScene.h"
#include "cStage1Scene.h"
#include "cStage2Scene.h"
#include "cResultScene.h"
#include "cTitleScene.h"

cMainGame::cMainGame()
{
}


cMainGame::~cMainGame()
{
}

void cMainGame::Init()
{
	IMAGE->CreateInstance();
	SOUND->CreateInstance();
	OBJECT->CreateInstance();
	PART->CreateInstance();
	INPUT->CreateInstance();
	CAMERA->CreateInstance();
	SCENE->CreateInstance();
	SYSTEM->CreateInstance();

	SCENE->AddScene("LOADING", new cLoadingScene);
	SCENE->AddScene("STAGE1", new cStage1Scene);
	SCENE->AddScene("STAGE2", new cStage2Scene);
	SCENE->AddScene("RESULT", new cResultScene);
	SCENE->AddScene("TITLE", new cTitleScene);

	SCENE->ChangeScene("LOADING");
}

void cMainGame::Update()
{
	INPUT->Update();
	SYSTEM->Update();
	SCENE->Update();
	OBJECT->Update();
	PART->Update();
	SOUND->Update();
	CAMERA->Update();
}

void cMainGame::Render()
{
	IMAGE->Begin();

	SCENE->Render();
	OBJECT->Render();
	PART->Render();
	SYSTEM->Render();
	CAMERA->Render();

	IMAGE->End();
}

void cMainGame::Release()
{
	OBJECT->ReleaseInstance();
	PART->ReleaseInstance();
	CAMERA->ReleaseInstance();
	INPUT->ReleaseInstance();
	SCENE->ReleaseInstance();
	SYSTEM->ReleaseInstance();
	SOUND->ReleaseInstance();
	IMAGE->ReleaseInstance();
}

void cMainGame::OnLostDevice()
{
	IMAGE->m_Sprite->OnLostDevice();
}

void cMainGame::OnResetDevice()
{
	IMAGE->m_Sprite->OnResetDevice();
}
