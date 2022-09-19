#include "StdAfx.h"
#include "SceneMgr.h"

IMPLEMENT_SINGLETONE(CSceneMgr)
CSceneMgr::CSceneMgr(void)
:m_pScene(NULL)
{
}

CSceneMgr::~CSceneMgr(void)
{
	Release();
}


void CSceneMgr::Update(void)
{
	m_pScene->Update();
}

void CSceneMgr::Render(void)
{
	m_pScene->Render();
}

void CSceneMgr::Release()
{
	m_pScene->Release();
	SAFE_DELETE(m_pScene);
}