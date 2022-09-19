#pragma once
#include "ui.h"
#include "BitMgr.h"
#include "Mouse.h"

class CEquipUI :
	public CUI
{
private:
	bool	m_Drag;
	float 	fX;
	float 	fY;
	EINFO*	m_pEquip;

public:
	virtual void Initialize(void);
	virtual void Update(void);
	virtual void Render(void);
	virtual void Release(void);

	virtual bool HighRect(void);

public:
	CEquipUI(void);
	virtual ~CEquipUI(void);
};
