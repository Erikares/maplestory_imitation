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
	TCHAR*	m_pName;	//UI�� �̸�
	bool	m_Act;		//Ȱ��ȭ �ڵ�
	bool	m_DragAct;	//�巡�� Ȱ��ȭ �ڵ�
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
