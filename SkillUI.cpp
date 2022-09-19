#include "StdAfx.h"
#include "SkillUI.h"

CSkillUI::CSkillUI(void)
{
	m_tInfo.fX = WINCX / 2;
	m_tInfo.fY = WINCY / 2 - 200;
	m_tInfo.fCX = 174.f;
	m_tInfo.fCY = 300.f;

	m_Act	=	false;
	m_Drag	=	false;
	m_DragAct = false;
}

CSkillUI::~CSkillUI(void)
{
}

void CSkillUI::Initialize(void)
{
}

void CSkillUI::Update(void)
{
	if(m_Act)
	{
		//마우스가 처음 눌렸을때 렉트의 중점과 클릭한 좌표의 차를 구함
		if(GetAsyncKeyState(VK_LBUTTON) && !m_Drag)
		{
			m_Drag = true;
			fX = CMouse::GetPos().x - m_tInfo.fX;
			fY = CMouse::GetPos().y - m_tInfo.fY;
			//cout << "fX : " << fX << ", fY : " << fY << endl;
		}

		//처음 눌렸던 곳이 UI의 헤드 위치라면 눌려진 상태에서 계속 따라옴.
		if((fX>=-81) && (fX<= 67) && (fY>=-147) && (fY<=-128) && m_DragAct)
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

void CSkillUI::Render(void)
{
	if(m_Act)
	{
		TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer")
			,static_cast<int>(m_tInfo.fX - m_tInfo.fCX / 2)
			,static_cast<int>(m_tInfo.fY - m_tInfo.fCY / 2)
			,static_cast<int>(174.f)
			,static_cast<int>(300.f)
			,CBitMgr::GetInstance()->GetImage(L"SkillUI")
			, 0
			, 0
			, static_cast<int>(m_tInfo.fCX)
			, static_cast<int>(m_tInfo.fCY)
			, RGB(255, 0, 255));
	}
}

void CSkillUI::Release(void)
{

}

bool CSkillUI::HighRect(void)
{
	if((fX>=-84) && (fX<= 84) && (fY>=-148) && (fY<=148))
	{
		if(GetAsyncKeyState(VK_LBUTTON))	//최상위 렉트로 대입
		{
			return true;
		}
	}
	return false;
}