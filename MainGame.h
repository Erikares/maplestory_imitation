#pragma once
#include "ObjMgr.h"		//������Ʈ �Ŵ���
#include "SceneMgr.h"	//�� �Ŵ���
#include "SoundMgr.h"	//���� �Ŵ���
#include "KeyMgr_60.h"	//Ű �Ŵ���
#include "UiMgr.h"		//UI �Ŵ���

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
