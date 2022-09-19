#include "StdAfx.h"
#include "Player.h"
#include "BitMgr.h"

CPlayer::CPlayer(void)
//플레이어의 장비 구조체 초기화
:m_tEquip(NULL, NULL, NULL, NULL, NULL)
{
	m_Drag = false;

	m_eArrow	=	DIR_RIGHT;
	m_bIsAtk	=	false;
	m_bIsJump	=	false;
	m_bIsFall	=	false;
	m_bIsHit	=	false;
	m_bIsSuper	=	false;

	m_bIsSkilling
				=	false;
	m_bIsDrive	=	false;
	m_bIsHigh	=	false;
	m_bIsRing	=	false;


	m_bIsClimb	=	false;
	m_bIsGhost	=	false;
	m_bIsHill	=	false;
	
	
	m_bIsKnockBack
				=	false;

	m_fJumpAcc = 0.f;
	m_fTime = 0.f;
	m_fKnockBack = 0.f;

	m_dwItemTime	=	GetTickCount();
	m_dwFrameTime	=	GetTickCount();
	m_dwActiveTime	=	GetTickCount();

	m_iPrevMap		=	0;	//이전에 있던 맵의 위치
}

CPlayer::~CPlayer(void)
{
	Release();
}

void CPlayer::Initialize()
{
	m_tPlayer.iHp		=	50000;
	m_tPlayer.iMaxHp	=	50000;
	m_tPlayer.iMp		=	30000;
	m_tPlayer.iMaxMp	=	30000;
	m_tPlayer.iAtk		=	1200;
	m_tPlayer.iDef		=	10000;

	m_tInfo.fX = WINCX / 2;
	m_tInfo.fY = WINCY / 2 + 100;
	m_tInfo.fCX = 50;
	m_tInfo.fCY = 100;

	m_fSpeed	=	3.f;

	m_pName		= L"Right_Player";
	m_tFrame = FRAME(0, 3, 0, 400); 

	m_vecInven.reserve(24);


	//기본 아이템
	CItem*	pItem;

	pItem = new CItem;
	pItem->SetItem(1);
	pItem->SetEquip(GetEquip());
	pItem->SetVector(GetVector());
	m_vecInven.push_back(pItem);

	pItem = new CItem;
	pItem->SetItem(100);
	pItem->SetEquip(GetEquip());
	pItem->SetVector(GetVector());
	m_vecInven.push_back(pItem);

	pItem = new CItem;
	pItem->SetItem(200);
	pItem->SetEquip(GetEquip());
	pItem->SetVector(GetVector());
	m_vecInven.push_back(pItem);

	pItem = new CItem;
	pItem->SetItem(300);
	pItem->SetEquip(GetEquip());
	pItem->SetVector(GetVector());
	m_vecInven.push_back(pItem);

	pItem = new CItem;
	pItem->SetItem(400);
	pItem->SetEquip(GetEquip());
	pItem->SetVector(GetVector());
	m_vecInven.push_back(pItem);

	pItem = new CItem;
	pItem->SetItem(500);
	pItem->SetEquip(GetEquip());
	pItem->SetVector(GetVector());
	m_vecInven.push_back(pItem);
	
	
	//퀵슬롯
	pItem = new CItem;
	pItem->SetItem(0);
	m_Quick.pQuick1 = pItem;
	pItem->GetInfo()->fX = 905;
	pItem->GetInfo()->fY = 715;
	pItem->Update();

	pItem = new CItem;
	pItem->SetItem(0);
	m_Quick.pQuick2 = pItem;
	pItem->GetInfo()->fX = 938;
	pItem->GetInfo()->fY = 715;
	pItem->Update();

	pItem = new CItem;
	pItem->SetItem(0);
	m_Quick.pQuick3 = pItem;
	pItem->GetInfo()->fX = 971;
	pItem->GetInfo()->fY = 715;
	pItem->Update();

	pItem = new CItem;
	pItem->SetItem(0);
	m_Quick.pQuick4 = pItem;
	pItem->GetInfo()->fX = 1004;
	pItem->GetInfo()->fY = 715;
	pItem->Update();

	pItem = new CItem;
	pItem->SetItem(0);
	m_Quick.pQuick5 = pItem;
	pItem->GetInfo()->fX = 905;
	pItem->GetInfo()->fY = 748;
	pItem->Update();

	pItem = new CItem;
	pItem->SetItem(0);
	m_Quick.pQuick6 = pItem;
	pItem->GetInfo()->fX = 938;
	pItem->GetInfo()->fY = 748;
	pItem->Update();

	pItem = new CItem;
	pItem->SetItem(0);
	m_Quick.pQuick7 = pItem;
	pItem->GetInfo()->fX = 971;
	pItem->GetInfo()->fY = 748;
	pItem->Update();

	pItem = new CItem;
	pItem->SetItem(0);
	m_Quick.pQuick8 = pItem;
	pItem->GetInfo()->fX = 1004;
	pItem->GetInfo()->fY = 748;
	pItem->Update();




	//pItem = new CItem;
	//pItem->SetItem(100);
	//m_vecInven.push_back(pItem);

	//pItem = new CItem;
	//pItem->SetItem(200);
	//m_vecInven.push_back(pItem);

	//인벤토리에 빈 아이템 생성
	for(int i = 0; i < 19; ++i)
	{
		pItem = new CItem;
		pItem->SetItem(0);
		pItem->SetEquip(GetEquip());
		pItem->SetVector(GetVector());
		m_vecInven.push_back(pItem);
	}

	//각 장비창에 빈 아이템 생성	
	pItem = new CItem;
	pItem->SetItem(0);
	pItem->SetEquip(GetEquip());
	pItem->SetVector(GetVector());
	m_tEquip.tWeapon = pItem;

	pItem = new CItem;
	pItem->SetItem(0);
	pItem->SetEquip(GetEquip());
	pItem->SetVector(GetVector());
	m_tEquip.tArmor = pItem;

	pItem = new CItem;
	pItem->SetItem(0);
	pItem->SetEquip(GetEquip());
	pItem->SetVector(GetVector());
	m_tEquip.tBoots = pItem;

	pItem = new CItem;
	pItem->SetItem(0);
	pItem->SetEquip(GetEquip());
	pItem->SetVector(GetVector());
	m_tEquip.tGloves = pItem;

	pItem = new CItem;
	pItem->SetItem(0);
	pItem->SetEquip(GetEquip());
	pItem->SetVector(GetVector());
	m_tEquip.tHead = pItem;
}

int CPlayer::Update()
{
	if(m_fJumpAcc > 15.f)
		m_bIsGhost = false;

	KeyCheck();
	Scroll();
	FrameMove();
	//TileCrush();	//스테이지에서 호출
	ItemSwap();
	ItemCrush();

	CObj::Update();
	return 0;
}

