#include "StdAfx.h"
#include "InvenUI.h"

CInvenUI::CInvenUI(void)
{
	m_tInfo.fX = WINCX / 2 + 200;
	m_tInfo.fY = WINCY / 2;
	m_tInfo.fCX = 172.f;
	m_tInfo.fCY = 335.f;

	m_Act	=	false;
	m_Drag	=	false;
	m_DragAct = false;
}

CInvenUI::~CInvenUI(void)
{
}

void CInvenUI::Initialize(void)
{
}

void CInvenUI::Update(void)
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
		if((fX>=-81) && (fX<= 63) && (fY>=-165) && (fY<=-148) && m_DragAct)
		{
			if(GetAsyncKeyState(VK_LBUTTON))	//결속 한 뒤 마우스 추적
			{
				m_tInfo.fX	= CMouse::GetPos().x - fX;
				m_tInfo.fY	= CMouse::GetPos().y - fY;
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

void CInvenUI::Render(void)
{
	if(m_Act)
	{
		TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer")
			,static_cast<int>(m_tInfo.fX - m_tInfo.fCX / 2)
			,static_cast<int>(m_tInfo.fY - m_tInfo.fCY / 2)
			,static_cast<int>(172.f)
			,static_cast<int>(335.f)
			,CBitMgr::GetInstance()->GetImage(L"InvenUI")
			, 0
			, 0
			, static_cast<int>(m_tInfo.fCX)
			, static_cast<int>(m_tInfo.fCY)
			, RGB(255, 0, 255));

		RenderItem();
	}

	

}

void CInvenUI::Release(void)
{

}

bool CInvenUI::HighRect(void)
{
	if((fX>=-83) && (fX<= 83) && (fY>=-166) && (fY<=166))
	{
		if(GetAsyncKeyState(VK_LBUTTON))	//최상위 렉트로 대입
		{
			return true;
		}
	}
	return false;
}


void	CInvenUI::RenderItem()
{
	vector<CItem*>::iterator iter = m_pVecInven->begin();
	vector<CItem*>::iterator iter_end = m_pVecInven->end();

	int i = 0;
	int j = 0;

	//이터를 돌면서 인벤토리에 아이템 출력
	for(iter; iter != iter_end; ++iter)
	{
		(*iter)->GetInfo()->fX = m_tInfo.fX - 59 + ( i * 36);
		(*iter)->GetInfo()->fY = m_tInfo.fY - 100 + (j * 35);
		(*iter)->Update();

		/*Rectangle(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
			(*iter)->GetInfo()->fX - ((*iter)->GetInfo()->fCX / 2),
			(*iter)->GetInfo()->fY - ((*iter)->GetInfo()->fCY / 2),
			(*iter)->GetInfo()->fX + ((*iter)->GetInfo()->fCX / 2),
			(*iter)->GetInfo()->fY + ((*iter)->GetInfo()->fCY / 2));*/

		TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer")
			,static_cast<int>((*iter)->GetInfo()->fX - ((*iter)->GetInfo()->fCX / 2))
			,static_cast<int>((*iter)->GetInfo()->fY - ((*iter)->GetInfo()->fCY / 2))
			,static_cast<int>(32.f)
			,static_cast<int>(32.f)
			,CBitMgr::GetInstance()->GetImage((*iter)->GetItemName())
			, 0
			, 0
			, 32
			, 32
			, RGB(255, 0, 255));

		++i;

		if((i > 3) && (i % 4 == 0))
		{
			i = 0;
			++j;
		}
	}
}