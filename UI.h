#pragma once
#include "Obj.h"
#include "Player.h"

class CUI
{
protected:
	RECT	m_Rect;
	INFO	m_tInfo;
	CObj*	m_pPlayer;
	

public:
	TCHAR*	m_pName;	//UI의 이름
	bool	m_Act;		//활성화 코드
	bool	m_DragAct;	//드래그 활성화 코드
public:
	virtual void Initialize(void) PURE;
	virtual void Update(void);
	virtual void Render(void) PURE;
	virtual void Release(void) PURE;
	virtual bool HighRect(void) PURE;

	void SetPlayer(CObj* pPlayer)
	{
		m_pPlayer = pPlayer;
	}

public:
	CUI(void);
	virtual ~CUI(void);



};
