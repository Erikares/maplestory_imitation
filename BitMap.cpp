#include "StdAfx.h"
#include "BitMap.h"

CBitMap::CBitMap(void)
{
}

CBitMap::~CBitMap(void)
{
	Release();
}

CBitMap*	CBitMap::LoadBmp(TCHAR *pFilename)
{
	m_hdc	= GetDC(g_hWnd);

	m_MemDC = CreateCompatibleDC(m_hdc);

	ReleaseDC(g_hWnd, m_hdc);

	m_Bitmap = (HBITMAP)LoadImage(NULL, pFilename, IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if(!m_Bitmap)
	{
		MessageBox(g_hWnd, pFilename, L"Image Load Failed", MB_OK);
	}

	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_Bitmap);

	return this;
}

void CBitMap::Release()
{
	SelectObject(m_MemDC, m_OldBitmap);
	DeleteObject(m_Bitmap);
	DeleteObject(m_MemDC);
}

HDC	CBitMap::GetMemDC(void)
{
	return m_MemDC;
}