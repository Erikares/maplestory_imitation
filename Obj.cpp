#include "StdAfx.h"
#include "Obj.h"


CObj::CObj(void)
{
	memset(&m_Rect, 0, sizeof(RECT));
	memset(&m_tInfo, 0, sizeof(INFO));
	//m_ptScroll.x = 0;
	//m_ptScroll.y = 0;
}

CObj::~CObj(void)
{
}

void CObj::Initialize()
{
}

int CObj::Update()
{
	m_Rect.left = static_cast<long>(m_tInfo.fX - (m_tInfo.fCX / 2));
	m_Rect.right = static_cast<long>(m_tInfo.fX + (m_tInfo.fCX / 2));
	m_Rect.top = static_cast<long>(m_tInfo.fY - (m_tInfo.fCY / 2));
	m_Rect.bottom = static_cast<long>(m_tInfo.fY + (m_tInfo.fCY / 2));
	return 0;
}

void CObj::Render()
{
}

void CObj::Release()
{
}
