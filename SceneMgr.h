#pragma once
#include "Scene.h"
#include "Obj.h"
#include "Player.h"
#include "Start.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "MapEdit.h"

class CSceneMgr
{
	DECLARE_SINGLETONE(CSceneMgr)
private:
	CScene*	m_pScene;
	CObj*	m_pPlayer;

public:
	CScene*	GetScene(void)
	{
		return m_pScene;
	}

	void	SetPlayer(CObj* pPlayer)
	{
		m_pPlayer = pPlayer;
	}

	void	SetScene(eSceneType eType)
	{
		if(m_pScene != NULL)
			SAFE_DELETE(m_pScene);

		switch(eType)
		{
		case SCENE_START:
			m_pScene = new CStart;
			m_pScene->SetPlayer(m_pPlayer);
			break;
		case SCENE_STAGE1:
			m_pScene = new CStage1;
			m_pScene->SetPlayer(m_pPlayer);
			break;
		case SCENE_STAGE2:
			m_pScene = new CStage2;
			m_pScene->SetPlayer(m_pPlayer);
			break;
		case SCENE_STAGE3:
			m_pScene = new CStage3;
			m_pScene->SetPlayer(m_pPlayer);
			break;
		case SCENE_MAP:
			m_pScene = new CMapEdit;
			break;
		}

		m_pScene->Initialize();

	}

	void Update(void);
	void Render(void);
	void Release(void);

private:
	CSceneMgr(void);
public:
	virtual ~CSceneMgr(void);
};
