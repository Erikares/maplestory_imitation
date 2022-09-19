#include "StdAfx.h"
#include "Item.h"

CItem::CItem(void)
:m_pName(NULL), m_tempItem(NULL)
{
	m_tInfo.fX = 0;
	m_tInfo.fY = 0;
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;

	m_Drag = false;

}

CItem::~CItem(void)
{
}

void CItem::Update(void)
{
	m_Rect.left = static_cast<int>(m_tInfo.fX - (m_tInfo.fCX / 2));
	m_Rect.right = static_cast<int>(m_tInfo.fX + (m_tInfo.fCX / 2));
	m_Rect.top = static_cast<int>(m_tInfo.fY - (m_tInfo.fCY / 2));
	m_Rect.bottom = static_cast<int>(m_tInfo.fY + (m_tInfo.fCY / 2));

	MouseCheck();
}

void CItem::MouseCheck(void)
{
	POINT	pt = CMouse::GetPos();

	if(GetAsyncKeyState(VK_LBUTTON) && !m_Drag)
	{
		m_Drag = true;
		fX = CMouse::GetPos().x - m_tInfo.fX;
		fY = CMouse::GetPos().y - m_tInfo.fY;
	}

	if((fX > -16) && (fX < 16) && (fY > -16) && (fY < 16))
	{
		if(GetAsyncKeyState(VK_LBUTTON))
		{
			CursorName = m_tItem.pName;
			m_tempItem = this;
			m_tInfo.fX = static_cast<float>(CMouse::GetPos().x);
			m_tInfo.fY = static_cast<float>(CMouse::GetPos().y);
		}
	}



	//if(PtInRect(m_pEquip->tWeapon->GetRect(),pt) && m_Drag && !GetAsyncKeyState(VK_LBUTTON))
	//{
	//	MessageBox(g_hWnd, L"¿ì¿Õ", L"¿ì¿Õ", MB_OK);
	//	//m_tempItem = m_pEquip->tWeapon;
	//	m_pEquip->tWeapon = this;
	//	//this = m_tempItem;
	//}

	if(0 == GetAsyncKeyState(VK_LBUTTON))
	{
		m_Drag = false;
	}
}

void CItem::SetItem(int _iCode)
{
	switch(_iCode)
	{
	case 0:
		m_tItem.iCode		=	0;
		m_tItem.eType		=	ITEM_END;
		m_tItem.iAp			=	0;
		m_tItem.iAtk		=	0;
		m_tItem.iDef		=	0;
		m_tItem.iPrice		=	0;
		m_tItem.pName = L"None";
		m_pName = L"";
		break;
	case 1:
		m_tItem.iCode		=	1;
		m_tItem.eType		=	ITEM_USE;
		m_tItem.iAp			=	150;
		m_tItem.iAtk		=	0;
		m_tItem.iDef		=	0;
		m_tItem.iPrice		=	100;
		m_tItem.pName = L"Red_Potion";
		m_pName = L"»¡°£ Æ÷¼Ç";
		break;
	case 100:
		m_tItem.iCode		=	100;
		m_tItem.eType		=	ITEM_WP;
		m_tItem.iAp			=	0;
		m_tItem.iAtk		=	50;
		m_tItem.iDef		=	0;
		m_tItem.iPrice		=	500;
		m_tItem.pName = L"Gunbow01";
		m_pName = L"°Çº¸¿ì";
		
		break;
	case 200:
		m_tItem.iCode		=	200;
		m_tItem.eType		=	ITEM_AR;
		m_tItem.iAp			=	0;
		m_tItem.iAtk		=	0;
		m_tItem.iDef		=	30;
		m_tItem.iPrice		=	500;
		m_tItem.pName = L"Armor01";
		m_pName = L"¹Ù¶÷ÀÇ°©ÁÖ";
		break;

	case 300:
		m_tItem.iCode		=	300;
		m_tItem.eType		=	ITEM_HEAD;
		m_tItem.iAp			=	0;
		m_tItem.iAtk		=	0;
		m_tItem.iDef		=	30;
		m_tItem.iPrice		=	500;
		m_tItem.pName = L"Hat01";
		m_pName = L"¹Ù¶÷ÀÇ º£·¹¸ð";
		break;

	case 400:
		m_tItem.iCode		=	400;
		m_tItem.eType		=	ITEM_GLOVES;
		m_tItem.iAp			=	0;
		m_tItem.iAtk		=	0;
		m_tItem.iDef		=	30;
		m_tItem.iPrice		=	500;
		m_tItem.pName = L"Gloves01";
		m_pName = L"ºûÀÇ ÆÈÂî";
		break;

	case 500:
		m_tItem.iCode		=	500;
		m_tItem.eType		=	ITEM_SHOES;
		m_tItem.iAp			=	0;
		m_tItem.iAtk		=	0;
		m_tItem.iDef		=	30;
		m_tItem.iPrice		=	500;
		m_tItem.pName = L"Shoes01";
		m_pName = L"ºûÀÇ ºÎÃ÷";
		break;
	}
}

