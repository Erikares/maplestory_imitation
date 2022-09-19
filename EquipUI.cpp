#include "StdAfx.h"
#include "EquipUI.h"

CEquipUI::CEquipUI(void)
{
	m_tInfo.fX = WINCX / 2 - 200;
	m_tInfo.fY = WINCY / 2;
	m_tInfo.fCX = 237.f;
	m_tInfo.fCY = 332.f;

	m_Act	=	false;
	m_Drag	=	false;
	m_DragAct = false;
}

CEquipUI::~CEquipUI(void)
{
	Release();
}

void CEquipUI::Initialize()
{
	//�÷��̾��� ���â�� ������.
	m_pEquip = static_cast<CPlayer*>(m_pPlayer)->GetEquip();
}

void CEquipUI::Update()
{
	//Ȱ��ȭ �Ǿ������� ����
	if(m_Act)	
	{
		//���콺�� ó�� �������� ��Ʈ�� ������ Ŭ���� ��ǥ�� ���� ����
		if(GetAsyncKeyState(VK_LBUTTON) && !m_Drag)
		{
			m_Drag = true;
			fX = CMouse::GetPos().x - m_tInfo.fX;
			fY = CMouse::GetPos().y - m_tInfo.fY;
			//cout << "fX : " << fX << ", fY : " << fY << endl;
		}

		//ó�� ���ȴ� ���� UI�� ��� ��ġ��� ������ ���¿��� ��� �����.
		if((fX>=-81) && (fX<= 63) && (fY>=-165) && (fY<=-148) && m_DragAct)
		{
			if(GetAsyncKeyState(VK_LBUTTON))	//��� �� �� ���콺 ����
			{
				m_tInfo.fX	= CMouse::GetPos().x - fX;
				m_tInfo.fY	= CMouse::GetPos().y - fY;
			}
		}

		//���콺�� ������ ���¶�� Ŭ������ �� ���� 0, false�� ����
		if(0 == GetAsyncKeyState(VK_LBUTTON))
		{
			fX = 0;
			fY = 0;
			m_Drag = false;
		}
	}

	CUI::Update();
}

