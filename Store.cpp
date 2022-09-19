#include "StdAfx.h"
#include "Store.h"

CStore::CStore(void)
{
	m_tInfo.fX = WINCX / 2;
	m_tInfo.fY = WINCY / 2;
	m_tInfo.fCX = 507.f;
	m_tInfo.fCY = 504.f;
	
	m_Act	=	true;
	m_Drag	=	false;
	m_DragAct = false;
}

CStore::~CStore(void)
{
	Release();
}

void CStore::Initialize()
{
	m_vecStore.reserve(10);

	CItem* pItem;
	
	pItem = new CItem;
	pItem->SetItem(1);
	m_vecStore.push_back(pItem);
}

void CStore::Update(void)
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

void CStore::Render(void)
{

	if(m_Act)
	{
		TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer")
			,static_cast<int>(m_tInfo.fX - m_tInfo.fCX / 2)
			,static_cast<int>(m_tInfo.fY - m_tInfo.fCY / 2)
			,static_cast<int>(232.f)
			,static_cast<int>(332.f)
			,CBitMgr::GetInstance()->GetImage(L"StoreUI")
			, 0
			, 0
			, static_cast<int>(m_tInfo.fCX)
			, static_cast<int>(m_tInfo.fCY)
			, RGB(255, 0, 255));

	}
	vector<CItem*>::iterator iter = m_vecStore.begin();
	vector<CItem*>::iterator iter_end = m_vecStore.end();


	for(iter; iter != iter_end; ++iter)
	{
		//(*iter)->GetInfo()->fX = 200;
		//(*iter)->GetInfo()->fY = 200;
	}
	//Rectangle(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
		//	(*iter)->GetInfo()->fX - ((*iter)->GetInfo()->fCX / 2),
		//	(*iter)->GetInfo()->fY - ((*iter)->GetInfo()->fCY / 2),
		//	(*iter)->GetInfo()->fX + ((*iter)->GetInfo()->fCX / 2),
		//	(*iter)->GetInfo()->fY + ((*iter)->GetInfo()->fCY / 2));
}

void CStore::Release()
{
}

bool CStore::HighRect(void)
{
	if((fX>=-116) && (fX<= 116) && (fY>=-166) && (fY<=166))
	{
		if(GetAsyncKeyState(VK_LBUTTON))	//최상위 렉트로 대입
		{
			return true;
		}
	}
	return false;
}