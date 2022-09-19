#pragma once
#include "Mouse.h"
#include "Player.h"
#include "KeyMgr_60.h"

class CPlayer;
class CItem
{
protected:
	RECT	m_Rect;
	INFO	m_tInfo;
	TINFO	m_tItem;
	TCHAR*	m_pName;
	EINFO*	m_pEquip;
	CObj*	m_pPlayer;
	CItem*	m_tempItem;

	vector<CItem*>*	m_pVecInven;



public:
	bool	m_Drag;
	float	fX;
	float	fY;

public:
	void	Update(void);
	void	SetItem(int _iCode);

	void	SetVector(vector<CItem*>* pVector)
	{
		m_pVecInven = pVector;
	}
	void	SetEquip(EINFO*	pEquip)
	{
		m_pEquip = pEquip;
	}

	RECT*	GetRect(void)
	{
		return &m_Rect;
	}

	INFO*	GetInfo(void)
	{
		return &m_tInfo;
	}

	int GetItemType(void)
	{
		return m_tItem.eType;
	}

	TCHAR*	GetItemName(void)
	{
		return m_tItem.pName;
	}

	void	MouseCheck(void);

public:
	CItem(void);
	virtual ~CItem(void);
};