void CEquipUI::Render()
{
	if(m_Act)
	{
		TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer")
			,static_cast<int>(m_tInfo.fX - m_tInfo.fCX / 2)
			,static_cast<int>(m_tInfo.fY - m_tInfo.fCY / 2)
			,static_cast<int>(232.f)
			,static_cast<int>(332.f)
			,CBitMgr::GetInstance()->GetImage(L"EquipUI")
			, 0
			, 0
			, static_cast<int>(m_tInfo.fCX)
			, static_cast<int>(m_tInfo.fCY)
			, RGB(255, 0, 255));


		//���� ����
		if(m_pEquip->tWeapon)
		{
			m_pEquip->tWeapon->GetInfo()->fX = m_tInfo.fX - 43;
			m_pEquip->tWeapon->GetInfo()->fY = m_tInfo.fY + 26;
			m_pEquip->tWeapon->Update();

			//Rectangle(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
			//	m_pEquip->tWeapon->GetInfo()->fX - m_pEquip->tWeapon->GetInfo()->fCX / 2,
			//	m_pEquip->tWeapon->GetInfo()->fY - m_pEquip->tWeapon->GetInfo()->fCY / 2,
			//	m_pEquip->tWeapon->GetInfo()->fX + m_pEquip->tWeapon->GetInfo()->fCX / 2,
			//	m_pEquip->tWeapon->GetInfo()->fY + m_pEquip->tWeapon->GetInfo()->fCY / 2);

			TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer")
				,static_cast<int>(m_pEquip->tWeapon->GetInfo()->fX - m_pEquip->tWeapon->GetInfo()->fCX / 2)
				,static_cast<int>(m_pEquip->tWeapon->GetInfo()->fY - m_pEquip->tWeapon->GetInfo()->fCY / 2)
				,static_cast<int>(32.f)
				,static_cast<int>(32.f)
				,CBitMgr::GetInstance()->GetImage(m_pEquip->tWeapon->GetItemName())
				, 0
				, 0
				, 32
				, 32
				, RGB(255, 0, 255));
		}
		//�Ƹ� ����
		if(m_pEquip->tArmor)
		{
			m_pEquip->tArmor->GetInfo()->fX = m_tInfo.fX - 3;
			m_pEquip->tArmor->GetInfo()->fY = m_tInfo.fY + 26;
			m_pEquip->tArmor->Update();

			//Rectangle(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
			//	m_pEquip->tArmor->GetInfo()->fX - m_pEquip->tArmor->GetInfo()->fCX / 2,
			//	m_pEquip->tArmor->GetInfo()->fY - m_pEquip->tArmor->GetInfo()->fCY / 2,
			//	m_pEquip->tArmor->GetInfo()->fX + m_pEquip->tArmor->GetInfo()->fCX / 2,
			//	m_pEquip->tArmor->GetInfo()->fY + m_pEquip->tArmor->GetInfo()->fCY / 2);

			TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer")
				,static_cast<int>(m_pEquip->tArmor->GetInfo()->fX - m_pEquip->tArmor->GetInfo()->fCX / 2)
				,static_cast<int>(m_pEquip->tArmor->GetInfo()->fY - m_pEquip->tArmor->GetInfo()->fCY / 2)
				,static_cast<int>(32.f)
				,static_cast<int>(32.f)
				,CBitMgr::GetInstance()->GetImage(m_pEquip->tArmor->GetItemName())
				, 0
				, 0
				, 32
				, 32
				, RGB(255, 0, 255));
		}

		//���� ����
		if(m_pEquip->tBoots)
		{
			m_pEquip->tBoots->GetInfo()->fX = m_tInfo.fX - 3;
			m_pEquip->tBoots->GetInfo()->fY = m_tInfo.fY + 107;
			m_pEquip->tBoots->Update();

			//Rectangle(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
			//	m_pEquip->tBoots->GetInfo()->fX - m_pEquip->tBoots->GetInfo()->fCX / 2,
			//	m_pEquip->tBoots->GetInfo()->fY - m_pEquip->tBoots->GetInfo()->fCY / 2,
			//	m_pEquip->tBoots->GetInfo()->fX + m_pEquip->tBoots->GetInfo()->fCX / 2,
			//	m_pEquip->tBoots->GetInfo()->fY + m_pEquip->tBoots->GetInfo()->fCY / 2);

			TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer")
				,static_cast<int>(m_pEquip->tBoots->GetInfo()->fX - m_pEquip->tBoots->GetInfo()->fCX / 2)
				,static_cast<int>(m_pEquip->tBoots->GetInfo()->fY - m_pEquip->tBoots->GetInfo()->fCY / 2)
				,static_cast<int>(32.f)
				,static_cast<int>(32.f)
				,CBitMgr::GetInstance()->GetImage(m_pEquip->tBoots->GetItemName())
				, 0
				, 0
				, 32
				, 32
				, RGB(255, 0, 255));
		}

		//�۷��� ����
		if(m_pEquip->tGloves)
		{
			m_pEquip->tGloves->GetInfo()->fX = m_tInfo.fX + 37;
			m_pEquip->tGloves->GetInfo()->fY = m_tInfo.fY + 67;
			m_pEquip->tGloves->Update();

			//Rectangle(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
			//	m_pEquip->tGloves->GetInfo()->fX - m_pEquip->tGloves->GetInfo()->fCX / 2,
			//	m_pEquip->tGloves->GetInfo()->fY - m_pEquip->tGloves->GetInfo()->fCY / 2,
			//	m_pEquip->tGloves->GetInfo()->fX + m_pEquip->tGloves->GetInfo()->fCX / 2,
			//	m_pEquip->tGloves->GetInfo()->fY + m_pEquip->tGloves->GetInfo()->fCY / 2);

			TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer")
				,static_cast<int>(m_pEquip->tGloves->GetInfo()->fX - m_pEquip->tGloves->GetInfo()->fCX / 2)
				,static_cast<int>(m_pEquip->tGloves->GetInfo()->fY - m_pEquip->tGloves->GetInfo()->fCY / 2)
				,static_cast<int>(32.f)
				,static_cast<int>(32.f)
				,CBitMgr::GetInstance()->GetImage(m_pEquip->tGloves->GetItemName())
				, 0
				, 0
				, 32
				, 32
				, RGB(255, 0, 255));
		}

		//��� ����
		if(m_pEquip->tHead)
		{
			m_pEquip->tHead->GetInfo()->fX = m_tInfo.fX - 3;
			m_pEquip->tHead->GetInfo()->fY = m_tInfo.fY - 97;
			m_pEquip->tHead->Update();

			//Rectangle(CBitMgr::GetInstance()->GetImage(L"BackBuffer"),
			//	m_pEquip->tHead->GetInfo()->fX - m_pEquip->tHead->GetInfo()->fCX / 2,
			//	m_pEquip->tHead->GetInfo()->fY - m_pEquip->tHead->GetInfo()->fCY / 2,
			//	m_pEquip->tHead->GetInfo()->fX + m_pEquip->tHead->GetInfo()->fCX / 2,
			//	m_pEquip->tHead->GetInfo()->fY + m_pEquip->tHead->GetInfo()->fCY / 2);

			TransparentBlt(CBitMgr::GetInstance()->GetImage(L"BackBuffer")
				,static_cast<int>(m_pEquip->tHead->GetInfo()->fX - m_pEquip->tHead->GetInfo()->fCX / 2)
				,static_cast<int>(m_pEquip->tHead->GetInfo()->fY - m_pEquip->tHead->GetInfo()->fCY / 2)
				,static_cast<int>(32.f)
				,static_cast<int>(32.f)
				,CBitMgr::GetInstance()->GetImage(m_pEquip->tHead->GetItemName())
				, 0
				, 0
				, 32
				, 32
				, RGB(255, 0, 255));
		}
	}
}

void CEquipUI::Release()
{
}

bool CEquipUI::HighRect(void)
{
	if((fX>=-116) && (fX<= 116) && (fY>=-166) && (fY<=166))
	{
		if(GetAsyncKeyState(VK_LBUTTON))	//�ֻ��� ��Ʈ�� ����
		{
			return true;
		}
	}
	return false;
}