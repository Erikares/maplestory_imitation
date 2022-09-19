#include "StdAfx.h"
#include "MainUI.h"

CMainUI::CMainUI(void)
{
	m_tInfo.fX = WINCX / 2;
	m_tInfo.fY = WINCY / 2;
	m_tInfo.fCX = WINCX;
	m_tInfo.fCY = WINCY;
}

CMainUI::~CMainUI(void)
{
}

void CMainUI::Initialize(void)
{
	m_pQuick = static_cast<CPlayer*>(m_pPlayer)->GetQuick();
}

void CMainUI::Update(void)
{
}

void CMainUI::Render(void)
{
	POINT	pt;
	pt = CMouse::GetPos();

	TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer"), 0, 0, 1024, 768,
		CBitMgr::GetInstance()->GetImage(L"MainUI"),0, 0, 1024, 768, RGB(255, 0, 255));
 
	//TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer"), 250, 734, 142, 14,
	//	CBitMgr::GetInstance()->GetImage(L"HpBar"), 250, 734,
	//	142 * (static_cast<CPlayer*>(m_pPlayer)->GetPInfo()->iHp / static_cast<CPlayer*>(m_pPlayer)->GetPInfo()->iMaxHp),
	//	14, RGB(255, 0, 255));

	//HP¹Ù
	TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
		251,
		734,
		static_cast<int>(142 * (static_cast<float>(static_cast<CPlayer*>(m_pPlayer)->GetPInfo()->iHp) / static_cast<float>(static_cast<CPlayer*>(m_pPlayer)->GetPInfo()->iMaxHp))),
		14,
		CBitMgr::GetInstance()->GetImage(L"HpBar"),
		0,
		0,
		142,
		14, RGB(255, 0, 255));

	TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
		421,
		734,
		static_cast<int>(142 * (static_cast<float>(static_cast<CPlayer*>(m_pPlayer)->GetPInfo()->iMp) / static_cast<float>(static_cast<CPlayer*>(m_pPlayer)->GetPInfo()->iMaxMp))),
		14,
		CBitMgr::GetInstance()->GetImage(L"MpBar"),
		0,
		0,
		142,
		14, RGB(255, 0, 255));



//	if(CursorName)
	{
		TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),pt.x - 16, pt.y - 16, 32, 32,
			CBitMgr::GetInstance()->GetImage(CursorName),0, 0, 32, 32, RGB(255, 0, 255));
	}

	//m_pQuick->pQuick1->Update();
	//Rectangle(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
	//	m_pQuick->pQuick1->GetRect()->left, m_pQuick->pQuick1->GetRect()->top,
	//	m_pQuick->pQuick1->GetRect()->right, m_pQuick->pQuick1->GetRect()->bottom);

	//m_pQuick->pQuick2->Update();
	//Rectangle(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
	//	m_pQuick->pQuick2->GetRect()->left, m_pQuick->pQuick2->GetRect()->top,
	//	m_pQuick->pQuick2->GetRect()->right, m_pQuick->pQuick2->GetRect()->bottom);

	//m_pQuick->pQuick3->Update();
	//Rectangle(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
	//	m_pQuick->pQuick3->GetRect()->left, m_pQuick->pQuick3->GetRect()->top,
	//	m_pQuick->pQuick3->GetRect()->right, m_pQuick->pQuick3->GetRect()->bottom);

	//m_pQuick->pQuick4->Update();
	//Rectangle(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
	//	m_pQuick->pQuick4->GetRect()->left, m_pQuick->pQuick4->GetRect()->top,
	//	m_pQuick->pQuick4->GetRect()->right, m_pQuick->pQuick4->GetRect()->bottom);

	//m_pQuick->pQuick5->Update();
	//Rectangle(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
	//	m_pQuick->pQuick5->GetRect()->left, m_pQuick->pQuick5->GetRect()->top,
	//	m_pQuick->pQuick5->GetRect()->right, m_pQuick->pQuick5->GetRect()->bottom);

	//m_pQuick->pQuick6->Update();
	//Rectangle(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
	//	m_pQuick->pQuick6->GetRect()->left, m_pQuick->pQuick6->GetRect()->top,
	//	m_pQuick->pQuick6->GetRect()->right, m_pQuick->pQuick6->GetRect()->bottom);

	//m_pQuick->pQuick7->Update();
	//Rectangle(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
	//	m_pQuick->pQuick7->GetRect()->left, m_pQuick->pQuick7->GetRect()->top,
	//	m_pQuick->pQuick7->GetRect()->right, m_pQuick->pQuick7->GetRect()->bottom);

	//m_pQuick->pQuick8->Update();
	//Rectangle(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
	//	m_pQuick->pQuick8->GetRect()->left, m_pQuick->pQuick8->GetRect()->top,
	//	m_pQuick->pQuick8->GetRect()->right, m_pQuick->pQuick8->GetRect()->bottom);

	


}

void CMainUI::Release(void)
{
	
}

bool CMainUI::HighRect(void)
{
	return 0;
}