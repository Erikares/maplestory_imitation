#pragma once
#include "ui.h"
#include "BitMgr.h"
#include "Mouse.h"

class CSkillUI :
	public CUI
{
public:
	//bool	m_Act;	//활성화 코드
private:
	bool	m_Drag;	//클릭 여부 확인
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