void CPlayer::Render()
{
	TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer")
		,static_cast<int>(m_tInfo.fX - 100) + m_ptScroll.x
		,static_cast<int>(m_tInfo.fY - 100) + m_ptScroll.y
		,static_cast<int>(200.f)
		,static_cast<int>(200.f)
		,CBitMgr::GetInstance()->GetImage(m_pName)
		, m_tFrame.iScene * 200
		, m_tFrame.iFrameStart * 200
		, 200
		, 200
		, RGB(140, 203, 157));

	//Rectangle(
	//	CBitMgr::GetInstance()->GetImage(L"BackBuffer")
	//	, m_Rect.left + m_ptScroll.x
	//	, m_Rect.top + m_ptScroll.y
	//	, m_Rect.right + m_ptScroll.x
	//	, m_Rect.bottom + m_ptScroll.y);
}

void CPlayer::Release()
{
	//인벤토리 메모리 해제
	vector<CItem*>::iterator iter = m_vecInven.begin();
	vector<CItem*>::iterator iter_end = m_vecInven.end();

	for(iter; iter != iter_end; ++iter)
	{
		delete (*iter);
	}
	m_vecInven.clear();

	//장비 메모리 해제
	delete m_tEquip.tArmor;
	delete m_tEquip.tBoots;
	delete m_tEquip.tGloves;
	delete m_tEquip.tWeapon;
	delete m_tEquip.tHead;

	//퀵 슬롯 메모리 해제
	delete m_Quick.pQuick1;
	delete m_Quick.pQuick2;
	delete m_Quick.pQuick3;
	delete m_Quick.pQuick4;
	delete m_Quick.pQuick5;
	delete m_Quick.pQuick6;
	delete m_Quick.pQuick7;
	delete m_Quick.pQuick8;

}

