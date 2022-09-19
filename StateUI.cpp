#include "StdAfx.h"
#include "StateUI.h"
#include "ObjMgr.h"
#include "Player.h"
CStateUI::CStateUI(void)
{
	m_tInfo.fX = WINCX / 2;
	m_tInfo.fY = WINCY / 2 + 200;
	m_tInfo.fCX = 212.f;
	m_tInfo.fCY = 373.f;

	m_Act	=	false;
	m_Drag	=	false;
	m_DragAct = false;
}

CStateUI::~CStateUI(void)
{
	Release();
}

void CStateUI::Initialize(void)
{
}

void CStateUI::Update(void)
{
	if(m_Act)
	{
		//마우스가 처음 눌렸을때 렉트의 중점과 클릭한 좌표의 차를 구함
		if(GetAsyncKeyState(VK_LBUTTON) && !m_Drag)
		{
			m_Drag = true;
			fX = CMouse::GetPos().x - m_tInfo.fX;
			fY = CMouse::GetPos().y - m_tInfo.fY;
			cout << "fX : " << fX << ", fY : " << fY << endl;
		}

		//처음 눌렸던 곳이 UI의 헤드 위치라면 눌려진 상태에서 계속 따라옴.
		if((fX>=-102) && (fX<= 103) && (fY>=-184) && (fY<=-164) && m_DragAct)
		{
			if(GetAsyncKeyState(VK_LBUTTON))	//결속 한 뒤 마우스 추적
			{
				m_tInfo.fX	= CMouse::GetPos().x - fX;
				m_tInfo.fY	= CMouse::GetPos().y - fY;
				//cout << "fX : " << fX << ", fY : " << fY << endl;
			}
		}

		//마우스가 떨어진 상태라면 클릭값과 차 값을 0, false로 만듦
		if(0 == GetAsyncKeyState(VK_LBUTTON))
		{
			fX = 0;
			fY = 0;
			m_Drag = false;
		}
	}

	

	CUI::Update();
}

void CStateUI::Render(void)
{
	if(m_Act)
	{
		TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer")
			,static_cast<int>(m_tInfo.fX - m_tInfo.fCX / 2)
			,static_cast<int>(m_tInfo.fY - m_tInfo.fCY / 2)
			,static_cast<int>(212.f)
			,static_cast<int>(373.f)
			,CBitMgr::GetInstance()->GetImage(L"StateUI")
			, 0
			, 0
			, static_cast<int>(m_tInfo.fCX)
			, static_cast<int>(m_tInfo.fCY)	, RGB(255, 0, 255));
	}

	TCHAR szBuf[128] = L"";
	wsprintf(szBuf, L"깨어난쥬신인");
	TextOut(CBitMgr::GetInstance()->GetImage(L"StateUI"), 70, 30, szBuf, lstrlen(szBuf));

	wsprintf(szBuf, L"메르세데스");
	TextOut(CBitMgr::GetInstance()->GetImage(L"StateUI"), 70, 48, szBuf, lstrlen(szBuf));

	wsprintf(szBuf, L"%d / %d",(static_cast<CPlayer*>(CObjMgr::GetInstance()->GetList(OBJ_PLY)->front())->GetPInfo()->iHp), (static_cast<CPlayer*>(CObjMgr::GetInstance()->GetList(OBJ_PLY)->front())->GetPInfo()->iMaxHp));
	TextOut(CBitMgr::GetInstance()->GetImage(L"StateUI"), 70, 158, szBuf, lstrlen(szBuf));

	wsprintf(szBuf, L"%d / %d",(static_cast<CPlayer*>(CObjMgr::GetInstance()->GetList(OBJ_PLY)->front())->GetPInfo()->iMp), (static_cast<CPlayer*>(CObjMgr::GetInstance()->GetList(OBJ_PLY)->front())->GetPInfo()->iMaxMp));
	TextOut(CBitMgr::GetInstance()->GetImage(L"StateUI"), 70, 176, szBuf, lstrlen(szBuf));
	
}

void CStateUI::Release(void)
{

}

bool CStateUI::HighRect(void)
{
	if((fX>=-104) && (fX<= 104) && (fY>=-187) && (fY<=187))
	{
		if(GetAsyncKeyState(VK_LBUTTON))	//최상위 렉트로 대입
		{
			return true;
		}
	}
	return false;
}