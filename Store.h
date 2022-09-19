#pragma once
#include "ui.h"
#include "Mouse.h"
#include "BitMgr.h"
#include "Item.h"

class CStore :
	public CUI
{
private:
	bool	m_Drag;
	float 	fX;
	float 	fY;
	vector<CItem*>	m_vecStore;

public:
	virtual void Initialize(void);
	virtual void Update(void);
	virtual void Render(void);
	virtual void Release(void);
	virtual bool HighRect(void);

	
	vector<CItem*>* GetVector(void)
	{
		return &m_vecStore;
	}

public:
	CStore(void);
	virtual ~CStore(void);
};
