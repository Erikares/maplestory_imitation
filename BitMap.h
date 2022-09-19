#pragma once

class CBitMap
{
private:
	HDC			m_hdc;
	HDC			m_MemDC;
	HBITMAP		m_Bitmap;
	HBITMAP		m_OldBitmap;
public:
	CBitMap*	LoadBmp(TCHAR*	pFilename);
	HDC			GetMemDC(void);
	void		Release(void);

public:
	CBitMap(void);
	~CBitMap(void);
};
