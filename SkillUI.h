#pragma once
#include "ui.h"
#include "BitMgr.h"
#include "Mouse.h"

class CSkillUI :
	public CUI
{
public:
	//bool	m_Act;	//Ȱ��ȭ �ڵ�
private:
	bool	m_Drag;	//Ŭ�� ���� Ȯ��
	float fX;
	float fY;

public:
	virtual void Initialize(void);
	virtual void Update(void);
	virtual void Render(void);
	virtual void Release(void);

	virtual bool HighRect(void);

public:
	CSkillUI(void);
	virtual ~CSkillUI(void);
};
