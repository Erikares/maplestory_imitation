#pragma once
#include "BitMap.h"

class CBitMgr
{
	DECLARE_SINGLETONE(CBitMgr)
private:
	map<const TCHAR*, CBitMap*>		m_MapBit;

public:
	void		LoadImageByScene(eSceneType eType);
	HDC			GetImage(const TCHAR*	pKey);
	void		Release(void);
	void		Initialize(void);

private:
	CBitMgr(void);
public:
	~CBitMgr(void);
};