void CPlayer::ItemSwap(void)
{
	CItem*	tempItem = new CItem;

	vector<CItem*>::iterator iter		= m_vecInven.begin();
	vector<CItem*>::iterator iter_end	= m_vecInven.end();

	//인벤토리 내의 아이템 클릭
	for(iter; iter != iter_end; ++iter)
	{
		if(GetAsyncKeyState(VK_RBUTTON))
		{
			(*iter)->fX = CMouse::GetPos().x - (*iter)->GetInfo()->fX;
			(*iter)->fY = CMouse::GetPos().y - (*iter)->GetInfo()->fY;
			if(((*iter)->fX > -16) && ((*iter)->fX < 16) && ((*iter)->fY > -16) && ((*iter)->fY < 16))
			{
				INFO*	tempInfo1 = new INFO;
				tempInfo1->fX = (*iter)->GetInfo()->fX;
				tempInfo1->fY = (*iter)->GetInfo()->fY;

				INFO*	tempInfo2 = new INFO;


				switch((*iter)->GetItemType())
				{
				case ITEM_USE:
					m_tPlayer.iHp += 5000;
					if(m_tPlayer.iHp > m_tPlayer.iMaxHp)
					{
						m_tPlayer.iHp = m_tPlayer.iMaxHp;
					}
					break;
				case ITEM_WP:
					//MessageBox(g_hWnd,L"무기무기", L"무기무기", MB_OK);
					tempInfo2->fX = m_tEquip.tWeapon->GetInfo()->fX;
					tempInfo2->fY = m_tEquip.tWeapon->GetInfo()->fY;

					*tempItem = *m_tEquip.tWeapon;
					*m_tEquip.tWeapon = *(*iter);
					*(*iter) = *tempItem;

					(*iter)->GetInfo()->fX = tempInfo1->fX;
					(*iter)->GetInfo()->fY = tempInfo1->fY;
					m_tEquip.tWeapon->GetInfo()->fX = tempInfo2->fX;
					m_tEquip.tWeapon->GetInfo()->fY = tempInfo2->fY;


					break;

				case ITEM_AR:
					//MessageBox(g_hWnd,L"갑옷 갑옷", L"갑옷 갑옷", MB_OK);
					tempInfo2->fX = m_tEquip.tArmor->GetInfo()->fX;
					tempInfo2->fY = m_tEquip.tArmor->GetInfo()->fY;

					*tempItem = *m_tEquip.tArmor;
					*m_tEquip.tArmor = *(*iter);
					*(*iter) = *tempItem;

					(*iter)->GetInfo()->fX = tempInfo1->fX;
					(*iter)->GetInfo()->fY = tempInfo1->fY;
					m_tEquip.tArmor->GetInfo()->fX = tempInfo2->fX;
					m_tEquip.tArmor->GetInfo()->fY = tempInfo2->fY;
					break;

				case ITEM_HEAD:
					//MessageBox(g_hWnd,L"자라나라 ", L"머리 머리", MB_OK);
					tempInfo2->fX = m_tEquip.tHead->GetInfo()->fX;
					tempInfo2->fY = m_tEquip.tHead->GetInfo()->fY;

					*tempItem = *m_tEquip.tHead;
					*m_tEquip.tHead = *(*iter);
					*(*iter) = *tempItem;

					(*iter)->GetInfo()->fX = tempInfo1->fX;
					(*iter)->GetInfo()->fY = tempInfo1->fY;
					m_tEquip.tHead->GetInfo()->fX = tempInfo2->fX;
					m_tEquip.tHead->GetInfo()->fY = tempInfo2->fY;
					break;

				case ITEM_GLOVES:
					//MessageBox(g_hWnd,L"장갑이 ", L"요기잉네", MB_OK);
					tempInfo2->fX = m_tEquip.tGloves->GetInfo()->fX;
					tempInfo2->fY = m_tEquip.tGloves->GetInfo()->fY;

					*tempItem = *m_tEquip.tGloves;
					*m_tEquip.tGloves = *(*iter);
					*(*iter) = *tempItem;

					(*iter)->GetInfo()->fX = tempInfo1->fX;
					(*iter)->GetInfo()->fY = tempInfo1->fY;
					m_tEquip.tGloves->GetInfo()->fX = tempInfo2->fX;
					m_tEquip.tGloves->GetInfo()->fY = tempInfo2->fY;
					break;

				case ITEM_SHOES:
					//MessageBox(g_hWnd,L"장갑이 ", L"요기잉네", MB_OK);
					tempInfo2->fX = m_tEquip.tBoots->GetInfo()->fX;
					tempInfo2->fY = m_tEquip.tBoots->GetInfo()->fY;

					*tempItem = *m_tEquip.tBoots;
					*m_tEquip.tBoots = *(*iter);
					*(*iter) = *tempItem;

					(*iter)->GetInfo()->fX = tempInfo1->fX;
					(*iter)->GetInfo()->fY = tempInfo1->fY;
					m_tEquip.tBoots->GetInfo()->fX = tempInfo2->fX;
					m_tEquip.tBoots->GetInfo()->fY = tempInfo2->fY;
					break;
				}
				SAFE_DELETE(tempInfo1);
				SAFE_DELETE(tempInfo2);
				SAFE_DELETE(tempItem);
			}
		}
	}

	iter = m_vecInven.begin(); //이터 시작점 초기화

	//장비창의 아이템클릭, 
	if(m_tEquip.tWeapon)
	{
		if(GetAsyncKeyState(VK_RBUTTON))
		{
			m_tEquip.tWeapon->fX = CMouse::GetPos().x - m_tEquip.tWeapon->GetInfo()->fX;
			m_tEquip.tWeapon->fY = CMouse::GetPos().y - m_tEquip.tWeapon->GetInfo()->fY;
			if((m_tEquip.tWeapon->fX > -16) && (m_tEquip.tWeapon->fX < 16) && (m_tEquip.tWeapon->fY > -16) && (m_tEquip.tWeapon->fY < 16))
			{
				//MessageBox(g_hWnd, L"장비무기", L"장비무기", MB_OK);

				for(iter; iter != iter_end; ++iter)
				{
					if((*iter)->GetItemType() == ITEM_END)
					{
						tempItem = m_tEquip.tWeapon;
						m_tEquip.tWeapon = (*iter);
						(*iter) = tempItem;
					}
				}

				if(iter == iter_end)
					return;

			}
		}
	}

	if(m_tEquip.tArmor)
	{
		if(GetAsyncKeyState(VK_RBUTTON))
		{
			m_tEquip.tArmor->fX = CMouse::GetPos().x - m_tEquip.tArmor->GetInfo()->fX;
			m_tEquip.tArmor->fY = CMouse::GetPos().y - m_tEquip.tArmor->GetInfo()->fY;
			if((m_tEquip.tArmor->fX > -16) && (m_tEquip.tArmor->fX < 16) && (m_tEquip.tArmor->fY > -16) && (m_tEquip.tArmor->fY < 16))
			{
				//cout << "장비와의 거리" << m_tEquip.tArmor->fX << ", " << m_tEquip.tArmor->fY << endl;
				//cout << "장비 좌표" << m_tEquip.tArmor->GetInfo()->fX << ", " << m_tEquip.tArmor->GetInfo()->fY << endl;
				//cout << "마우스 좌표" << CMouse::GetPos().x << ", " << CMouse::GetPos().y << endl;
				//MessageBox(g_hWnd, L"장비갑옷", L"장비갑옷", MB_OK);
				for(iter; iter != iter_end; ++iter)
				{
					if((*iter)->GetItemType() == ITEM_END)
					{
						tempItem = m_tEquip.tArmor;
						m_tEquip.tArmor = (*iter);
						(*iter) = tempItem;
					}
				}

				if(iter == iter_end)
					return;
			}
		}
	}

	if(m_tEquip.tGloves)
	{
		if(GetAsyncKeyState(VK_RBUTTON))
		{
			m_tEquip.tGloves->fX = CMouse::GetPos().x - m_tEquip.tGloves->GetInfo()->fX;
			m_tEquip.tGloves->fY = CMouse::GetPos().y - m_tEquip.tGloves->GetInfo()->fY;
			if((m_tEquip.tGloves->fX > -16) && (m_tEquip.tGloves->fX < 16) && (m_tEquip.tGloves->fY > -16) && (m_tEquip.tGloves->fY < 16))
			{
				//MessageBox(g_hWnd, L"장비장갑", L"장비장갑", MB_OK);
				for(iter; iter != iter_end; ++iter)
				{
					if((*iter)->GetItemType() == ITEM_END)
					{
						tempItem = m_tEquip.tGloves;
						m_tEquip.tGloves = (*iter);
						(*iter) = tempItem;
					}
				}

				if(iter == iter_end)
					return;
			}
		}
	}

	if(m_tEquip.tBoots)
	{
		if(GetAsyncKeyState(VK_RBUTTON))
		{
			m_tEquip.tBoots->fX = CMouse::GetPos().x - m_tEquip.tBoots->GetInfo()->fX;
			m_tEquip.tBoots->fY = CMouse::GetPos().y - m_tEquip.tBoots->GetInfo()->fY;
			if((m_tEquip.tBoots->fX > -16) && (m_tEquip.tBoots->fX < 16) && (m_tEquip.tBoots->fY > -16) && (m_tEquip.tBoots->fY < 16))
			{
				//MessageBox(g_hWnd, L"장비신발", L"장비신발", MB_OK);
				for(iter; iter != iter_end; ++iter)
				{
					if((*iter)->GetItemType() == ITEM_END)
					{
						tempItem = m_tEquip.tBoots;
						m_tEquip.tBoots = (*iter);
						(*iter) = tempItem;
					}
				}

				if(iter == iter_end)
					return;
			}
		}
	}

	if(m_tEquip.tHead)
	{
		if(GetAsyncKeyState(VK_RBUTTON))
		{
			m_tEquip.tHead->fX = CMouse::GetPos().x - m_tEquip.tHead->GetInfo()->fX;
			m_tEquip.tHead->fY = CMouse::GetPos().y - m_tEquip.tHead->GetInfo()->fY;
			if((m_tEquip.tHead->fX > -16) && (m_tEquip.tHead->fX < 16) && (m_tEquip.tHead->fY > -16) && (m_tEquip.tHead->fY < 16))
			{
				//MessageBox(g_hWnd, L"장비머리", L"장비머리", MB_OK);
				for(iter; iter != iter_end; ++iter)
				{
					if((*iter)->GetItemType() == ITEM_END)
					{
						tempItem = m_tEquip.tHead;
						m_tEquip.tHead = (*iter);
						(*iter) = tempItem;
					}
				}

				if(iter == iter_end)
					return;
			}
		}
	}

	SAFE_DELETE(tempItem);


}

