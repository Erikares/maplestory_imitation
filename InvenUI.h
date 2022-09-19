#pragma once
#include "ui.h"
#include "BitMgr.h"
#include "Item.h"
#include "Mouse.h"

class CInvenUI :
	public CUI
{
public:
	//bool	m_Act;	//Ȱ��ȭ �ڵ�
private:
	bool	m_Drag;	//Ŭ�� ���� Ȯ��
	float fX;
	float fY;

	vector<CItem*>* m_pVecInven;

public:
	virtual void Initialize(void);
	virtual void Update(void);
	virtual void Render(void);
	virtual void Release(void);

	virtual bool HighRect(void);

	void	RenderItem(void);
	void	SetVector(vector<CItem*>* pInven)
	{
		m_pVecInven = pInven;
	}

public:
	CInvenUI(void);
	virtual ~CInvenUI(void);
};
