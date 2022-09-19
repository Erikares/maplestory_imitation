#include "StdAfx.h"
#include "UI.h"

CUI::CUI(void)
{
}

CUI::~CUI(void)
{
}

void CUI::Update(void)
{
	m_Rect.left = static_cast<long>(m_tInfo.fX - (m_tInfo.fCX / 2));
	m_Rect.right = static_cast<long>(m_tInfo.fX + (m_tInfo.fCX / 2));
	m_Rect.top = static_cast<long>(m_tInfo.fY - (m_tInfo.fCY / 2));
	m_Rect.bottom = static_cast<long>(m_tInfo.fY + (m_tInfo.fCY / 2));
}