void CPlayer::ItemCrush(void)
{
	CItem*	tempItem = NULL;
	pt = CMouse::GetPos();

	//인벤 내에 있는 아이템들의 충돌 테스트
	vector<CItem*>::iterator iter		= m_vecInven.begin();
	vector<CItem*>::iterator iter_end	= m_vecInven.end();

	if(!m_Drag)
	{
		if(GetAsyncKeyState(VK_LBUTTON) && !m_Drag)
		{
			iItemNum = 0;
			for(iter; iter != iter_end; ++iter)
			{
				++iItemNum;

				//(*iter)->fX = CMouse::GetPos().x - (*iter)->GetInfo()->fX;
				//(*iter)->fY = CMouse::GetPos().y - (*iter)->GetInfo()->fY;

				if(((*iter)->fX > -16) && ((*iter)->fX < 16)
					&& ((*iter)->fY > -16) && ((*iter)->fY < 16))
				{
					m_Drag = true;
					//cout << iItemNum << "fX : " << (*iter)->GetInfo()->fX << ", fY : " << (*iter)->GetInfo()->fY << endl;
					//cout << (*(*iter)->GetItemName()) << endl;
					tempItem = (*iter);

					break;
				}
			}
		}
	}


	if(PtInRect(m_tEquip.tWeapon->GetRect(),pt) && m_Drag && !GetAsyncKeyState(VK_LBUTTON))
	{
		//cout << iItemNum << endl;
		if(m_vecInven[iItemNum - 1]->GetItemType() == ITEM_WP)
		{
			tempItem = m_tEquip.tWeapon;
			m_tEquip.tWeapon = m_vecInven[iItemNum - 1];
			m_vecInven[iItemNum - 1] = tempItem;
		}
	}

	if(PtInRect(m_tEquip.tArmor->GetRect(),pt) && m_Drag && !GetAsyncKeyState(VK_LBUTTON))
	{
		//cout << iItemNum << endl;
		if(m_vecInven[iItemNum - 1]->GetItemType() == ITEM_AR)
		{
			tempItem = m_tEquip.tArmor;
			m_tEquip.tArmor = m_vecInven[iItemNum - 1];
			m_vecInven[iItemNum - 1] = tempItem;
		}
	}

	if(PtInRect(m_tEquip.tHead->GetRect(),pt) && m_Drag && !GetAsyncKeyState(VK_LBUTTON))
	{
		//cout << iItemNum << endl;
		if(m_vecInven[iItemNum - 1]->GetItemType() == ITEM_HEAD)
		{
			tempItem = m_tEquip.tHead;
			m_tEquip.tHead = m_vecInven[iItemNum - 1];
			m_vecInven[iItemNum- 1] = tempItem;
		}
	}

	if(PtInRect(m_tEquip.tGloves->GetRect(),pt) && m_Drag && !GetAsyncKeyState(VK_LBUTTON))
	{
		//cout << iItemNum << endl;
		if(m_vecInven[iItemNum - 1]->GetItemType() == ITEM_GLOVES)
		{
			tempItem = m_tEquip.tGloves;
			m_tEquip.tGloves = m_vecInven[iItemNum - 1];
			m_vecInven[iItemNum - 1] = tempItem;
		}
	}

	if(PtInRect(m_tEquip.tBoots->GetRect(),pt) && m_Drag && !GetAsyncKeyState(VK_LBUTTON))
	{
		//cout << iItemNum << endl;
		if(m_vecInven[iItemNum - 1]->GetItemType() == ITEM_SHOES)
		{
			tempItem = m_tEquip.tBoots;
			m_tEquip.tBoots = m_vecInven[iItemNum - 1];
			m_vecInven[iItemNum - 1] = tempItem;
		}
	}



	if(!GetAsyncKeyState(VK_LBUTTON))
		m_Drag = false;


	////////////////////////////////////////////////////////////////////////////

	////장비창 아이템의 충돌 테스트
	////무기
	//if(!m_Drag)
	//{
	//	if(GetAsyncKeyState(VK_LBUTTON) && !m_Drag && PtInRect(m_tEquip.tWeapon->GetRect(),pt))
	//	{
	//		m_tEquip.tWeapon->fX = CMouse::GetPos().x - m_tEquip.tWeapon->GetInfo()->fX;
	//		m_tEquip.tWeapon->fY = CMouse::GetPos().y - m_tEquip.tWeapon->GetInfo()->fY;

	//		if((m_tEquip.tWeapon->fX > -16) && (m_tEquip.tWeapon->fX < 16)
	//			&& (m_tEquip.tWeapon->fY > -16) && (m_tEquip.tWeapon->fY < 16))
	//		{
	//			m_Drag = true;
	//			cout << "무기잡았당" << endl;
	//			//tempItem = (*iter);
	//		}
	//		
	//	}
	//}

	//iter		= m_vecInven.begin();

	//for(iter; iter != iter_end; ++iter)
	//{
	//	if(PtInRect((*iter)->GetRect(),pt) && m_Drag
	//		&& GetAsyncKeyState(VK_LBUTTON) && dwItemTime + 1000 < GetTickCount())
	//	{
	//		if(((*iter)->GetItemType() == ITEM_WP) || ((*iter)->GetItemType() == ITEM_END))
	//		{
	//			dwItemTime = GetTickCount();
	//			cout << "무기잡혔땅" << endl;
	//			tempItem = (*iter);
	//			(*iter) = m_tEquip.tWeapon;
	//			m_tEquip.tWeapon = tempItem;
	//			m_Drag = false;
	//		}
	//	}
	//}

	//if(!GetAsyncKeyState(VK_LBUTTON))
	//	m_Drag = false;

	////////////////////////////////////////////////////////////////////////////////////
	//
	////아머
	//if(!m_Drag)
	//{
	//	if(GetAsyncKeyState(VK_LBUTTON) && !m_Drag)
	//	{
	//		m_tEquip.tArmor->fX = CMouse::GetPos().x - m_tEquip.tArmor->GetInfo()->fX;
	//		m_tEquip.tArmor->fY = CMouse::GetPos().y - m_tEquip.tArmor->GetInfo()->fY;

	//		if((m_tEquip.tArmor->fX > -16) && (m_tEquip.tArmor->fX < 16)
	//			&& (m_tEquip.tArmor->fY > -16) && (m_tEquip.tArmor->fY < 16))
	//		{
	//			m_Drag = true;
	//			cout << "아머잡았당" << endl;
	//			//tempItem = (*iter);
	//		}
	//		
	//	}
	//}

	//iter		= m_vecInven.begin();

	//for(iter; iter != iter_end; ++iter)
	//{
	//	if(PtInRect((*iter)->GetRect(),pt) && m_Drag
	//		&& GetAsyncKeyState(VK_LBUTTON) && dwItemTime + 1000 < GetTickCount())
	//	{
	//		if((*iter)->GetItemType() == ITEM_AR)
	//		{
	//			dwItemTime = GetTickCount();
	//			cout << "아머잡혔땅" << endl;
	//			tempItem = (*iter);
	//			(*iter) = m_tEquip.tArmor;
	//			m_tEquip.tArmor = tempItem;
	//			m_Drag = false;
	//		}
	//	}
	//}

	//if(!GetAsyncKeyState(VK_LBUTTON))
	//	m_Drag = false;

	////////////////////////////////////////////////////////////////////////////////////
	////머리
	//if(!m_Drag)
	//{
	//	if(GetAsyncKeyState(VK_LBUTTON) && !m_Drag)
	//	{
	//		m_tEquip.tHead->fX = CMouse::GetPos().x - m_tEquip.tHead->GetInfo()->fX;
	//		m_tEquip.tHead->fY = CMouse::GetPos().y - m_tEquip.tHead->GetInfo()->fY;

	//		if((m_tEquip.tHead->fX > -16) && (m_tEquip.tHead->fX < 16)
	//			&& (m_tEquip.tHead->fY > -16) && (m_tEquip.tHead->fY < 16))
	//		{
	//			m_Drag = true;
	//			cout << "투구 잡았당" << endl;
	//			//tempItem = (*iter);
	//		}
	//		
	//	}
	//}

	//iter		= m_vecInven.begin();

	//for(iter; iter != iter_end; ++iter)
	//{
	//	if(PtInRect((*iter)->GetRect(),pt) && m_Drag
	//		&& GetAsyncKeyState(VK_LBUTTON) && dwItemTime + 1000 < GetTickCount())
	//	{
	//		if((*iter)->GetItemType() == ITEM_HEAD)
	//		{
	//			dwItemTime = GetTickCount();
	//			cout << "투구 잡혔땅" << endl;
	//			tempItem = (*iter);
	//			(*iter) = m_tEquip.tHead;
	//			m_tEquip.tHead = tempItem;
	//			m_Drag = false;
	//		}
	//	}
	//}

	//if(!GetAsyncKeyState(VK_LBUTTON))
	//	m_Drag = false;

	////////////////////////////////////////////////////////////////////////////////////
	////장갑
	//if(!m_Drag)
	//{
	//	if(GetAsyncKeyState(VK_LBUTTON) && !m_Drag)
	//	{
	//		m_tEquip.tGloves->fX = CMouse::GetPos().x - m_tEquip.tGloves->GetInfo()->fX;
	//		m_tEquip.tGloves->fY = CMouse::GetPos().y - m_tEquip.tGloves->GetInfo()->fY;

	//		if((m_tEquip.tGloves->fX > -16) && (m_tEquip.tGloves->fX < 16)
	//			&& (m_tEquip.tGloves->fY > -16) && (m_tEquip.tGloves->fY < 16))
	//		{
	//			m_Drag = true;
	//			cout << "장갑 잡았당" << endl;
	//			//tempItem = (*iter);
	//		}
	//		
	//	}
	//}

	//iter		= m_vecInven.begin();

	//for(iter; iter != iter_end; ++iter)
	//{
	//	if(PtInRect((*iter)->GetRect(),pt) && m_Drag
	//		&& GetAsyncKeyState(VK_LBUTTON) && dwItemTime + 1000 < GetTickCount())
	//	{
	//		if((*iter)->GetItemType() == ITEM_GLOVES)
	//		{
	//			dwItemTime = GetTickCount();
	//			cout << "장갑 잡혔땅" << endl;
	//			tempItem = (*iter);
	//			(*iter) = m_tEquip.tGloves;
	//			m_tEquip.tGloves = tempItem;
	//			m_Drag = false;
	//		}
	//	}
	//}

	//if(!GetAsyncKeyState(VK_LBUTTON))
	//	m_Drag = false;

	////////////////////////////////////////////////////////////////////////////////////
	////장갑
	//if(!m_Drag)
	//{
	//	if(GetAsyncKeyState(VK_LBUTTON) && !m_Drag)
	//	{
	//		m_tEquip.tBoots->fX = CMouse::GetPos().x - m_tEquip.tBoots->GetInfo()->fX;
	//		m_tEquip.tBoots->fY = CMouse::GetPos().y - m_tEquip.tBoots->GetInfo()->fY;

	//		if((m_tEquip.tBoots->fX > -16) && (m_tEquip.tBoots->fX < 16)
	//			&& (m_tEquip.tBoots->fY > -16) && (m_tEquip.tBoots->fY < 16))
	//		{
	//			m_Drag = true;
	//			cout << "신발 잡았당" << endl;
	//			//tempItem = (*iter);
	//		}
	//		
	//	}
	//}

	//iter		= m_vecInven.begin();

	//for(iter; iter != iter_end; ++iter)
	//{
	//	if(PtInRect((*iter)->GetRect(),pt) && m_Drag
	//		&& GetAsyncKeyState(VK_LBUTTON) && dwItemTime + 1000 < GetTickCount())
	//	{
	//		if((*iter)->GetItemType() == ITEM_SHOES)
	//		{
	//			dwItemTime = GetTickCount();
	//			cout << "신발 잡혔땅" << endl;
	//			tempItem = (*iter);
	//			(*iter) = m_tEquip.tBoots;
	//			m_tEquip.tBoots = tempItem;
	//			m_Drag = false;
	//		}
	//	}
	//}

	//if(!GetAsyncKeyState(VK_LBUTTON))
	//{
	//	m_Drag = false;
	//}

}
void CPlayer::TileCrush(TILE*	_Tile)
{
	if(m_bIsSuper)
	{
		return;
	}

	switch(_Tile->iOption)
	{
		//빈 타일 충돌
	case TILE_NORMAL:
		//캐릭터의 바닥이 빈 타일일 때, 추락 상태 적용

		if((_Tile->fX - (_Tile->fCX / 2) <= m_tInfo.fX)
			&& (_Tile->fX + (_Tile->fCX / 2) >= m_tInfo.fX)
			&& (_Tile->fY - (_Tile->fCY / 2) <= m_tInfo.fY + 40)
			&& (_Tile->fY + (_Tile->fCY / 2) >= m_tInfo.fY + 40))
		{
			//cout << "일반 타일" << endl;
			if(m_bIsClimb)
				m_bIsClimb = false;

			if(m_bIsHill)
				m_bIsHill = false;

			if(GetAsyncKeyState(VK_UP))
			{
				return;
			}

			if(m_bIsFall == false && m_bIsJump == false)
			{
				//cout << "추락 상태!" << endl << endl;
				m_bIsFall = true;
				//m_tInfo.fY -= 5;
				m_fJumpAcc = 10.f;
				m_bIsJump = true;
			}

			if(m_dwState == PLY_CLIMB)
			{
				m_eArrow = DIR_RIGHT;
				m_dwState = PLY_STAND;
				m_pName = L"Right_Player";
				m_bIsClimb = false;
			}
			return;
		}
		break;


		//접근 불가 타일(바닥 벽 등등)
	case TILE_DISABLE:

		//캐릭터가 왼쪽 벽에 닿았을 때 밀어준다.
		if((_Tile->fX - (_Tile->fCX / 2) <= m_tInfo.fX - 20)
			&& (_Tile->fX + (_Tile->fCX / 2) >= m_tInfo.fX - 20)
			&& (_Tile->fY - (_Tile->fCY / 2) <= m_tInfo.fY)
			&& (_Tile->fY + (_Tile->fCY / 2) >= m_tInfo.fY))
		{

			m_tInfo.fX += 2;

			if(m_bIsClimb)
				m_bIsClimb = false;

			if(m_bIsHill)
				m_bIsHill = false;

			return;
			//m_fJumpAcc = 0.f;
			//m_bIsJump = false;
		}

		//캐릭터가 오른쪽 벽에 닿았을 때 밀어준다.
		if((_Tile->fX - (_Tile->fCX / 2) <= m_tInfo.fX + 20)
			&& (_Tile->fX + (_Tile->fCX / 2) >= m_tInfo.fX + 20)
			&& (_Tile->fY - (_Tile->fCY / 2) <= m_tInfo.fY)
			&& (_Tile->fY + (_Tile->fCY / 2) >= m_tInfo.fY))
		{
			m_tInfo.fX -= 2;

			if(m_bIsClimb)
				m_bIsClimb = false;
			return;
			//m_fJumpAcc = 0.f;
			//m_bIsJump = false;
		}
		//캐릭터의 바닥이 닿았을 때 타일 위로 올려준다.
		if((_Tile->fX - (_Tile->fCX / 2) <= m_tInfo.fX)
			&& (_Tile->fX + (_Tile->fCX / 2) >= m_tInfo.fX)
			&& (_Tile->fY - (_Tile->fCY / 2) <= m_tInfo.fY + 30)
			&& (_Tile->fY + (_Tile->fCY / 2) >= m_tInfo.fY + 30))
		{
			//cout << "착륙 상태!" << endl << endl;
			m_tInfo.fY -= 5;
			m_fJumpAcc = 0.f;
			m_bIsJump = false;
			m_bIsFall = false;

			if(m_bIsClimb)
				m_bIsClimb = false;
			return;
		}
		break;

	case TILE_HILL:

		//캐릭터의 바닥이 닿았을 때 타일 위로 올려준다.
		if((_Tile->fX - (_Tile->fCX / 2) <= m_tInfo.fX)
			&& (_Tile->fX + (_Tile->fCX / 2) >= m_tInfo.fX)
			&& (_Tile->fY - (_Tile->fCY / 2) <= m_tInfo.fY + 30)
			&& (_Tile->fY + (_Tile->fCY / 2) >= m_tInfo.fY + 30))
		{
			if(!m_bIsGhost)
			{
				m_tInfo.fY -= 5;
				m_fJumpAcc = 0.f;
				m_bIsJump = false;
				m_bIsFall = false;
			}

			//cout << "착지! Y : " << m_tInfo.fY << endl;

			if(m_bIsClimb)
				m_bIsClimb = false;

			return;
		}

		if((_Tile->fX - (_Tile->fCX / 2) <= m_tInfo.fX)
			&& (_Tile->fX + (_Tile->fCX / 2) >= m_tInfo.fX)
			&& (_Tile->fY - (_Tile->fCY / 2) <= m_tInfo.fY + 40)
			&& (_Tile->fY + (_Tile->fCY / 2) >= m_tInfo.fY + 40))
		{
			//cout << "언덕 밟고있음!" << endl;
			if(m_bIsClimb)
				m_bIsClimb = false;

			if(!m_bIsHill)
				m_bIsHill = true;

			//if(GetAsyncKeyState(VK_DOWN))
			//{
			//	if(GetAsyncKeyState(VK_MENU))
			//	{
			//		m_bIsJump = true;
			//		m_bIsFall = true;
			//		m_fJumpAcc = 5.f;
			//		m_bIsGhost = true;
			//	}
			//}
		}
		break;

	case TILE_LINE:

		//라인 타일에 캐릭터의 바닥이 닿았을때 업,다운키 사용 가능
		if((_Tile->fX - (_Tile->fCX / 2) <= m_tInfo.fX)
			&& (_Tile->fX + (_Tile->fCX / 2) >= m_tInfo.fX)
			&& (_Tile->fY - (_Tile->fCY / 2) <= m_tInfo.fY + 30)
			&& (_Tile->fY + (_Tile->fCY / 2) >= m_tInfo.fY + 30))
		{

			if(m_bIsHill)
				m_bIsHill = false;

			if(GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN))
			{
				m_tInfo.fX = _Tile->fX;
			}
			m_bIsClimb = true;
		}
		break;

	case TILE_TOPLINE:

		//탑라인 타일에 캐릭터의 바닥이 닿았을때 기본 모습으로 돌아오며 오르기 불가
		if((_Tile->fX - (_Tile->fCX / 2) <= m_tInfo.fX)
			&& (_Tile->fX + (_Tile->fCX / 2) >= m_tInfo.fX)
			&& (_Tile->fY - (_Tile->fCY / 2) <= m_tInfo.fY + 32)
			&& (_Tile->fY + (_Tile->fCY / 2) >= m_tInfo.fY + 32))
		{


			m_bIsClimb = true;

			//아래 방향키를 누르지 않을 경우 충돌해서 내려가지 못함.
			if(!GetAsyncKeyState(VK_DOWN))
			{
				if(m_tInfo.fY + 30 >= _Tile->fY - 15)
				{
					m_tInfo.fY -= 5;
					m_fJumpAcc = 0.f;
					m_bIsJump = false;
					m_bIsFall = false;
				}
			}
			else if(GetAsyncKeyState(VK_DOWN))
			{
				m_tInfo.fX = _Tile->fX;
			}

			if(m_bIsHill)
				m_bIsHill = false;
		}

		if((_Tile->fX - (_Tile->fCX / 2) <= m_tInfo.fX)
			&& (_Tile->fX + (_Tile->fCX / 2) >= m_tInfo.fX)
			&& (_Tile->fY - (_Tile->fCY / 2) <= m_tInfo.fY + 40)
			&& (_Tile->fY + (_Tile->fCY / 2) >= m_tInfo.fY + 40))
		{
			//cout << "줄언덕 밟고있음!" << endl;
			if(!m_bIsClimb)
			{
				//cout << "True" << endl;
				m_bIsClimb = true;
			}
		}
		break;
	}

}
void CPlayer::FrameMove(void)
{


	if(m_dwState != m_dwPrevState)
	{
		switch(m_dwState)
		{
		case PLY_STAND:
			m_tFrame = FRAME(0, 4, 0, 400);
			break;
		case PLY_RUN:
			m_tFrame = FRAME(0, 3, 1, 150);
			break;
		case PLY_JUMP:
			m_tFrame = FRAME(0, 0, 2, 1000);
			break;
		case PLY_ALERT:
			m_tFrame = FRAME(0, 4, 3, 400);
			break;
		case PLY_PRONE:
			m_tFrame = FRAME(1, 1, 2, 100000);
			break;
		case PLY_CLIMB:
			m_tFrame = FRAME(0, 1, 0, 500);
			break;
		case PLY_SHOOT:
			m_tFrame = FRAME(0, 4, 4, 150);
			break;
		case PLY_DRIVE:
			m_tFrame = FRAME(0, 2, 0, 200);
			break;
		case PLY_HIGH:
			m_tFrame = FRAME(0, 2, 1, 200);
			break;
		case PLY_ENREAL:
			m_tFrame = FRAME(0, 2, 2, 400);
			break;

		}
		m_dwPrevState = m_dwState;
	}

	if(m_dwFrameTime + m_tFrame.dwFrameTime < GetTickCount())
	{
		m_dwFrameTime = GetTickCount();
		++m_tFrame.iFrameStart;
		//cout << "Frameeeeeeeee : " << m_tFrame.iFrameStart << endl;
	}



	if(m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
	{
		m_tFrame.iFrameStart = 0;

		if(m_dwState == PLY_DRIVE)
		{
			m_bIsDrive	=	false;
		}

		if(m_dwState == PLY_HIGH)
		{
			m_bIsSuper	=	false;
		}

		if(m_dwState == PLY_ENREAL)
		{
			m_bIsSuper	=	false;
		}

		//공격 중 상태일 경우 상태 해제
		if(m_bIsAtk)
		{
			m_bIsAtk = false;
			m_dwState = PLY_STAND;
		}

		if(m_bIsSkilling)
		{
			m_bIsSkilling	= false;
			
			m_dwState		= PLY_STAND;

			if(m_eArrow == DIR_RIGHT)
			{
				m_pName = L"Right_Player";
			}
			else if(m_eArrow == DIR_LEFT)
			{
				m_pName = L"Left_Player";
			}
		}
	}
}

void CPlayer::KeyCheck(void)
{
	static bool bIsPress = false;

	if(m_dwState != PLY_STAND && m_dwState != PLY_CLIMB
		&& !m_bIsAtk && !m_bIsSkilling && !m_bIsRing)
	{
		m_dwState		= PLY_STAND;
	}

	if(GetAsyncKeyState(VK_LEFT))
	{
		//등반중이 아니고 공격을 하지않고 있거나 점프하면서 공격하고 있을 때
		if(m_dwState != PLY_CLIMB &&  (!m_bIsAtk || (m_bIsAtk && m_bIsJump))
			&& !m_bIsSkilling)
		{
			m_tInfo.fX -= m_fSpeed;
			m_pName = L"Left_Player";
			m_eArrow = DIR_LEFT;
			m_dwState = PLY_RUN;
		}
	}
	else if(GetAsyncKeyState(VK_RIGHT))
	{
		if(m_dwState != PLY_CLIMB &&  (!m_bIsAtk || (m_bIsAtk && m_bIsJump))
			&& !m_bIsSkilling)
		{
			m_tInfo.fX += m_fSpeed;
			m_pName = L"Right_Player";
			m_eArrow = DIR_RIGHT;
			m_dwState = PLY_RUN;
		}
	}
	else if(GetAsyncKeyState(VK_DOWN) && !m_bIsSkilling)
	{
		if(m_bIsClimb && !m_bIsAtk)
		{
			m_bIsJump = false;
			m_bIsFall = false;
			m_dwState = PLY_CLIMB;
			m_pName = L"Climb_Player";
			m_tInfo.fY += m_fSpeed;
		}
		else if(!m_bIsAtk)
			m_dwState = PLY_PRONE;

		//하향 점프
		if(GetAsyncKeyState(VK_MENU) && m_bIsHill)
		{
			m_bIsJump = true;
			m_bIsFall = true;
			m_fJumpAcc = 5.f;
			m_bIsGhost = true;
		}
	}
	else if(GetAsyncKeyState(VK_UP))
	{
		if(m_bIsClimb && !m_bIsAtk)
		{
			m_bIsJump = false;
			m_bIsFall = false;
			m_dwState = PLY_CLIMB;
			m_pName = L"Climb_Player";
			m_tInfo.fY -= m_fSpeed;
		}
	}

	//스킬////////////////////////////////////////////////////////////////////////
	//차지 드라이브
	if(GetAsyncKeyState('A') & 1 && (m_dwState != PLY_CLIMB))
	{
		if(!m_bIsSkilling)
		{
			m_bIsDrive	=	true;

			if(m_eArrow == DIR_RIGHT)
			{
				m_pName		=	L"Right_Skill_Player";
			}
			else if(m_eArrow == DIR_LEFT)
			{
				m_pName		=	L"Left_Skill_Player";
			}
			m_dwState	=	PLY_DRIVE;
			CObj* pObj	=	new CAtk(m_tInfo.fX, m_tInfo.fY, Atk_DRIVER, m_eArrow, m_tPlayer.iAtk);
			pObj->Initialize();
			m_tPlayer.iMp	-= 10;
			
			CSoundMgr::GetInstance()->PlaySound(L"charge.mp3");



			CObjMgr::GetInstance()->AddObj(pObj, OBJ_ATK);
		}
		
		m_bIsSkilling = true;

		//캐릭터 좌우에 따라 스킬 모션 이미지 달라짐
		if(m_eArrow == DIR_RIGHT)
		{
		}
		else if(m_eArrow == DIR_LEFT)
		{
		}
	}

	//하이킥 데몰리션
	if(GetAsyncKeyState('Z') & 1 && (m_dwState != PLY_CLIMB))
	{
		if(!m_bIsSkilling)
		{
			m_bIsHigh	=	true;

			if(m_eArrow == DIR_RIGHT)
			{
				m_pName		=	L"Right_Skill_Player";
			}
			else if(m_eArrow == DIR_LEFT)
			{
				m_pName		=	L"Left_Skill_Player";
			}

			m_dwState	=	PLY_HIGH;
			CObj* pObj	=	new CAtk(m_tInfo.fX, m_tInfo.fY, Atk_HIGH, m_eArrow, m_tPlayer.iAtk);
			pObj->Initialize();
			m_tPlayer.iMp	-= 10;

			CSoundMgr::GetInstance()->PlaySound(L"high.mp3");

		
			CObjMgr::GetInstance()->AddObj(pObj, OBJ_ATK);
			m_tInfo.fY -= 200;
			m_bIsSuper	=	true;
		}
		
		m_bIsSkilling = true;

		//캐릭터 좌우에 따라 스킬 모션 이미지 달라짐
		if(m_eArrow == DIR_RIGHT)
		{
		}
		else if(m_eArrow == DIR_LEFT)
		{
		}
	}
	
	//래쓰오브 엔릴
	if(GetAsyncKeyState('C') & 1 && (m_dwState != PLY_CLIMB))
	{
		if(!m_bIsSkilling)
		{
			m_bIsHigh	=	true;

			if(m_eArrow == DIR_RIGHT)
			{
				m_pName		=	L"Right_Skill_Player";
			}
			else if(m_eArrow == DIR_LEFT)
			{
				m_pName		=	L"Left_Skill_Player";
			}

			m_dwState	=	PLY_ENREAL;
			CObj* pObj	=	new CAtk(m_tInfo.fX, m_tInfo.fY, Atk_ENREAL, m_eArrow, m_tPlayer.iAtk);
			pObj->Initialize();
			m_tPlayer.iMp	-= 1000;

			CSoundMgr::GetInstance()->PlaySound(L"enreal.mp3");

		
			CObjMgr::GetInstance()->AddObj(pObj, OBJ_ATK);
			m_bIsSuper	=	true;
		}
		
		m_bIsSkilling = true;

		//캐릭터 좌우에 따라 스킬 모션 이미지 달라짐
		if(m_eArrow == DIR_RIGHT)
		{
		}
		else if(m_eArrow == DIR_LEFT)
		{
		}
	}
	
	//이슈타르의 링
	if(GetAsyncKeyState('X') & 1 && (m_dwState != PLY_CLIMB))
	{
		if(!m_bIsRing)
		{
			m_bIsRing	=	true;
			m_dwState	=	PLY_SHOOT;
			//m_pName		=	L"Right_Skill_Player";
			CObj* pObj	=	new CAtk(m_tInfo.fX, m_tInfo.fY, Atk_RING, m_eArrow, m_tPlayer.iAtk);
			pObj->Initialize();
			m_tPlayer.iMp	-= 1000;


			CSoundMgr::GetInstance()->PlaySound(L"ring_prepare.mp3");
		
			CObjMgr::GetInstance()->AddObj(pObj, OBJ_ATK);
		}
	}

	//이슈타르 링 해제
	if(!GetAsyncKeyState('X') && m_bIsRing)
	{
		m_bIsRing	=	false;
	}
	//////////////////////////////////////////////////////////////////////////

	if(GetAsyncKeyState(VK_LCONTROL) & 1 && (m_dwState != PLY_CLIMB))
	{
		if(!m_bIsAtk)
		{
			CObj*	pObj = new CAtk(m_tInfo.fX,m_tInfo.fY, Atk_SHOOT, m_eArrow, m_tPlayer.iAtk);
			pObj->Initialize();

			CObjMgr::GetInstance()->AddObj(pObj, OBJ_ATK);
		}

		m_dwState = PLY_SHOOT;
		m_bIsAtk = true;		//공격 여부 판단.
		//m_pName = L"Right_Battle";
	}

	if(GetAsyncKeyState(VK_MENU) && !m_bIsSkilling)
	{
		if((GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT)) && bIsPress == false
			&& m_bIsClimb)
		{
			m_dwState = PLY_JUMP;
			bIsPress = true;
			m_bIsJump = true;
		}

		if(!m_bIsClimb)
		{
			m_dwState = PLY_JUMP;
			bIsPress = true;
			m_bIsJump = true;
		}

		//if(GetAsyncKeyState(VK_MENU) && bIsPress == false)
		//{
		//	bIsPress = true;
		//	m_bIsJump = true;
		//}
	}
	if(!GetAsyncKeyState(VK_MENU) && bIsPress == true)
		bIsPress = false;

	if(m_bIsJump == true)
	{
		m_dwState = PLY_JUMP;

		//점프 상태일 때 점프 가속도는 계속해서 증가하게 된다..
		m_fJumpAcc += 0.3f;	// <== 얘는 점프 가속도...
		//cout << "점프가속도 : " << m_fJumpAcc;
		//cout << ", 플레이어Y  : " << m_tInfo.fY << endl;

		//위치에 점프 속도를 더하고
		//속도에 가속도를 더한다..

		m_tInfo.fY += -8.f + m_fJumpAcc;
	}

	if(m_bIsKnockBack)
	{
		if(m_fKnockBack < -0.5f)
		{
			//cout << "넉배액" << endl;
			//cout << "X: " << m_tInfo.fX << endl;
			m_fKnockBack += 0.065f;
			m_tInfo.fX += m_fKnockBack;
		}
		else if(m_fKnockBack > 0.5f)
		{
			//cout << "넉백백" << endl;
			m_fKnockBack += -0.065f;
			m_tInfo.fX += m_fKnockBack;
		}
		else
			m_bIsKnockBack = false;
	}

	if(m_bIsAtk)
	{
		m_dwState = PLY_SHOOT;
	}
}
void CPlayer::Scroll(void)
{
	if(m_tInfo.fX + m_ptScroll.x > WINCX / 2)
	{
		float fSpeed = (m_tInfo.fX + m_ptScroll.x) - WINCX / 2;
		fSpeed /= 32.f;

		m_ptScroll.x -= (long)fSpeed;

		//스테이지에 맞는 스크롤 값 부여
		switch(m_iPrevMap)
		{
		case 1:
			if(m_ptScroll.x < WINCX - 1483)
				m_ptScroll.x = WINCX - 1483;
			break;
		case 2:
			if(m_ptScroll.x < WINCX - 1621)
				m_ptScroll.x = WINCX - 1621;
			break;
		case 3:
			if(m_ptScroll.x < WINCX - 2102)
				m_ptScroll.x = WINCX - 2102;
			break;
		}
	}
	//왼쪽
	if(m_tInfo.fX + m_ptScroll.x < WINCX / 2)
	{
		float fSpeed = WINCX / 2 - (m_tInfo.fX + m_ptScroll.x);
		fSpeed /= 32.f;

		m_ptScroll.x += (long)fSpeed;

		if(m_ptScroll.x > 0)
			m_ptScroll.x = 0;
	}

	//아래
	if(m_tInfo.fY + m_ptScroll.y > WINCY / 2)
	{
		float fSpeed = (m_tInfo.fY + m_ptScroll.y) - WINCY / 2;
		fSpeed /= 32.f;

		m_ptScroll.y -= (long)fSpeed;

		//스테이지에 맞는 스크롤 값 부여
		switch(m_iPrevMap)
		{
		case 1:
			if(m_ptScroll.y < WINCY - 1200)
				m_ptScroll.y = WINCY - 1200;
			break;
		case 2:
			if(m_ptScroll.y < WINCY - 1240)
				m_ptScroll.y = WINCY - 1240;
			break;
		case 3:
			if(m_ptScroll.y < WINCY - 1200)
				m_ptScroll.y = WINCY - 1200;
			break;
		}
	}
	//위
	if(m_tInfo.fY + m_ptScroll.y < WINCY / 2)
	{
		float fSpeed = WINCY / 2 - (m_tInfo.fY + m_ptScroll.y);
		fSpeed /= 32.f;

		m_ptScroll.y += (long)fSpeed;

		if(m_ptScroll.y > 0)
			m_ptScroll.y = 0;
	}
}

