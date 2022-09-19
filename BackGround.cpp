#include "StdAfx.h"
#include "BackGround.h"

CBackGround::CBackGround(void)
{
	m_tInfo.fX = WINCX / 2;
	m_tInfo.fY = WINCY / 2;
}

CBackGround::~CBackGround(void)
{
}

void CBackGround::Initialize()
{
	m_tInfo.fX = WINCX / 2;
	m_tInfo.fY = WINCY / 2;
}

int CBackGround::Update()
{
	return 0;
}

void CBackGround::Render()
{
}

void CBackGround::Release()
{
}
