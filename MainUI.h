#pragma once
#include "ui.h"
#include "BitMgr.h"
#include "Mouse.h"
#include "Player.h"

class CPlayer;

class CMainUI :
	public CUI
{
private:
	QSLOT*		m_pQuick;

public:
	virtual void Initialize(void);
	virtual void Update(void);
	virtual void Render(void);
	virtual void Release(void);

	virtual bool HighRect(void);



public:
	CMainUI(void);
	virtual ~CMainUI(void);
};