void CPlayer::HpMgr(int _iDmg, int iAtkType, eArrow e_Arrow)
{

	if(m_dwActiveTime + 2000 < GetTickCount())
	{
		m_dwActiveTime = GetTickCount();
		cout << "HP : " << m_tPlayer.iHp << endl;
		//m_dwActiveTime = GetTickCount();
		m_tPlayer.iHp -= _iDmg + (_iDmg / (rand() % 10) + (rand() % 100));
		m_bIsKnockBack = true;
		m_bIsJump		= true;
		m_fJumpAcc		= 3.f;

		CObj* pEffect = new CEffect(m_tInfo.fX, m_tInfo.fY, _iDmg + (_iDmg / (rand() % 10) + (rand() % 100)), Atk_DMG, true);
		pEffect->Initialize();

		CObjMgr::GetInstance()->AddObj(pEffect, OBJ_EFFECT);

		switch(e_Arrow)
		{
		case DIR_RIGHT:
			m_pName = L"Right_Player";
			m_eArrow = DIR_RIGHT;
			m_fKnockBack = -4.f;
			break;
		case DIR_LEFT:
			m_pName = L"Left_Player";
			m_eArrow = DIR_LEFT;
			m_fKnockBack = 4.f;
			break;
		}
		m_bIsSuper	=	false;
	}
}