#pragma once
#include "ObjMgr.h"		//오브젝트 매니저
#include "SceneMgr.h"	//신 매니저
#include "SoundMgr.h"	//사운드 매니저
#include "KeyMgr_60.h"	//키 매니저
#include "UiMgr.h"		//UI 매니저

#include "UI.h"
#include "MainUI.h"
#include "InvenUI.h"
#include "EquipUI.h"
#include "SkillUI.h"
#include "StateUI.h"
#include "Mouse.h"

#include "Player.h"
#include "Monster.h"

class CMainGame
{
private:
	bool	m_bIsMenu;
	bool	m_bTransScene;
	bool	m_bBlackScene;
	bool	m_bNotUpdate;

	int		m_iBlend;
	int		m_iScene;

	HDC		m_DC;

	CUI*	m_pUI;
	CUI*	m_pInvenUI;
	CUI*	m_pEquipUI;
public:
	void Initialize(void);
	void Update(void);
	void Render(void);
	void Release(void);
public:
	CMainGame(void);
	~CMainGame(void);
};
